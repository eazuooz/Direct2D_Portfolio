#pragma once
#include "Resources.h"
#include "Shader.h"

#include <DirectXTex.h>

//#ifdef _WIN32
//#ifdef _WIN64         /// 64-bit  only
//#ifdef _DEBUG         /// 64-bit debug
//#pragma comment(lib, "..\\x64\\Debug\\DirectXTex.lib")
//#else               /// 64-bit release
//#pragma comment(lib, "..\\x64\\Release\\DirectXTex.lib")
//#endif               // 64-bit _DEBUG
//#else               /// 32-bit  only
//#ifdef _DEBUG         /// 32-bit debug
//#pragma comment(lib, "..\\x32\\Debug\\DirectXTex.lib")
//#else               /// 32-bit release
//#pragma comment(lib, "..\\x32\\Release\\DirectXTex.lib")
//#endif               // 32-bit _DEBUG
//#endif               // _WIN64
///// 32/64 common def 공통된 부분 64 32같이 사용하는경우
//#endif               // _WIN32

#ifdef X32
#ifdef DEBUGMODE
#pragma comment(lib, "..\\TPARTY\\X32\\Debug\\DirectXTex.lib")
#elif RELEASEMODE
#pragma comment(lib, "..\\TPARTY\\X32\\Release\\DirectXTex.lib")
#endif
#elif X64
#ifdef DEBUGMODE
#pragma comment(lib, "..\\TPARTY\\X64\\Debug\\DirectXTexD64.lib")
#elif RELEASEMODE
#pragma comment(lib, "..\\TPARTY\\X64\\Release\\DirectXTex.lib")
#endif
#endif


class Texture : public Resources
{
private:
	DirectX::ScratchImage		image;
	ID3D11Resource*				texture;

	ID3D11RenderTargetView*		renderTargetView;
	ID3D11DepthStencilView*		depthStencilView;
	ID3D11ShaderResourceView*	shaderResourceView;

public:
	ID3D11RenderTargetView*		RTV()	{ return renderTargetView; }
	ID3D11DepthStencilView*		DSV()	{ return depthStencilView; }
	ID3D11ShaderResourceView*	SRV()	{ return shaderResourceView; }

public:
	size_t Width() 
	{
		return image.GetMetadata().width;
	}

	size_t Height() 
	{		
		return image.GetMetadata().height;
	}

public:
	void Update(Shader::SHADERTYPE _ShaderType, int _SetIndex);

public:	
	bool Load();
	

public:
	Texture();
	~Texture();
};

