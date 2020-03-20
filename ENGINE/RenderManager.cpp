#include "RenderManager.h"

#include "GraphicDevice.h"
#include "GraphicDebug.h"
#include "Renderer.h"

#include "Mesh.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Sampler.h"
#include "Sprite.h"
////



void Instancing::SetMesh(const wchar_t* _Name)
{
	mesh = Resources::Find<Mesh>(_Name);

	if (nullptr == mesh)
	{
		BOOM;
	}
}




/////
bool(*RenderManager::sortFunc[SORTTYPE::MAX])(const My_Ptr<Renderer>&, const My_Ptr<Renderer>&);
std::map<std::wstring, My_Ptr<Instancing>>::iterator RenderManager::findInstIter;
std::map<std::wstring, My_Ptr<Instancing>> RenderManager::instMap;


RenderManager::RenderManager(Scene* _Scene) : scene(_Scene)
{
	sortFunc[Z] = ZSort;
	sortFunc[Y] = YSort;
	sortFunc[X] = XSort;
	//sortFunc[CAMZ] = nullptr;
	//sortFunc[CAMY] = nullptr;
	//sortFunc[CAMX] = nullptr;
}


RenderManager::~RenderManager()
{
}

void RenderManager::CollectCamForRender(int _Order)
{
	camList.clear();

	camListMap_Begin	= camListMap.begin();
	camListMap_End		= camListMap.end(); 

	for (; camListMap_Begin != camListMap_End; ++camListMap_Begin)
	{
		camList_Begin	= camListMap_Begin->second.begin();
		camList_End	= camListMap_Begin->second.end();
			
		for (; camList_Begin != camList_End; ++camList_Begin)
		{
			if ((*camList_Begin)->IsAllView() || true == (*camList_Begin)->IsRender(_Order))
			{
				camList.push_back((*camList_Begin));
			}
		}
	}
}

void RenderManager::SortByCameraOrder()
{
	camListMap_Begin	= camListMap.begin();
	camListMap_End		= camListMap.end();
	

	std::list<My_Ptr<Camera>> TempCameraList;//OrderCheck
	for (; camListMap_Begin != camListMap_End; ++camListMap_Begin)
	{
		camList_Begin	= camListMap_Begin->second.begin();
		camList_End	= camListMap_Begin->second.end();

		for (; camList_Begin != camList_End; ++camList_Begin)
		{
			//둘이 다르다면 이녀석은 지금 여기에 있어야할 녀석이 아니다.
			if (camListMap_Begin->first != (*camList_Begin)->GetOrder())
			{
				TempCameraList.push_back((*camList_Begin));
				camList_Begin = camListMap_Begin->second.erase(camList_Begin);

				if (camList_End == camList_Begin)
				{
					break;
				}
			}
		}
	}

	camList_Begin		= TempCameraList.begin();
	camList_End		= TempCameraList.end();

	for (; camList_Begin != camList_End; ++camList_Begin)
	{
		PushCamera((*camList_Begin));
	}

	//TempCameraList.clear();
}

void RenderManager::PushCamera(const My_Ptr<Camera>& _CAM)
{
	std::map<int, std::list<My_Ptr<Camera>>>::iterator FindIter	= camListMap.find(_CAM->GetOrder());

	if (FindIter == camListMap.end())
	{
		camListMap.insert(std::map<int, std::list<My_Ptr<Camera>>>::value_type(_CAM->GetOrder(), std::list<My_Ptr<Camera>>()));
		FindIter = camListMap.find(_CAM->GetOrder());
	}

	FindIter->second.push_back(_CAM);
}

void RenderManager::PushRenderer(const My_Ptr<Renderer>& _Renderer)
{
	std::map<int, std::list<My_Ptr<Renderer>>>::iterator FindIter = renderList_Map.find(_Renderer->GetOrder());

	if (FindIter == renderList_Map.end())
	{
		renderList_Map.insert(std::map<int, std::list<My_Ptr<Renderer>>>::value_type
		(_Renderer->GetOrder(), std::list<My_Ptr<Renderer>>()));
		FindIter = renderList_Map.find(_Renderer->GetOrder());
		sortType.insert(std::map<int, SORTTYPE>::value_type(_Renderer->GetOrder(), SORTTYPE::Z));
	}

	FindIter->second.push_back(_Renderer);
}


