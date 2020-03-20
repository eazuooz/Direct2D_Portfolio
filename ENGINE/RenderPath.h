#pragma once
#include <vector>
#include "Sampler.h"
#include "Mesh.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Sprite.h"
#include "Blender.h"
#include "DepthStencil.h"
#include "Rasterizer.h"

class RenderPath
{
public:
	class SamplerInfo
	{
	public:
		Shader::SHADERTYPE _ShaderType;
		int _SetIndex;
		My_Ptr<Sampler> smp;
	};

	class TextureInfo
	{
	public:
		Shader::SHADERTYPE _ShaderType;
		int _SetIndex;
		My_Ptr<Texture> texture;
	};

public:
	My_Ptr<Blender> blender;
	My_Ptr<DepthStencil> depthStencil;
	My_Ptr<Rasterizer> rasterizer;
	My_Ptr<VtxShader>	vtxShader;
	My_Ptr<PxlShader>	pxlShader;
	std::vector<SamplerInfo>		samplerVector;
	std::vector<TextureInfo>		textureVector;
	
	
public:
	void BLEND(const wchar_t* _Name);
	void DSSTATE(const wchar_t* _Name);
	void RSSTATE(const wchar_t* _Name);
	void VTXSHADER(const wchar_t* _Name);
	void PIXSHADER(const wchar_t* _Name);
	void SMP(const wchar_t* _Name, Shader::SHADERTYPE _ShaderType, int _SetIndex);
	void TEX(const wchar_t* _Name, Shader::SHADERTYPE _ShaderType, int _SetIndex);

public:
	void Update();

public:
	RenderPath();
	~RenderPath();
};

