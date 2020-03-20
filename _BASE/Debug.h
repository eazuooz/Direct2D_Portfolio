#pragma once
#include <assert.h>

#include <crtdbg.h>
#include <iostream>
#include <Windows.h>



#pragma region BASEDEFINE

#define BOOM assert(false)

#pragma endregion

#define FALLTHROUGH void(0)


class Debug
{
private:
	static Debug m_Inst;
		
public:
	static Debug& Inst()
	{		
		return m_Inst;
	}

#pragma region ACTIVE
private:
	bool active;

public:
	inline void On()
	{
		active = true;
	}

	inline void Off()
	{
		active = false;
	}

	bool GetActive()
	{
		return active;
	}
#pragma endregion

#pragma region CONSOLE
public:
	bool IsOpenConsole;
	   
	void OpenConsole();
	void EndConsole();

	void ConsolePrintLineArg(const wchar_t* _Text, ...);
	void ConsolePrintArg(const wchar_t* _Text, ...);

	void ConsolePrintLine(const wchar_t* _Text);
	void ConsolePrint(const wchar_t* _Text);
	void ConsolePrint(const char* _Text);

#pragma endregion

public:
	void LeakCheck();
	
public:
	void Update();
	void RenderObj();
	void PrintText(HDC _DC, int _X, int _Y, const std::wstring _Str);


private:
	Debug() : IsOpenConsole(false), active(true) { }
	~Debug() {}
};