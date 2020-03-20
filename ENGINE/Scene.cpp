#include "Scene.h"
#include "Actor.h"
#include "Transform.h"

Scene::Scene() : renderMgr(this)
{
}


Scene::~Scene()
{
}

void Scene::AddUpdater(My_Ptr<Updater> _COM)
{
	if (nullptr == _COM)
	{
		BOOM;
		return;
	}

	_COM->SetScene(this);
	updaterList.push_back(_COM);
}

My_Ptr<Actor> Scene::CreateActor(const wchar_t* _Name )
{
	Actor* newActor = new Actor();
	newActor->SetName(_Name);
	newActor->SetScene(this);
	actorList.push_back(newActor);

	if (nullptr == newActor->AddComponent<Transform>())
	{
		BOOM;
		return nullptr;
	}

	return newActor;
}

void Scene::Loading() {}
void Scene::SceneUpdate() {}

void Scene::ChangeEnd() 
{
	updaterStart = updaterList.begin();
	updaterEnd = updaterList.end();

	for (; updaterStart != updaterEnd; ++updaterStart)
	{
		(*updaterStart)->ChangeEnd();
	}
}
void Scene::ChangeStart() 
{
	updaterStart = updaterList.begin();
	updaterEnd = updaterList.end();

	for (; updaterStart != updaterEnd; ++updaterStart)
	{
		(*updaterStart)->ChangeStart();
	}
}


// 의존성 역전의 법직을 잘 지켜라.
void Scene::Progress()
{
	// 씬만이 업데이트 해주는 것
	SceneUpdater_Update();

	ActorCheck();

	UpdateAfter();
	Update();
	UpdateBefore();
	FinalUpdate();
	RenderObjBefore();
	SceneRender();
	RenderObjAfter();
	ColBefore();
	SceneColl();
	//Col();
	ColAfter();
	Release();
	ReleaseAfter();
}

void Scene::SceneUpdater_Update()
{
	updaterStart = updaterList.begin();
	updaterEnd = updaterList.end();

	for (; updaterStart != updaterEnd; ++updaterStart)
	{
		(*updaterStart)->SceneUpdate();
	}
}

void Scene::ActorCheck()
{
	actorStart = actorList.begin();
	actorEnd = actorList.end();

	for (; actorStart != actorEnd; )
	{
		if (true == (*actorStart)->IsChildReady())
		{
			(*actorStart)->ChildReadyUpdate();
			actorStart = actorList.erase(actorStart);
		}
		else 
		{
			++actorStart;
		}
	}

	// ITERFOR(AStart, AEnd, m_ActorList, ChildReadyUpdate);
}

void Scene::UpdateAfter()
{
	actorStart = actorList.begin();
	actorEnd = actorList.end();

	for (; actorStart != actorEnd; ++actorStart)
	{
		if (false == (*actorStart)->IsUpdate())
		{
			continue;
		}
		(*actorStart)->UpdateAfter();
	}

	//ITERFOR(actorStart, actorEnd, actorList, UpdateAfter);
}
void Scene::Update()
{
	actorStart = actorList.begin();
	actorEnd = actorList.end();

	for (; actorStart != actorEnd; ++actorStart)
	{
		if (false == (*actorStart)->IsUpdate())
		{
			continue;
		}
		(*actorStart)->Update();
	}

	//ITERFOR(actorStart, actorEnd, actorList, Update);
}
void Scene::UpdateBefore()
{
	ITERFOR(actorStart, actorEnd, actorList, UpdateBefore);
}
void Scene::FinalUpdate()
{
	ITERFOR(actorStart, actorEnd, actorList, FinalUpdate);
}
void Scene::RenderObjBefore()
{
	ITERFOR(actorStart, actorEnd, actorList, RenderObjBefore);
}

void Scene::SceneRender()
{
	renderMgr.Render();
}
//void Scene::RenderObj()
//{
//	GraphicDevice::Inst()->ClearTarget();
//	GraphicDevice::Inst()->RenderTargetSetting();
//	GraphicDevice::Inst()->ViewPortSetting();
//	ITERFOR(actorStart, actorEnd, actorList, RenderObj);
//	GraphicDevice::Inst()->Present();
//}
void Scene::RenderObjAfter()
{
	ITERFOR(actorStart, actorEnd, actorList, RenderObjAfter);
}
void Scene::ColBefore()
{
	ITERFOR(actorStart, actorEnd, actorList, ColBefore);
}
//void Scene::Col()
//{
//	ITERFOR(actorStart, actorEnd, actorList, Col);
//}
void Scene::SceneColl()
{
	colliderMgr.Circulate_ColliderGroupMap();
}

void Scene::ColAfter()
{
	ITERFOR(actorStart, actorEnd, actorList, ColAfter);
}
void Scene::Release()
{
	//ITERFOR(actorStart, actorEnd, actorList, Release);

	renderMgr.Release();
	colliderMgr.Release();
		

	actorStart	= actorList.begin();
	actorEnd	= actorList.end();

	for (; actorStart != actorEnd;)
	{
		(*actorStart)->Release();
		if (true == (*actorStart)->IsDeath())
		{
			actorStart = actorList.erase(actorStart);
		}
		else
		{
			++actorStart;
		}
	}
}
void Scene::ReleaseAfter()
{
	ITERFOR(actorStart, actorEnd, actorList, ReleaseAfter);
}

std::list<My_Ptr<Actor>> Scene::ExtractOverActor(const wchar_t* _NextSceneName)
{
	std::list<My_Ptr<Actor>> overActor_List;

	actorStart = actorList.begin();
	actorEnd = actorList.end();

	for (; actorStart != actorEnd; )
	{
		if (false == (*actorStart)->IsOver())
		{
			++actorStart;
			continue;
		}
		else if (true == (*actorStart)->CheckSceneOver(_NextSceneName))
		{
			(*actorStart)->PossibleOverScene();

			overActor_List.push_back(*actorStart);
			actorStart = actorList.erase(actorStart);
		}
		else
		{
			++actorStart;
		}
	}

	renderMgr.OverRendererRelease();
	colliderMgr.OverColliderGroupRelease();

	return overActor_List;
}

void Scene::PushOverActor(std::list<My_Ptr<Actor>>&& _List)
{
	std::list<My_Ptr<Actor>>::iterator Start	= _List.begin();
	std::list<My_Ptr<Actor>>::iterator End		= _List.end();

	for (; Start != End; ++Start)
	{
		(*Start)->SetScene(this);
		
		//자신이 가진 컴포넌트들에게
		(*Start)->SceneChangeStart();
		(*Start)->ImPossibleOverScene();
		actorList.push_back((*Start));
	}
}

