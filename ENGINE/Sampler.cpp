#include "Sampler.h"



Sampler::Sampler() : state(nullptr)
{

}


Sampler::~Sampler()
{
	if (nullptr != state)
	{
		state->Release();
		state = nullptr;
	}
}

bool Sampler::Create()
{
	//Desc.Filter = D3D11_FILTER::D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT;
	//Desc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_LINEAR;

	samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_POINT;
	//samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	// D3D11_FILTER::D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR

	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;

	memcpy_s(samplerDesc.BorderColor, sizeof(Vector4), &Vector4::RED, sizeof(Vector4));

	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	samplerDesc.MaxAnisotropy = 0;
	samplerDesc.MinLOD = -FLT_MAX;
	samplerDesc.MaxLOD =  FLT_MAX;

	samplerDesc.MipLODBias = 1.0f;

	return Create(samplerDesc);
}

bool Sampler::Create(const D3D11_SAMPLER_DESC& _Desc)
{
	if (&samplerDesc != &_Desc)
	{
		samplerDesc = _Desc;
	}

	if (S_OK != GraphicDevice::Inst()->GetDXDevice()->CreateSamplerState(&samplerDesc, &state))
	{
		BOOM;
		return false;
	}

	return true;
}

void Sampler::Update(Shader::SHADERTYPE _ShaderType, int _SetIndex)
{
	if (nullptr == state)
	{
		BOOM;
	}

	// _SetIndex 세팅되는 위치
	// 그 위치부터 연속으로 몇개 세팅할래????

	switch (_ShaderType)
	{
	case Shader::SHTYPE_VS:
		GraphicDevice::Inst()->GetDXContext()->VSSetSamplers(_SetIndex, 1, &state);
		break;
	case Shader::SHTYPE_HS:
		GraphicDevice::Inst()->GetDXContext()->HSSetSamplers(_SetIndex, 1, &state);
		break;
	case Shader::SHTYPE_DS:
		GraphicDevice::Inst()->GetDXContext()->DSSetSamplers(_SetIndex, 1, &state);
		break;
	case Shader::SHTYPE_GS:
		GraphicDevice::Inst()->GetDXContext()->GSSetSamplers(_SetIndex, 1, &state);
		break;
	case Shader::SHTYPE_PS:
		GraphicDevice::Inst()->GetDXContext()->PSSetSamplers(_SetIndex, 1, &state);
		break;
	default:
		BOOM;
		break;
	}
}