#include "FontRenderer.h"
#include <MyTime.h>
#include "GameWindow.h"

#include "Camera.h"
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


FontRenderer::FontRenderer() : font(nullptr), addPos({0.0f, 0.0f, 0.0f, 0.0f})
{
}


FontRenderer::~FontRenderer()
{
}

void FontRenderer::Init()
{
	Renderer::Init();
	font = Resources::Find<Font>(L"Silkscreen");
}

void FontRenderer::Render(const My_Ptr<Camera>& _CAM)
{
	UpdateTransform();

	Matrix W = GetWorldMatrix();
	Vector4 CameraWorldPos = _CAM->GetTransform()->GetLocalPosition();
	CameraWorldPos.z = 0.0f;
	CameraWorldPos.w = 1.0f;
	Vector4 TextWorldPos = { W._30, W._31, 0.0f, 1.0f };
	Vector4 TextPos;
	
	
	TextPos.x = (GameWindow::Inst()->GetWindowSize().x / 2.0f) - ((CameraWorldPos.x - TextWorldPos.x) * (GameWindow::Inst()->GetWindowSize().y / 4.8f));
	TextPos.y = (GameWindow::Inst()->GetWindowSize().y / 2.0f) + ((CameraWorldPos.y - TextWorldPos.y) * (GameWindow::Inst()->GetWindowSize().y / 4.8f));
	TextPos.z = 90.0f;

	TextPos += addPos;
	//DRAW UI 렌더링 파이프라인을 자기맘대로 바꾸어쓴다.
	font->DrawUI(text.text.c_str(), text.size, TextPos, text.color, FW1_CENTER);
}

void FontRenderer::Update()
{

}

void FontRenderer::SetFont(std::wstring _FontName)
{
	text.fontName = _FontName;
	font = Resources::Find<Font>(_FontName);
}

void FontRenderer::SetColorAlpha(float _Value)
{
	text.color.w = _Value;
}

void FontRenderer::SetColorAlphaMul(float _Value)
{
	text.color.w *= _Value;
}

