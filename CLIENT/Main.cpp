#ifdef X32
#ifdef DEBUGMODE
#pragma comment(lib, "..\\_BIN\\X32\\ENGINED32.lib")
#elif RELEASEMODE
#pragma comment(lib, "..\\_BIN\\X32\\ENGINER32.lib")
#endif
#elif X64
#ifdef DEBUGMODE
#pragma comment(lib, "..\\_BIN\\X64\\ENGINED64.lib")
#elif RELEASEMODE
#pragma comment(lib, "..\\_BIN\\X64\\ENGINER64.lib")
#endif
#endif

#ifdef X32
#ifdef DEBUGMODE
#pragma comment(lib, "..\\_BIN\\X32\\LOGICD32.lib")
#elif RELEASEMODE
#pragma comment(lib, "..\\_BIN\\X32\\LOGICR32.lib")
#endif
#elif X64
#ifdef DEBUGMODE
#pragma comment(lib, "..\\_BIN\\X64\\LOGICD64.lib")
#elif RELEASEMODE
#pragma comment(lib, "..\\_BIN\\X64\\LOGICR64.lib")
#endif
#endif

#include <SDKDDKVer.h>

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>


//#include <MyWindow.h>
#include <GameWindow.h>
#include <GraphicDevice.h>
#include <Debug.h>
#include <Actor.h>

#include "SoftRender.h"

//===================UPDATER====================//
#include "LoadingUpdater.h"
#include "TitleUpdater.h"
#include "SelectUpdater.h"
#include "SelectMapUpdater.h"
#include "AdventureUpdater.h"
#include "EndingUpdater.h"

#include "TestUpdater.h"
//=============================================//
#include "Mouse.h"


// C 런타임 헤더 파일입니다.
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	Debug::Inst().LeakCheck();
	Debug::Inst().OpenConsole();
	//Mouse::Inst().Init();


	GameWindow::Init(hInstance);
	GameWindow::CreateGameWindow(L"MainWindow");
	GameWindow::Inst()->SetSize(640, 480);
	GameWindow::Inst()->CreateGraphicDevice();

	//GraphicDevice::Inst()->CreateDevice(L"MainWindow");
	
	GameWindow::Inst()->CreateScene(L"TestScene",		new TestUpdater());


	GameWindow::Inst()->CreateScene(L"LoadingScene",	new LoadingUpdater());
	GameWindow::Inst()->CreateScene(L"TitleScene",		new TitleUpdater());
	GameWindow::Inst()->CreateScene(L"SelectMapScene",	new SelectMapUpdater());
	GameWindow::Inst()->CreateScene(L"SelectScene",		new SelectUpdater());
	GameWindow::Inst()->CreateScene(L"AdventureScene",	new AdventureUpdater());
	GameWindow::Inst()->CreateScene(L"EndingScene",		new EndingUpdater());
	
	GameWindow::Inst()->ChangeScene(L"EndingScene");	
	GameWindow::Inst()->ChangeScene(L"LoadingScene");
	//GameWindow::Inst()->ChangeScene(L"TestScene");

	GameWindow::EngineLoop();
	Debug::Inst().EndConsole();
	Mouse::Inst().Destroy();
	AdventureUpdater::DeletesHatchList();
}