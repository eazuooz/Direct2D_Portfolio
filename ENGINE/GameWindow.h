#pragma once
#include <MyWindow.h>

#include "GraphicDevice.h"
#include "Scene.h"

class GameWindow : public Window
{
private:
	static std::map<std::wstring, My_Ptr<GameWindow>>::iterator gameWindow_Start;
	static std::map<std::wstring, My_Ptr<GameWindow>>::iterator gameWindow_End;
	static std::map<std::wstring, My_Ptr<GameWindow>> gameWindow_Map;
	static GameWindow* inst;

public:
	static My_Ptr<GameWindow> FindGameWindow(const wchar_t* _WindowName);
	static My_Ptr<GameWindow> CreateGameWindow(const wchar_t* _WindowName);
	
	//이미 만들어진 윈도우를 받아서 내가  관리하는 형식으로 가는
	static My_Ptr<GameWindow> CreateGameWindow(const wchar_t* _WindowName, HWND _Hwnd);


	static GameWindow* Inst()
	{
		return inst;
	}

public:
	static void EngineLoop();
	static void __stdcall GameWindowUpdate();

	////////////////////내부에서 씬을 게임 윈도우가 관리한다

private:
	std::map<std::wstring, My_Ptr<Scene>> sceneMap;
	My_Ptr<Scene> nextScene;
	My_Ptr<Scene> currentScene;
	Scene* madeScene;

public:
	std::set<std::wstring> sceneNameSet;	//모든 씬의 이름만 가지고있는 Set

public:
	void ChangeScene(const wchar_t* _SceneName);

#pragma region Variable Template
	template<typename ...Rest>
	void CreateScene(const wchar_t* _SceneName, Rest ..._Arg)
	{
		sceneNameSet.insert(std::set<std::wstring>::value_type(_SceneName));

		madeScene = new Scene();
		madeScene->SetWindow(this);
		madeScene->SetName(_SceneName);
		PushUpdater(_Arg...);
	}
	template<typename ...Rest>
	void PushUpdater(Scene::Updater* _Updater, Rest ..._Arg)
	{
		madeScene->AddUpdater(_Updater);
		PushUpdater(_Arg...);
	}
	void PushUpdater()
	{
		if (0 == sceneMap.size())	//first Created scene Become currentScene
		{
			nextScene = madeScene;
		}

		sceneMap.insert(std::map<std::wstring, My_Ptr<Scene>>::value_type(madeScene->GetName(), madeScene));

		madeScene = nullptr;
	}
#pragma endregion

	void SceneUpdate();

private:
	My_Ptr<GraphicDevice> device;

public:
	void CreateGraphicDevice();

private:
	GameWindow();
	~GameWindow();
};

