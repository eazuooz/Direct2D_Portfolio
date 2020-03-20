#include "GameWindow.h"
#include <Input.h>
#include "Sound.h"

std::map<std::wstring, My_Ptr<GameWindow>>::iterator GameWindow::gameWindow_Start;
std::map<std::wstring, My_Ptr<GameWindow>>::iterator GameWindow::gameWindow_End;
std::map<std::wstring, My_Ptr<GameWindow>> GameWindow::gameWindow_Map;
GameWindow* GameWindow::inst = nullptr;

GameWindow::GameWindow() : nextScene(nullptr), currentScene(nullptr), madeScene(nullptr)
{
}


GameWindow::~GameWindow()
{
	int a = 0;
}

My_Ptr<GameWindow> GameWindow::FindGameWindow(const wchar_t* _WindowName)
{
	std::map<std::wstring, My_Ptr<GameWindow>>::iterator FindIter = gameWindow_Map.find(_WindowName);

	if (FindIter == gameWindow_Map.end())
	{
		return nullptr;
	}

	return FindIter->second;
}

My_Ptr<GameWindow> GameWindow::CreateGameWindow(const wchar_t* _WindowName)
{
	if (nullptr != FindGameWindow(_WindowName))
	{
		BOOM;
	}

	GameWindow* NewGameWindow = new GameWindow();
	NewGameWindow->SetName(_WindowName);

	if (false == NewGameWindow->Create(L"Default", _WindowName))
	{
		BOOM;
		return nullptr;
	}

	if (0 == gameWindow_Map.size())
	{
		mainWindow	= NewGameWindow;
		inst		= NewGameWindow;
	}

	NewGameWindow->Show();
	gameWindow_Map.insert(std::map<std::wstring, My_Ptr<GameWindow>>::value_type(_WindowName, NewGameWindow));
	InsertOtherWindow(NewGameWindow);

	return NewGameWindow;
}

My_Ptr<GameWindow> GameWindow::CreateGameWindow(const wchar_t* _WindowName, HWND _Hwnd)
{
	if (nullptr == _Hwnd)
	{
		BOOM;
	}

	GameWindow* newGameWindow = new GameWindow();
	newGameWindow->SetName(_WindowName);
	newGameWindow->hWnd = _Hwnd;
	newGameWindow->Init();
	if (0 == gameWindow_Map.size())
	{
		mainWindow = newGameWindow;
		inst = newGameWindow;
	}

	gameWindow_Map.insert(std::map<std::wstring, My_Ptr<GameWindow>>::value_type(_WindowName, newGameWindow));
	InsertOtherWindow(newGameWindow);

	return newGameWindow;
}

void GameWindow::EngineLoop()
{
	Sound::Init();
	Time::Reset();
	Window::BasicPeekLoop(GameWindowUpdate);
}

void __stdcall GameWindow::GameWindowUpdate()
{
	Sound::Update();
	Time::Update();
	Input::Update();
	

	gameWindow_Start = gameWindow_Map.begin();
	gameWindow_End = gameWindow_Map.end();

	for (; gameWindow_Start != gameWindow_End; ++gameWindow_Start)
	{
		gameWindow_Start->second->Update();
		gameWindow_Start->second->SceneUpdate();
	}
}


//////////////SCENE

void GameWindow::ChangeScene(const wchar_t* _SceneName)
{
	if (nullptr != currentScene && _SceneName == currentScene->GetWstringName())
	{
		return;
	}


	std::map<std::wstring, My_Ptr<Scene>>::iterator FindIter = sceneMap.find(_SceneName);

	if (FindIter == sceneMap.end())
	{
		BOOM;
		return;
	}

	nextScene = FindIter->second;
}

void GameWindow::SceneUpdate()
{
	if (nullptr != nextScene)
	{
		if (nextScene == currentScene)
		{
			BOOM;
		}

		if (nullptr != currentScene)
		{
			currentScene->ChangeEnd();
			nextScene->PushOverActor(currentScene->ExtractOverActor(nextScene->GetName()));
		}

		nextScene->LoadingCheck();
		currentScene = nextScene;
		currentScene->ChangeStart();
		nextScene = nullptr;
	}
	currentScene->Progress();
}

void GameWindow::CreateGraphicDevice()
{
	device = new GraphicDevice();
	device->Init(this);
}