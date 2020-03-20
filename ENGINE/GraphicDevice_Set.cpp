#include "GraphicDevice.h"
#include <math.h>
#include <Path.h>
#include <Maths.h>
#include <iostream>
#include <algorithm>

#include "Sampler.h"
#include "ConstantBuffer.h"
#include "Mesh.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Blender.h"
#include "DepthStencil.h"
#include "Rasterizer.h"
#include "GraphicDebug.h"
#include "Font.h"

void GraphicDevice::BaseResInit()
{
	if (false == pathInit)
	{
		Path::root.ReplaceToParentPath();
		Path::root.MoveDirectory(L"_BIN");
		Path::CreatePath(L"SHADER");

		pathInit = true;
	}

	DeviceStateInit();
	MeshInfoInit();
	ShaderInfoInit();

	GraphicDebug::Init();

	baseInit = true;
}

void GraphicDevice::DeviceStateInit()
{
	Resources::Create<Font>(L"Silkscreen", L"Silkscreen");

	//***Default***//
	Resources::Create<Sampler>		(L"SAMPLER");
	Resources::Create<DepthStencil>	(L"DEPTHSTENCIL");
	Resources::Create<Rasterizer>	(L"RASTERIZER");
	Resources::Create<Blender>		(L"BLEND");
	Resources::Create<Blender>		(L"BLEND1TO1", D3D11_BLEND_ONE, D3D11_BLEND_ONE, D3D11_BLEND_ONE, D3D11_BLEND_ZERO);
	Resources::Create<ConstBuffer>	(L"MATRIXCONSTBUFFER", Shader::SHADERTYPE::SHTYPE_VS, (UINT)sizeof(Matrix), 0);
	Resources::Create<ConstBuffer>	(L"UVCONSTBUFFER", Shader::SHADERTYPE::SHTYPE_VS, (UINT)sizeof(Vector4), 1);
	
	
	Resources::Create<ConstBuffer>	(L"RECTCOLOR", Shader::SHADERTYPE::SHTYPE_PS, (UINT)sizeof(Vector4), 1);
	
	Resources::Create<ConstBuffer>	(L"BLENDGRADATION", Shader::SHADERTYPE::SHTYPE_PS, (UINT)sizeof(Vector4), 2);
	Resources::Create<ConstBuffer>	(L"HPBUFFER", Shader::SHADERTYPE::SHTYPE_PS, (UINT)sizeof(Vector4), 3);

	//Resources::Create<ConstBuffer>	(L"RECTCOLOR", Shader::SHADERTYPE::SHTYPE_PS, (UINT)sizeof(Vector4), 1);
	
	//***DebugState***//
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc = D3D11_DEPTH_STENCIL_DESC();	//지역변수 0으로 초기화해주어야한다 쓰레기값 들어감
	memset(&depthStencilDesc, NULL, sizeof(depthStencilDesc));
	depthStencilDesc.DepthEnable = TRUE;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.StencilEnable = FALSE;
	Resources::Create<DepthStencil>(L"DEBUGDEPTHSTENCIL", depthStencilDesc);


	D3D11_RASTERIZER_DESC rasterizerDesc;
	memset(&rasterizerDesc, 0, sizeof(rasterizerDesc));
	rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
	rasterizerDesc.MultisampleEnable = FALSE;
	rasterizerDesc.AntialiasedLineEnable = FALSE;
	Resources::Create<Rasterizer>(L"DEBUGRASTERIZER", rasterizerDesc);


	D3D11_BLEND_DESC blendDesc;
	blendDesc.AlphaToCoverageEnable = true;
	blendDesc.IndependentBlendEnable = false;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	blendDesc.RenderTarget[0].BlendEnable = true;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	Resources::Create<Blender>(L"DEBUGBLEND", blendDesc);
}

