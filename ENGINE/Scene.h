#pragma once
#ifdef X32
#ifdef DEBUGMODE
#pragma comment(lib, "..\\_BIN\\X32\\_BASED32.lib")
#elif RELEASEMODE
#pragma comment(lib, "..\\_BIN\\X32\\_BASER32.lib")
#endif
#elif X64
#ifdef DEBUGMODE
#pragma comment(lib, "..\\_BIN\\X64\\_BASED64.lib")
#elif RELEASEMODE
#pragma comment(lib, "..\\_BIN\\X64\\_BASER64.lib")
#endif
#endif

#include <map>
#include <list>

#include <Name.h>
#include <MyTime.h>
//#include <MyWindow.h>


//#include "GameWindow.h"
#include "UpdaterBase.h"
#include "GraphicDevice.h"
#include "Actor.h"
#include "Transform.h"

#include "RenderManager.h"
#include "ColliderManager.h"


class GameWindow;
class Scene final : public ControlBlock, public Name, public UpdaterBase
{
public:
	friend GameWindow;

#pragma region INNER CLASS
public:
	class Updater: public ControlBlock
	{
	public:
		friend Scene;

	private:
		Scene* scene;
		void SetScene(Scene* _Scene)
		{
			scene = _Scene;
		}

	public:
		Scene* GetScene()
		{
			return scene;
		}

	private:
		bool isLoading;

	protected:
		Updater() : isLoading(false) {}

		virtual void Loading()		= 0;	//로딩
		virtual void SceneUpdate()	{}		//씬 업데이트에서 만들어야할 내용
		virtual void ChangeStart()	{}		//내가 새로운 메인씬이 되었을떄
		virtual void ChangeEnd()	{}		//내가 이제 사라질때
	};
	
#pragma endregion

#pragma region MEMBER

private:
	GameWindow* pWindow;
	void SetWindow(GameWindow* _Window) { pWindow = _Window; }
public:
	GameWindow* GetWindow() { return pWindow; }

#pragma region UPDATER
private:
	std::list <My_Ptr<Updater>> updaterList;
	std::list <My_Ptr<Updater>>::iterator updaterStart;
	std::list <My_Ptr<Updater>>::iterator updaterEnd;

private:
	virtual void LoadingCheck()
	{
 		updaterStart = updaterList.begin();
		updaterEnd	 = updaterList.end();

		for (; updaterStart != updaterEnd; ++updaterStart)
		{
			if (false == (*updaterStart)->isLoading)
			{
				(*updaterStart)->Loading();
				(*updaterStart)->isLoading = true;
			}
		}
	}

public:
	template<typename Updater>
	void AddUpdater()
	{
		Updater* newUpdater = new Updater();
		AddUpdater(newUpdater);
	}
private:
	void AddUpdater(My_Ptr<Updater> _Updater);
#pragma endregion

#pragma region ACTOR
	private:
		std::list<My_Ptr<Actor>>::iterator actorStart;
		std::list<My_Ptr<Actor>>::iterator actorEnd;
		std::list<My_Ptr<Actor>> actorList;

public:
	My_Ptr<Actor> CreateActor(const wchar_t* _Name = L"GameObject");

public:
	void Loading() ; // 로딩될때
	void SceneUpdate(); // 로딩될때
	void ChangeEnd(); // 내가 이제 사라질때
	void ChangeStart(); // 내가 새로운 메인씬이 되었을때

private:
	void Progress();
	void SceneUpdater_Update();

	void ActorCheck();

	void UpdateAfter()		override;
	void Update()			override;
	void UpdateBefore()		override;
	void FinalUpdate()		override;
	void RenderObjBefore()	override;
	void RenderObjAfter()	override;
	void ColBefore()		override;
	void ColAfter()			override;
	void Release()			override;
	void ReleaseAfter()		override;


public:
	RenderManager	renderMgr;
	ColliderManager colliderMgr;

private:
	void SceneRender();
	void SceneColl();

#pragma region OverActorList
	std::list<My_Ptr<Actor>> ExtractOverActor(const wchar_t* _NextSceneName);
	void PushOverActor(std::list<My_Ptr<Actor>>&& _List);

#pragma endregion


private:
	Scene();
	~Scene();
#pragma endregion
};

