#pragma once
#include "Shader.h"


class PxlShader : public Shader
{
private:
	ID3D11PixelShader* pixelShader;

public:
	bool Load(UINT _VH, UINT _VL, const char* _FuncName);
	void Update() override;

public:
	PxlShader();
	~PxlShader();
};

