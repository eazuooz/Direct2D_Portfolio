#include "Debug.h"

Debug Debug::m_Inst = Debug();

#pragma region CONSOLE

void Debug::OpenConsole()
{
	if (AllocConsole())
	{
		FILE* acStreamOut;
		FILE* acStreamIn;

		IsOpenConsole = true;
		freopen_s(&acStreamOut, "CONOUT$",	"wt",	stdout);
		freopen_s(&acStreamIn,	"CONIN$",	"r",	stdin);		
		
		std::wcout.imbue(std::locale("kor"));
		std::wcout << L"콘솔창 출력 성공!!!" << std::endl;
	}
}


void Debug::ConsolePrintLineArg(const wchar_t* _Text, ...)
{
	if (false == IsOpenConsole) { return; }

	va_list		argp;
	va_start(argp, _Text);
	wchar_t Text[1024] = { 0, };
	swprintf_s(Text, _Text, argp);
	va_end(argp);

	std::wcout << _Text << std::endl;
}

void Debug::ConsolePrintArg(const wchar_t* _Text, ...)
{
	if (false == IsOpenConsole) { return; }

	va_list		argp;
	va_start(argp, _Text);
	wchar_t Text[1024] = { 0, };
	swprintf_s(Text, _Text, argp);
	va_end(argp);

	std::wcout << _Text;
}

void Debug::ConsolePrintLine(const wchar_t* _Text)
{
	if (false == IsOpenConsole)
	{
		return;
	}

	std::wcout << _Text << std::endl;
}
void Debug::ConsolePrint(const wchar_t* _Text) 
{
	if (false == IsOpenConsole)
	{
		return;
	}

	std::wcout << _Text;
}

void Debug::ConsolePrint(const char* _Text)
{
	if (false == IsOpenConsole)
	{
		return;
	}

	std::cout << _Text;
}

void Debug::EndConsole()
{
	if (true == IsOpenConsole)
	{
		FreeConsole();	//콘솔을 해제
	}
}



#pragma endregion




void Debug::LeakCheck()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(2800);
}

void Debug::Update()
{

}

void Debug::RenderObj()
{

}

void Debug::PrintText(HDC _DC, int _X, int _Y, const std::wstring _Str)
{
	std::wstring str = _Str;
	TextOutW(_DC, _X, _Y, str.c_str(), (int)str.size() );
	//TextOut(GameCore::MainWindow().GetHDC(), 100, 80, Path::FindPathToString(L"Charcter").c_str(), (int)Path::FindPathToString(L"Charcter").size());
}