void GraphicDevice::MeshInfoInit()
{
	//***Default***//
	std::vector<Index::IDX32> idxArr;
	idxArr.push_back({ 0, 3, 2 });
	idxArr.push_back({ 0, 1, 3 });

	std::vector<Vertex::Vtx2D> vtxArr;
	vtxArr.resize(4);

	vtxArr[0].pos = Vector4(-0.5f, 0.5f, 0.5f, 1.0f);
	vtxArr[1].pos = Vector4(0.5f, 0.5f, 0.5f, 1.0f);
	vtxArr[2].pos = Vector4(-0.5f, -0.5f, 0.5f, 1.0f);
	vtxArr[3].pos = Vector4(0.5f, -0.5f, 0.5f, 1.0f);

	vtxArr[0].uv = Vector2(0.0f, 0.0f);
	vtxArr[1].uv = Vector2(1.0f, 0.0f);
	vtxArr[2].uv = Vector2(0.0f, 1.0f);
	vtxArr[3].uv = Vector2(1.0f, 1.0f);

	vtxArr[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	vtxArr[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
	vtxArr[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
	vtxArr[3].color = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
	Resources::Create<Mesh>(L"DTEXMESH", vtxArr, D3D11_USAGE_DYNAMIC, idxArr, D3D11_USAGE_DYNAMIC);

	//***Debug State***//
	std::vector<DWORD> debugRectIdxArr;
	debugRectIdxArr.push_back(0);
	debugRectIdxArr.push_back(1);
	debugRectIdxArr.push_back(2);
	debugRectIdxArr.push_back(3);
	debugRectIdxArr.push_back(0);

	std::vector<Vertex::VtxDebug> debugRectVtxArr;
	debugRectVtxArr.resize(4);

	debugRectVtxArr[0].pos = Vector4(-0.5f, 0.5f, 0.0f, 1.0f);
	debugRectVtxArr[1].pos = Vector4(0.5f, 0.5f, 0.0f, 1.0f);
	debugRectVtxArr[2].pos = Vector4(0.5f, -0.5f, 0.0f, 1.0f);
	debugRectVtxArr[3].pos = Vector4(-0.5f, -0.5f, 0.0f, 1.0f);

	Resources::Create<Mesh>(L"DEBUGRECTMESH", debugRectVtxArr, D3D11_USAGE_DYNAMIC, debugRectIdxArr, D3D11_USAGE_DYNAMIC);

	///CIRLCE

	std::vector<DWORD> debugCircleIdxArr;
	std::vector<Vertex::VtxDebug> debugCircleVtxArr;
	debugCircleVtxArr.resize(360);

	for (int angle = 0; angle < 360; ++angle)
	{
		debugCircleIdxArr.push_back(angle);
		
		float x = (cosf((float)angle * Constant::PI / 180.0f ) * 0.5f) ;
		float y = (sinf((float)angle * Constant::PI / 180.0f ) * 0.5f) ;

		Vector4 calPos = { x,y, 0.0f };

		debugCircleVtxArr[angle].pos = calPos;
	}
	debugCircleIdxArr.push_back(0);		

	Resources::Create<Mesh>(L"DEBUGSPHEREMESH", debugCircleVtxArr, D3D11_USAGE_DYNAMIC, debugCircleIdxArr, D3D11_USAGE_DYNAMIC);
}

void GraphicDevice::ShaderInfoInit()
{	
	My_Ptr<VtxShader> rectVtxShader = Resources::Load<VtxShader>(Path::FindPathToString(L"SHADER") + L"\\ColorRect.fx", 5, 0, "VS_COLORRECT");
	rectVtxShader->AddLayOut("POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0);
	rectVtxShader->AddLayOut("TEXCOORD", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0, 0);
	rectVtxShader->EndLayOut("COLOR", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0);
	Resources::Load<PxlShader>(Path::FindPathToString(L"SHADER") + L"\\ColorRect.fx", 5, 0, "PS_COLORRECT");
	//컬러 쉐이더 하나 만듬
		
	My_Ptr<VtxShader> textureVtxShader = Resources::Load<VtxShader>(Path::FindPathToString(L"SHADER") + L"\\TextureShader.fx", 5, 0, "VS_TEX");
	textureVtxShader->AddLayOut("POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0);
	textureVtxShader->AddLayOut("TEXCOORD", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0, 0);
	textureVtxShader->EndLayOut("COLOR", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0);
	Resources::Load<PxlShader>(Path::FindPathToString(L"SHADER") + L"\\TextureShader.fx", 5, 0, "PS_TEX");
		
	My_Ptr<VtxShader> debugVtxShader= Resources::Load<VtxShader>(Path::FindPathToString(L"SHADER") + L"\\DebugMesh.fx", 5, 0, "VS_DEBUGMESH");
	debugVtxShader->EndLayOut("POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0);
	Resources::Load<PxlShader>(Path::FindPathToString(L"SHADER") + L"\\DebugMesh.fx", 5, 0, "PS_DEBUGMESH");	



	//인스턴싱용 셰이더
	My_Ptr<VtxShader> instVtxShader = Resources::Load<VtxShader>(Path::FindPathToString(L"SHADER") + L"\\TextureShaderInst.fx", 5, 0, "VS_TEX");
	instVtxShader->AddLayOut("POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0);
	instVtxShader->AddLayOut("TEXCOORD", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0, 0);
	instVtxShader->AddLayOut("COLOR",	 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0);

	instVtxShader->AddLayOut("WVP", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 1, D3D11_INPUT_PER_INSTANCE_DATA);
	instVtxShader->AddLayOut("WVP", 1, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 1, D3D11_INPUT_PER_INSTANCE_DATA);
	instVtxShader->AddLayOut("WVP", 2, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 1, D3D11_INPUT_PER_INSTANCE_DATA);
	instVtxShader->AddLayOut("WVP", 3, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 1, D3D11_INPUT_PER_INSTANCE_DATA);
	instVtxShader->EndLayOut("SPRITEUV", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 1, D3D11_INPUT_PER_INSTANCE_DATA);


}