#include "DepthStencil.h"



DepthStencil::DepthStencil()
{
}


DepthStencil::~DepthStencil()
{
	if (nullptr != state)
	{
		state->Release();
		state = nullptr;
	}
}


bool DepthStencil::Create()
{
	// 뎁스를 사용한다.
	// 2D게임이면
	// 먼저 그려지는 놈이 뒤에 오는 놈이다.
	desc.DepthEnable = TRUE;

	// 그리고 깊이값을 비교할때
	// 픽셀쉐이더에서 색깔 처리 해야한다고 말해줘야 하는데. 
	// 새로운 픽셀의 깊이값이
	// 기존의 깊이값보다 작을때.

	// 2D게임이면
	// 먼저 그려지는 놈이 뒤에 오는 놈이다.
	desc.DepthFunc = D3D11_COMPARISON_LESS;

	// 제로면 검출만 하고 
	// 덮어 씌우지는 않는다. 
	// 랜더링 순서에 의해서만 
	// Z값을 완전히 
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;


	//BOOL DepthEnable;
	//D3D11_DEPTH_WRITE_MASK DepthWriteMask;
	//D3D11_COMPARISON_FUNC DepthFunc;
	// BOOL StencilEnable;
	// UINT8 StencilReadMask;
	// UINT8 StencilWriteMask;
	// D3D11_DEPTH_STENCILOP_DESC FrontFace;
	// D3D11_DEPTH_STENCILOP_DESC BackFace;

	//typedef struct D3D11_DEPTH_STENCILOP_DESC
	//{
	//	D3D11_STENCIL_OP StencilFailOp;
	//	D3D11_STENCIL_OP StencilDepthFailOp;
	//	D3D11_STENCIL_OP StencilPassOp;
	//	D3D11_COMPARISON_FUNC StencilFunc;
	//} 	D3D11_DEPTH_STENCILOP_DESC;

	//D3D11_STENCIL_OP_KEEP = 1,
	//D3D11_STENCIL_OP_ZERO = 2,
	//D3D11_STENCIL_OP_REPLACE = 3,
	//D3D11_STENCIL_OP_INCR_SAT = 4,
	//D3D11_STENCIL_OP_DECR_SAT = 5,
	//D3D11_STENCIL_OP_INVERT = 6,
	//D3D11_STENCIL_OP_INCR = 7,
	//D3D11_STENCIL_OP_DECR = 8


	// 볼륨메시.
	desc.StencilEnable = FALSE;

	return Create(desc);
}

bool DepthStencil::Create(const D3D11_DEPTH_STENCIL_DESC& _Desc)
{
	if (&desc != &_Desc)
	{
		desc = _Desc;
	}

	if (S_OK != GraphicDevice::Inst()->GetDXDevice()->CreateDepthStencilState(&desc, &state))
	{
		BOOM;
		return false;
	}

	return true;
}

void DepthStencil::Update()
{
	GraphicDevice::Inst()->GetDXContext()->OMSetDepthStencilState(state, 0);
}
