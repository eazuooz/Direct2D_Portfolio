#pragma once
#include <map>

#include "Camera.h"
#include "RenderPath.h"

//모든 렌더러들의 렌더순서와
//렌더러가	render함수를 호출하는 순서를 조정하고
//카메라도 여러개 만들면 관리를 쉽게 해주는것이 좋을것이다
//컴포넌트도 필요성이 생긴다.
//카메라/ Rnder::FInDCAMERA(L"");
//뷰행렬과 프로젝트 행렬이 없으면 안되죠
//카메라 누가렌더링 하는거야?
//누가 이걸 봐주고 있는거야?
//렌더를 하는 그룹
//카메라
//렌더러
//HCAM의 기능중 나는 어떤 렌더러 부류들만 비춰준다

class Mesh;
class RenderManager;
class Instancing
{
public:
	friend RenderManager;

private:
	RenderPath	renderPath;
	const type_info* dataType;
	int dataSize;
	int dataCount;
	std::vector<char>	data;	//인스턴싱용 데이터를 모아두는곳
	My_Ptr<Mesh> mesh;

public:
	void SetRenderPath(const RenderPath& _RenderPath)
	{
		renderPath = _RenderPath;
	}

public:
	void SetMesh(const wchar_t* _Name);
};


class Camera;
class Scene;
class Renderer;
class RenderManager
{
public:
	enum SORTTYPE
	{
		NONE, 
		Z,Y,X,
		CAMZ, CAMY, CAMX,
		MAX,
	};

public:
	friend Camera;
	friend Renderer;
	friend Scene;

private:
	Scene* scene;

private:
	std::map<int, std::list<My_Ptr<Camera>>>::iterator	camListMap_Begin;
	std::map<int, std::list<My_Ptr<Camera>>>::iterator	camListMap_End;
	std::map<int, std::list<My_Ptr<Camera>>>			camListMap;
	std::map<int, SORTTYPE>								sortType;

	std::list<My_Ptr<Camera>>::iterator					camList_Begin;
	std::list<My_Ptr<Camera>>::iterator					camList_End;
	std::list<My_Ptr<Camera>>							camList;

private:
	void CollectCamForRender(int _Order);
	void SortByCameraOrder();

private:
	void PushCamera(const My_Ptr<Camera>& _CAM);

private:
	// 오더
	// 0을 기준으로 생각하자.
	// 1번 그룹이 있다면
	std::map<int, std::list<My_Ptr<Renderer>>>::iterator renderListMap_Begin;
	std::map<int, std::list<My_Ptr<Renderer>>>::iterator renderListMap_End;
	std::map<int, std::list<My_Ptr<Renderer>>> renderList_Map;

	std::list<My_Ptr<Renderer>>::iterator renderList_Begin;
	std::list<My_Ptr<Renderer>>::iterator renderList_End;

private:
	void PushRenderer(const My_Ptr<Renderer>& _Renderer);


public:
	void Render();
	void Release();
	void OverRendererRelease();
//SORT FUNCTION
public:
	static bool ZSort(const My_Ptr<Renderer>&, const My_Ptr<Renderer>&);
	static bool YSort(const My_Ptr<Renderer>&, const My_Ptr<Renderer>&);
	static bool XSort(const My_Ptr<Renderer>&, const My_Ptr<Renderer>&);
	static bool (*sortFunc[MAX])(const My_Ptr<Renderer>&, const My_Ptr<Renderer>&);

	//INSTANCING
private:
	static std::map<std::wstring, My_Ptr<Instancing>>::iterator findInstIter;
	static std::map<std::wstring, My_Ptr<Instancing>> instMap;

public:
	static My_Ptr<Instancing> FindInstancing(const wchar_t* _Name)
	{
		findInstIter = instMap.find(_Name);
		
		if (findInstIter == instMap.end())
		{
			return nullptr;
		}
		return findInstIter->second;
	}

	template<typename  T>
	static void CreateInstancing(const wchar_t* _Name, const wchar_t* _MeshName, const RenderPath& _Path, UINT _InstCount = 1000)//자동확장하게 만들겠다.
	{
		My_Ptr<Instancing> inst = FindInstancing(_Name);
		
		if (nullptr != inst)
		{
			BOOM;
			return;
		}

		inst = new Instancing();
		inst->SetMesh(_MeshName);
		inst->SetRenderPath(_Path);

		inst->dataType = &typeid(T);
		inst->dataSize = sizeof(T);
		inst->dataCount = _InstCount;
		inst->data.resize(inst->dataSize * inst->dataCount);

		instMap.insert(std::map<std::wstring, My_Ptr<Instancing>>::value_type(_Name, inst));
	}

public:
	RenderManager(Scene* _Scene) ;
	~RenderManager();
};

