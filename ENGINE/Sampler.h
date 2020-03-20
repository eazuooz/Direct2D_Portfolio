#pragma once
#include "Resources.h"


#include "Shader.h"


class Sampler :	public Resources
{
private:
	D3D11_SAMPLER_DESC  samplerDesc;
	ID3D11SamplerState* state;

public:
	bool Create();
	bool Create(const D3D11_SAMPLER_DESC& _Desc);
	
	void Update(Shader::SHADERTYPE _ShaderType, int _SetIndex);

public:
	Sampler();
	~Sampler();
};

