#include "EffectSpriteRenderer.h"
#include <MyTime.h>


#include "Sampler.h"
#include "Mesh.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Sprite.h"
#include "Blender.h"
#include "DepthStencil.h"
#include "Rasterizer.h"
#include "RenderManager.h"





EffectSpriteRenderer::EffectSpriteRenderer() : mesh(nullptr), constBuffer(nullptr),
constBuffer_UV(nullptr), vtxShader(nullptr), pxlShader(nullptr), sampler(nullptr),
OneAndOneBlender(false), dir(DIRECTION::LEFT), isRotate(true), alphaValue(1.0f), alphaGradation(false), hpRate(1.0f)
{
}


EffectSpriteRenderer::~EffectSpriteRenderer()
{
}


void EffectSpriteRenderer::Init()
{
	//RenderPath newPath;
	//RenderManager::CreateInstancing<SpriteInstData>(L"SpriteInst", L"DTEXMESH", newPath);

	Renderer::Init();

	sampler = Resources::Find<Sampler>(L"SAMPLER");
	mesh = Resources::Find<Mesh>(L"DTEXMESH");


	vtxShader = Resources::Find<VtxShader>(L"TextureShader.fx");
	pxlShader = Resources::Find<PxlShader>(L"TextureShader.fx");

	constBuffer = Resources::Find<ConstBuffer>(L"MATRIXCONSTBUFFER");
	constBuffer_UV = Resources::Find<ConstBuffer>(L"UVCONSTBUFFER");
	constBuffer_Blender = Resources::Find<ConstBuffer>(L"BLENDGRADATION");
	constBuffer_Hp = Resources::Find<ConstBuffer>(L"HPBUFFER");


	blender = Resources::Find<Blender>(L"BLEND");

	depthStencil = Resources::Find<DepthStencil>(L"DEPTHSTENCIL");
	rasterizer = Resources::Find<Rasterizer>(L"RASTERIZER");



}

void EffectSpriteRenderer::Render(const My_Ptr<Camera>& _Camera)
{
	UpdateTransform();
	//UpdateTransforms();

	Matrix WorldMatrix = GetWorldMatrix();//GetActor()->GetTransform()->GetWorldMatrix();
	Matrix ViewMatrix = _Camera->GetViewMatrix();
	Matrix ProjectionMatrix = _Camera->GetProjectionMatrix();

	Matrix WVP = WorldMatrix * ViewMatrix * ProjectionMatrix;
	Matrix WVPT = WVP;

	if (DIRECTION::RIGHT == dir && true == isRotate)	//방향에따른 y축회전
	{
		// 레스터라이저에 뭐가 있냐?
		WVPT.Arr2D[0][0] = -WVPT.Arr2D[0][0];
	}
	WVPT.Arr2D[3][2] += -0.0000001f;
	//rasterizer


	WVPT.TransPose();

	// 최대한 덜 호출하는 것이 빠를것이다.
	constBuffer->DataSetting(&WVPT, sizeof(Matrix));
	constBuffer->Update();

	//blender->SetColor({0.0f, 0.0f, 0.0f, 0.0f});
	blender->Update();

	GraphicDevice::Inst()->GetDXContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	textureUV = sprite->GetCutData(spriteIndex);
	constBuffer_UV->DataSetting(&textureUV, sizeof(textureUV));
	constBuffer_UV->Update();



	if (true == alphaGradation)
	{
		alphaValue.Arr[3] -= 0.2f * Time::DeltaTime();

		constBuffer_Blender->DataSetting(&alphaValue, sizeof(alphaValue));
		constBuffer_Blender->Update();
	}
	else
	{
		alphaValue.Arr[3] = 1.0f;

		constBuffer_Blender->DataSetting(&alphaValue, sizeof(alphaValue));
		constBuffer_Blender->Update();
	}


	constBuffer_Hp->DataSetting(&hpRate, sizeof(hpRate));
	constBuffer_Hp->Update();

	vtxShader->Update();
	pxlShader->Update();

	sampler->Update(Shader::SHADERTYPE::SHTYPE_PS, 0);
	sprite->Update(Shader::SHADERTYPE::SHTYPE_PS, 0);
	//Tex->Update(Shader::SHADERTYPE::SHTYPE_PS, 0);

	depthStencil->Update();
	rasterizer->Update();

	// 세팅이 다른부분만 세팅해준다.
	mesh->Update(0, 0);
	mesh->Render(0, 0);

	//UpdateTransform();

	//Matrix WorldMatrix = GetWorldMatrix();//GetActor()->GetTransform()->GetWorldMatrix();
	//Matrix ViewMatrix = _Camera->GetViewMatrix();
	//Matrix ProjectionMatrix = _Camera->GetProjectionMatrix();

	//Matrix WVP = WorldMatrix * ViewMatrix * ProjectionMatrix;
	//Matrix WVPT = WVP;

	//WVPT.TransPose();

	//// 최대한 덜 호출하는 것이 빠를것이다.

	//constBuffer->DataSetting(&WVPT, sizeof(Matrix));
	//constBuffer->Update();
	//blender->Update();

	//GraphicDevice::Inst()->GetDXContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//constColor->DataSetting(&color, sizeof(color));
	//constColor->Update();

	//////


	///////
	//vtxShader->Update();
	//pxlShader->Update();


	//sampler->Update(Shader::SHADERTYPE::SHTYPE_PS, 0);
	////sprite->Update(Shader::SHADERTYPE::SHTYPE_PS, 0);
	////Tex->Update(Shader::SHADERTYPE::SHTYPE_PS, 0);

	//depthStencil->Update();
	//rasterizer->Update();


	//// 세팅이 다른부분만 세팅해준다.

	//mesh->Update(0, 0);
	//mesh->Render(0, 0);
}

void EffectSpriteRenderer::SetSprite(const wchar_t* _SpriteName, int _SpriteIndex)
{
	spriteIndex = _SpriteIndex;
	sprite = Resources::Find<Sprite>(_SpriteName);
}

void EffectSpriteRenderer::SetBlender(std::wstring _Name)
{
	blender = Resources::Find<Blender>(L"BLEND1TO1");
}
