#include "RenderPath.h"



RenderPath::RenderPath()
{
}


RenderPath::~RenderPath()
{
}

void RenderPath::BLEND(const wchar_t* _Name)
{
	blender = Resources::Find<Blender>(_Name);

	if (nullptr == blender)
	{
		BOOM;
	}
}
void RenderPath::DSSTATE(const wchar_t* _Name)
{
	depthStencil = Resources::Find<DepthStencil>(_Name);

	if (nullptr == depthStencil)
	{
		BOOM;
	}
}
void RenderPath::RSSTATE(const wchar_t* _Name)
{
	rasterizer = Resources::Find<Rasterizer>(_Name);

	if (nullptr == rasterizer)
	{
		BOOM;
	}
}
void RenderPath::VTXSHADER(const wchar_t* _Name)
{
	 vtxShader = Resources::Find<VtxShader>(_Name);

	if (nullptr == vtxShader)
	{
		BOOM;
	}
}
void RenderPath::PIXSHADER(const wchar_t* _Name)
{
	pxlShader = Resources::Find<PxlShader>(_Name);

	if (nullptr == pxlShader)
	{
		BOOM;
	}
}
void RenderPath::SMP(const wchar_t* _Name, Shader::SHADERTYPE _ShaderType, int _SetIndex)
{
	My_Ptr<Sampler> sampler = Resources::Find<Sampler>(_Name);

	if (nullptr == sampler)
	{
		BOOM;
	}

	SamplerInfo Data;
	Data.smp = sampler;
	Data._SetIndex = _SetIndex;
	Data._ShaderType = _ShaderType;

	samplerVector.push_back(Data);
}
void RenderPath::TEX(const wchar_t* _Name, Shader::SHADERTYPE _ShaderType, int _SetIndex)
{
	My_Ptr<Texture> texture = Resources::Find<Texture>(_Name);

	if (nullptr == texture)
	{
		BOOM;
	}

	TextureInfo Data;
	Data.texture = texture;
	Data._SetIndex = _SetIndex;
	Data._ShaderType = _ShaderType;

	textureVector.push_back(Data);
}


void RenderPath::Update()
{
	if (nullptr != blender)
	{
		blender->Update();
	}

	if (nullptr != depthStencil)
	{
		depthStencil->Update();
	}

	if (nullptr != rasterizer)
	{
		rasterizer->Update();
	}

	if (nullptr != vtxShader)
	{
		vtxShader->Update();
	}

	if (nullptr != pxlShader)
	{
		pxlShader->Update();
	}

	if (0 != samplerVector.size())
	{
		for (size_t i = 0; i < samplerVector.size(); i++)
		{
			samplerVector[i].smp->Update(samplerVector[i]._ShaderType, samplerVector[i]._SetIndex);
		}
	}

	if (0 != textureVector.size())
	{
		for (size_t i = 0; i < textureVector.size(); i++)
		{
			textureVector[i].texture->Update(textureVector[i]._ShaderType, textureVector[i]._SetIndex);
		}
	}
}