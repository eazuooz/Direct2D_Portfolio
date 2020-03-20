#include "Blender.h"
#include "GraphicDevice.h"


Blender::Blender() : color(1.0f)
{
}


Blender::~Blender()
{
	if (nullptr != state)
	{
		state->Release();
		state = nullptr;
	}
}

bool Blender::Create()
{
#pragma region remark
	// 각자 할거냐 
	// false면 한개만 사용하겠다라는 이야기
	// 그중 0번만 사용하겠다.
	// 랜더타겟이 여러개라도 0번의 블랜드 방식만을 이용하겠다는 거지
	// 세팅 안해준 녀석들을 블랜딩을 안하겠다는 것은 아니다.
	//BOOL BlendEnable;
	//D3D11_BLEND SrcBlend;
	//D3D11_BLEND DestBlend;
	//D3D11_BLEND_OP BlendOp;
	//D3D11_BLEND SrcBlendAlpha;
	//D3D11_BLEND DestBlendAlpha;
	//D3D11_BLEND_OP BlendOpAlpha;
	//UINT8 RenderTargetWriteMask;
	//AlphaToCoverageEnable	FALSE
	//IndependentBlendEnable	FALSE
	//RenderTarget[0].BlendEnable	FALSE
	//RenderTarget[0].SrcBlend	D3D11_BLEND_ONE
	//RenderTarget[0].DestBlend	D3D11_BLEND_ZERO
	//RenderTarget[0].BlendOp	D3D11_BLEND_OP_ADD
	//RenderTarget[0].SrcBlendAlpha	D3D11_BLEND_ONE
	//RenderTarget[0].DestBlendAlpha	D3D11_BLEND_ZERO
	//RenderTarget[0].BlendOpAlpha	D3D11_BLEND_OP_ADD
	//RenderTarget[0].RenderTargetWriteMask	D3D11_COLOR_WRITE_ENABLE_ALL
	// https://docs.microsoft.com/ko-kr/windows/desktop/api/d3d11/ne-d3d11-d3d11_blend
	//typedef enum D3D11_BLEND {
	//	D3D11_BLEND_ZERO,
	//	D3D11_BLEND_ONE,
	//	D3D11_BLEND_SRC_COLOR,
	//	D3D11_BLEND_INV_SRC_COLOR,
	//	D3D11_BLEND_SRC_ALPHA,
	//	D3D11_BLEND_INV_SRC_ALPHA,
	//	D3D11_BLEND_DEST_ALPHA,
	//	D3D11_BLEND_INV_DEST_ALPHA,
	//	D3D11_BLEND_DEST_COLOR,
	//	D3D11_BLEND_INV_DEST_COLOR,
	//	D3D11_BLEND_SRC_ALPHA_SAT,
	//	D3D11_BLEND_BLEND_FACTOR,
	//	D3D11_BLEND_INV_BLEND_FACTOR,
	//	D3D11_BLEND_SRC1_COLOR,
	//	D3D11_BLEND_INV_SRC1_COLOR,
	//	D3D11_BLEND_SRC1_ALPHA,
	//	D3D11_BLEND_INV_SRC1_ALPHA
	//};
#pragma endregion

	desc.AlphaToCoverageEnable					= false;								//멀티샘플링에서 렌더타켓에 픽셀값을 설정할때의 알파값을 사용할지를 설정하는 값이다.
	desc.IndependentBlendEnable					= false;							//FALSE로 설정하면 렌더타겟 0의 설정만을 사용하여 렌더타겟 1~7까지의 설정은 무시 된다.
	desc.RenderTarget[0].BlendEnable			= true;								//픽셸 셰이더의 값과 렌더타겟의 값의 블렌드 처리를 할지 안할지 설정하며 렌더타겟마다 설정할수 있다.
	desc.RenderTarget[0].RenderTargetWriteMask	= D3D11_COLOR_WRITE_ENABLE_ALL;		//렌더타겟의 어던색을 쓸가를 지정한다. 
	desc.RenderTarget[0].BlendOp				= D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].SrcBlend				= D3D11_BLEND_SRC_ALPHA;
	desc.RenderTarget[0].DestBlend				= D3D11_BLEND_INV_SRC_ALPHA;
	desc.RenderTarget[0].BlendOpAlpha			= D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].SrcBlendAlpha			= D3D11_BLEND_ONE;
	desc.RenderTarget[0].DestBlendAlpha			= D3D11_BLEND_ZERO;

	//desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;		//렌더타겟의 어던색을 쓸가를 지정한다. 
	//desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	//desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	//desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	//desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	//desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	//desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

	return Create(desc);
}

bool Blender::Create(D3D11_BLEND _SrcBlend, D3D11_BLEND _DestBlend, D3D11_BLEND _SrcAlpha, D3D11_BLEND _DestAlpha)
{
	desc.AlphaToCoverageEnable = true;								//멀티샘플링에서 렌더타켓에 픽셀값을 설정할때의 알파값을 사용할지를 설정하는 값이다.
	desc.IndependentBlendEnable = false;							//FALSE로 설정하면 렌더타겟 0의 설정만을 사용하여 렌더타겟 1~7까지의 설정은 무시 된다.
	desc.RenderTarget[0].BlendEnable = true;								//픽셸 셰이더의 값과 렌더타겟의 값의 블렌드 처리를 할지 안할지 설정하며 렌더타겟마다 설정할수 있다.
	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;		//렌더타겟의 어던색을 쓸가를 지정한다. 
	desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].SrcBlend = _SrcBlend;
	desc.RenderTarget[0].DestBlend = _DestBlend;
	desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].SrcBlendAlpha = _SrcAlpha;
	desc.RenderTarget[0].DestBlendAlpha = _DestAlpha;

	//desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;		//렌더타겟의 어던색을 쓸가를 지정한다. 
	//desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	//desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	//desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	//desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	//desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	//desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

	return Create(desc);
}

void Blender::SetBlendOneAndOne()
{
	desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
	desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
}

bool Blender::Create(const D3D11_BLEND_DESC& _Desc)
{
	if (&desc != &_Desc)
	{
		desc = _Desc;
	}

	if (S_OK != GraphicDevice::Inst()->GetDXDevice()->CreateBlendState(&desc, &state))
	{
		BOOM;
		return false;
	}

	return true;
}

void Blender::Update()
{

	GraphicDevice::Inst()->GetDXContext()->OMSetBlendState(state, color.Arr, 0xffffffff);	//BlendFactor 는 D3D11_BLEND_FACTOR에서 사용할 상수값을 RGBA별로 설정한 배열이며
																							//SampleMask는 멀티샘플 렌더타겟에서 어떤 샘플로 Enable로 할까?(Msking)을 설정하는 값
}
