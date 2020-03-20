#include "GraphicDebug.h"

#include "Mesh.h"
#include "ConstantBuffer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Sprite.h"
#include "Blender.h"
#include "DepthStencil.h"
#include "Rasterizer.h"


#pragma region static initialize
std::vector<GraphicDebug::FontDrawInfo> GraphicDebug::debugRenderText;
std::vector<GraphicDebug::ShapeInfo> GraphicDebug::debugRender_Vector;
int GraphicDebug::shapeCount = 0;
int GraphicDebug::textCount = 0;
Vector4 GraphicDebug::startTextPos;

bool GraphicDebug::isInit = false;
bool GraphicDebug::isDebug = false;

My_Ptr<Mesh>			GraphicDebug::mesh[SHAPETYPE::MAX]  = { nullptr };
My_Ptr<ConstBuffer>		GraphicDebug::constBuffer			=	nullptr;
My_Ptr<ConstBuffer>		GraphicDebug::colorConstBuffer		=	nullptr;
My_Ptr<VtxShader>		GraphicDebug::vtxShader				=	nullptr;
My_Ptr<PxlShader>		GraphicDebug::pxlShader				=	nullptr;
My_Ptr<Blender>			GraphicDebug::blender				=	nullptr;
My_Ptr<DepthStencil>	GraphicDebug::depthStencil			=	nullptr;
My_Ptr<Rasterizer>		GraphicDebug::rasterizer			=	nullptr;
My_Ptr<Font>			GraphicDebug::font					=	nullptr;
#pragma endregion


GraphicDebug::GraphicDebug()
{
}


GraphicDebug::~GraphicDebug()
{
}

void GraphicDebug::Init()
{
	if (true == isInit)
	{
		return;
	}

	mesh[SHAPETYPE::SQUARE]			= Resources::Find<Mesh>(L"DEBUGRECTMESH");
	mesh[SHAPETYPE::SPHERE]			= Resources::Find<Mesh>(L"DEBUGSPHEREMESH");

	constBuffer		= Resources::Find<ConstBuffer>	(L"MATRIXCONSTBUFFER");
	colorConstBuffer= Resources::Find<ConstBuffer>	(L"RECTCOLOR");
	vtxShader		= Resources::Find<VtxShader>	(L"DebugMesh.fx");
	pxlShader		= Resources::Find<PxlShader>	(L"DebugMesh.fx");
	blender			= Resources::Find<Blender>		(L"DEBUGBLEND");
	depthStencil	= Resources::Find<DepthStencil>	(L"DEBUGDEPTHSTENCIL");
	rasterizer		= Resources::Find<Rasterizer>	(L"DEBUGRASTERIZER");

	debugRender_Vector.resize(1000);
	debugRenderText.resize(1000);

	isInit = true;
}

// 전용 매쉬들 만든다.
void GraphicDebug::DebugRender()
{
	for (int i = 0; i < shapeCount; ++i)
	{
		Matrix worldMatrix = debugRender_Vector[i].world * debugRender_Vector[i].view * debugRender_Vector[i].projection;

		worldMatrix.TransPose();

		// 최대한 덜 호출하는 것이 빠를것이다.
		constBuffer->DataSetting(&worldMatrix, sizeof(Matrix));
		constBuffer->Update();

		debugRender_Vector[i].color = { 1.0f, 0.0f, 1.0f, 1.0f };
		colorConstBuffer->DataSetting(&debugRender_Vector[i].color, sizeof(debugRender_Vector[i].color));
		colorConstBuffer->Update();

		blender->Update();
		GraphicDevice::Inst()->GetDXContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
		
		vtxShader->Update();
		pxlShader->Update();
		
		depthStencil->Update();
		rasterizer->Update();

		mesh[debugRender_Vector[i].type]->Update(0, 0);
		mesh[debugRender_Vector[i].type]->Render(0, 0);
	}
	shapeCount = 0;

	for (int i = 0; i < textCount; ++i)
	{
		My_Ptr<Font> font = Resources::Find<Font>(debugRenderText[i].fontName);

		if (nullptr == font)
		{
			BOOM;
			continue;
		}

		font->DrawUI(debugRenderText[i].text.c_str(), 20.0f, startTextPos + (Vector4::UP * 20.0f *(float)i), debugRenderText[i].color);
	}

	textCount = 0;
}

// 카메라 넣어줘야 하는경우.
void GraphicDebug::DrawSquare(My_Ptr<Camera> _Cam, Matrix _WorldMatrix)
{
	debugRender_Vector[shapeCount].type			= SHAPETYPE::SQUARE;
	debugRender_Vector[shapeCount].world		= _WorldMatrix;
	debugRender_Vector[shapeCount].view			= _Cam->GetViewMatrix();
	debugRender_Vector[shapeCount].projection	= _Cam->GetProjectionMatrix();

	++shapeCount;
}
void GraphicDebug::DrawSquare(My_Ptr<Camera> _Cam, Vector4 _Pos, Vector4 _Rot, Vector4 _Scale, Vector4 _Color)
{
	++shapeCount;
}
void GraphicDebug::DrawSquare(Vector4 _Pos, Vector4 _Rot, Vector4 _Scale, Vector4 _Color)
{
	++shapeCount;
}


void GraphicDebug::DrawSphere(My_Ptr<Camera> _Cam, Matrix _WorldMatrix)
{
	debugRender_Vector[shapeCount].type			= SHAPETYPE::SPHERE;
	debugRender_Vector[shapeCount].world		= _WorldMatrix;
	//debugRender_Vector[shapeCount].world.Arr2D[0][0] = 0.15f;
	debugRender_Vector[shapeCount].view			= _Cam->GetViewMatrix();
	debugRender_Vector[shapeCount].projection	= _Cam->GetProjectionMatrix();

	++shapeCount;
}
void GraphicDebug::DrawSphere(My_Ptr<Camera> _Cam, Vector4 _Pos, Vector4 _Rot, Vector4 _Scale, Vector4 _Color)
{
	++shapeCount;
}
void GraphicDebug::DrawSphere(Vector4 _Pos, Vector4 _Rot, Vector4 _Scale, Vector4 _Color)
{
	++shapeCount;
}



void GraphicDebug::DrawFontUI(const wchar_t* _Text, Vector4 _Color)
{
	debugRenderText[textCount].fontName = L"Silkscreen";
	debugRenderText[textCount].text = _Text;
	debugRenderText[textCount].color = _Color;
	++textCount;
}