void RenderManager::Render()
{
	GraphicDevice::Inst()->ClearTarget();
	GraphicDevice::Inst()->RenderTargetSetting();
	GraphicDevice::Inst()->ViewPortSetting();

	// ★ 1. 모든 렌더그룹을 돌릴준비를한다.	
	renderListMap_Begin = renderList_Map.begin();
	renderListMap_End	= renderList_Map.end();

	for (; renderListMap_Begin != renderListMap_End; ++renderListMap_Begin)
	{
		//★ 2. 이 렌더 그룹을 렌더할 카메라들을 모은다.
		CollectCamForRender(renderListMap_Begin->first);
		//카메라중 어떤 카메라가 우선적으로 그걸 렌더할거느냐가 의미가 있다.
		//들어가 있는 캠들
		camList_Begin	= camList.begin();
		camList_End		= camList.end();

		//★ 3. 카메라들이 렌더 그룹에 속한 렌더러들을 모조리 렌더한다. 
		for (; camList_Begin != camList_End; ++camList_Begin)
		{
			std::map<int, SORTTYPE>::iterator sortIter = sortType.find(renderListMap_Begin->first);
			if (SORTTYPE::NONE != sortIter->second)
			{
				//아무것도 안넣어주는건 그냥 값 비교로정렬
				renderListMap_Begin->second.sort(sortFunc[sortIter->second]);
			}

			renderList_Begin	= renderListMap_Begin->second.begin();
			renderList_End		= renderListMap_Begin->second.end();
			for (; renderList_Begin != renderList_End; ++renderList_Begin)
			{
				if (false == (*renderList_Begin)->IsUpdate())
				{
					continue;
				}
				//(*renderList_Start)->
				(*renderList_Begin)->Render((*camList_Begin));
				GraphicDevice::Inst()->MainReset();
			}
		}
	}

	GraphicDebug::DebugRender();


	GraphicDevice::Inst()->MainReset();
	GraphicDevice::Inst()->Present();
}

void RenderManager::Release()
{
	renderListMap_Begin = renderList_Map.begin();
	renderListMap_End = renderList_Map.end();

	for (; renderListMap_Begin != renderListMap_End; ++renderListMap_Begin)
	{
		renderList_Begin = renderListMap_Begin->second.begin();
		renderList_End = renderListMap_Begin->second.end();

		for (; renderList_Begin != renderList_End; )
		{
			if (true == (*renderList_Begin)->IsDeath())
			{
				renderList_Begin = renderListMap_Begin->second.erase(renderList_Begin);
			}
			else
			{
				++renderList_Begin;
			}
		}
	}
}


void RenderManager::OverRendererRelease()
{
	renderListMap_Begin = renderList_Map.begin();
	renderListMap_End = renderList_Map.end();

	for (; renderListMap_Begin != renderListMap_End; ++renderListMap_Begin)
	{
		renderList_Begin = renderListMap_Begin->second.begin();
		renderList_End = renderListMap_Begin->second.end();

		for (; renderList_Begin != renderList_End; )
		{
			if (true == (*renderList_Begin)->GetActor()->IsOverScene())
			{
				renderList_Begin = renderListMap_Begin->second.erase(renderList_Begin);
			}
			else
			{
				++renderList_Begin;
			}
		}
	}
}

#pragma region SORT FUNC
bool RenderManager::ZSort(const My_Ptr<Renderer>& _Left, const My_Ptr<Renderer>& _Right)
{
	return _Left->GetActor()->GetTransform()->GetPosition().z > _Right->GetActor()->GetTransform()->GetPosition().z;
}

bool RenderManager::YSort(const My_Ptr<Renderer>& _Left, const My_Ptr<Renderer>& _Right)
{
	return _Left->GetActor()->GetTransform()->GetPosition().y > _Right->GetActor()->GetTransform()->GetPosition().y;
}

bool RenderManager::XSort(const My_Ptr<Renderer>& _Left, const My_Ptr<Renderer>& _Right)
{
	return _Left->GetActor()->GetTransform()->GetPosition().x > _Right->GetActor()->GetTransform()->GetPosition().x;
}
#pragma endregion


