#pragma once
#include "Resources.h" 


#ifdef X32
#ifdef DEBUGMODE
#pragma comment(lib, "..\\TPARTY\\X32\\Debug\\FW1FontWrapperD32.lib")
#elif RELEASEMODE
#pragma comment(lib, "..\\TPARTY\\X32\\Release\\FW1FontWrapperR32.lib")
#endif
#elif X64
#ifdef DEBUGMODE
#pragma comment(lib, "..\\TPARTY\\X64\\Debug\\FW1FontWrapperD64.lib")
#elif RELEASEMODE
#pragma comment(lib, "..\\TPARTY\\X64\\Release\\FW1FontWrapperR64.lib")
#endif
#endif

#include <FW1CompileSettings.h>
#include <FW1FontWrapper.h>

class Font : public Resources
{
private:
	IFW1Factory* fontFactory;
	IFW1FontWrapper* fontWrapper;

public:
	bool Create(const wchar_t* _FontName);
	bool DrawWorld(const wchar_t* _Name, float _FontSize, Vector4 _Position, Vector4 _Color, FW1_TEXT_FLAG _Flag);

	//스크린좌표 기준으로 하므로 캐릭터 머리우에 캐리턱명을 띄우고 싶다던가 하면
	// 월드 좌표계에서 스크린 좌표계로 변환해서 수치를 넣어주면 될것이다.
	void DrawUI(const wchar_t* _Name, float _FontSize, Vector4 _Position, Vector4 _Color, FW1_TEXT_FLAG _Flag = FW1_TOP);



public:
	Font();
	~Font();
};

