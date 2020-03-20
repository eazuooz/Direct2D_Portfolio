#include "RectRenderer.h"
#include "SpriteRenderer.h"
#include "Sampler.h"
#include "Mesh.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Sprite.h"
#include "Blender.h"
#include "DepthStencil.h"
#include "Rasterizer.h"


RectRenderer::RectRenderer()
{
}


RectRenderer::~RectRenderer()
{
}

void RectRenderer::Init()
{
	Renderer::Init();

	color = 0.0f;

	sampler			= Resources::Find<Sampler>		(L"SAMPLER");
	mesh			= Resources::Find<Mesh>			(L"DTEXMESH");
	constBuffer		= Resources::Find<ConstBuffer>	(L"MATRIXCONSTBUFFER");
	constColor		= Resources::Find<ConstBuffer>	(L"RECTCOLOR");
	vtxShader		= Resources::Find<VtxShader>	(L"ColorRect.fx");
	pxlShader		= Resources::Find<PxlShader>	(L"ColorRect.fx");
	blender			= Resources::Find<Blender>		(L"BLEND");
	depthStencil	= Resources::Find<DepthStencil>	(L"DEPTHSTENCIL");
	rasterizer		= Resources::Find<Rasterizer>	(L"RASTERIZER");
}

void RectRenderer::Render(const My_Ptr<Camera>& _Camera)
{	
	UpdateTransform();
	
	Matrix WorldMatrix = GetWorldMatrix();//GetActor()->GetTransform()->GetWorldMatrix();
	Matrix ViewMatrix = _Camera->GetViewMatrix();
	Matrix ProjectionMatrix = _Camera->GetProjectionMatrix();

	Matrix WVP = WorldMatrix * ViewMatrix * ProjectionMatrix;
	Matrix WVPT = WVP;

	WVPT.TransPose();

	// 최대한 덜 호출하는 것이 빠를것이다.

	constBuffer->DataSetting(&WVPT, sizeof(Matrix));
	constBuffer->Update();
	blender->Update();

	GraphicDevice::Inst()->GetDXContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	   
	constColor->DataSetting(&color, sizeof(color));
	constColor->Update();

	////


	/////
	vtxShader->Update();
	pxlShader->Update();


	sampler->Update(Shader::SHADERTYPE::SHTYPE_PS, 0);
	//sprite->Update(Shader::SHADERTYPE::SHTYPE_PS, 0);
	//Tex->Update(Shader::SHADERTYPE::SHTYPE_PS, 0);

	depthStencil->Update();
	rasterizer->Update();


	// 세팅이 다른부분만 세팅해준다.

	mesh->Update(0,0);
	mesh->Render(0, 0);
}