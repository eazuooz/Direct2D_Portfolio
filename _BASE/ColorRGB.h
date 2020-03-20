#pragma once
#include <Windows.h>




#define MAGENTA RGB(255, 0, 255)
class ColorRGB
{
public:
	static const int Magenta;
	static const int Red;
	static const int Blue;

	static int RGBAToInt(UCHAR R, UCHAR G, UCHAR B, UCHAR A)
	{
		UCHAR Arr[4] = {R, G, B, A};

		return *((int*)Arr);
	}


public:
	ColorRGB(int _R = 255, int _G = 0, int _B = 255)
	{
		color = (	(COLORREF)(((BYTE)(_R) | ((WORD)((BYTE)(_G)) << 8)) | (((DWORD)(BYTE)(_B)) << 16)) );
	}

	ColorRGB(UINT _Color)
	{
		color = _Color;
	}

	~ColorRGB() = default;

public:
	UINT color;
};

