#pragma once
#include "GraphicDevice.h"
#include "Shader.h"



class ConstBuffer : public Resources	//Vertex shader or Pixel Shader
{
private:
	Shader::SHADERTYPE			shaderType;
	UINT						reg;			//레지스터 넘버
	UINT						bufferSize;
	D3D11_SUBRESOURCE_DATA		subResouceData;
	D3D11_MAPPED_SUBRESOURCE	mapSubResource;
	D3D11_BUFFER_DESC			bufferDesc;
	ID3D11Buffer*				constantBuffer;

	void* Data;
	void(ConstBuffer::*SHUpdateFunc)();

public:
	bool Create(Shader::SHADERTYPE _SHType, UINT _Byte, UINT _Reg);

public:
	void DataSetting(void* _Data, UINT _Size);
	void Update();

private:
	void VSUpdate();
	void HSUpdate();
	void DSUpdate();
	void GSUpdate();
	void PSUpdate();

public:
	ConstBuffer();
	~ConstBuffer();
};

