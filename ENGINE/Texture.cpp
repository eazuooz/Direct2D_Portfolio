#include "Texture.h"
#include <File.h>


Texture::Texture() :renderTargetView(nullptr), depthStencilView(nullptr), shaderResourceView(nullptr), texture(nullptr)
{
	
}


Texture::~Texture()
{
	image.Release();

	// 텍스처가 만들어내고 나머지를 뽑아냈으므로 항상 안전하려면
	// 역순으로
	if (nullptr != renderTargetView)	{ renderTargetView->Release();		renderTargetView	= nullptr; }
	if (nullptr != depthStencilView)	{ depthStencilView->Release();		depthStencilView	= nullptr; }
	if (nullptr != shaderResourceView)	{ shaderResourceView->Release();	shaderResourceView	= nullptr; }
	if (nullptr != texture)				{ texture->Release();				texture				= nullptr; }
}
void Texture::Update(Shader::SHADERTYPE _ShaderType, int _SetIndex)
{
	if (nullptr == shaderResourceView)
	{
		BOOM;
	}

	// _SetIndex 세팅되는 위치
	// 그 위치부터 연속으로 몇개 세팅할래????

	switch (_ShaderType)
	{
	case Shader::SHTYPE_VS:
		GraphicDevice::Inst()->GetDXContext()->VSSetShaderResources(_SetIndex, 1, &shaderResourceView);
		break;
	case Shader::SHTYPE_HS:
		GraphicDevice::Inst()->GetDXContext()->HSSetShaderResources(_SetIndex, 1, &shaderResourceView);
		break;
	case Shader::SHTYPE_DS:
		GraphicDevice::Inst()->GetDXContext()->DSSetShaderResources(_SetIndex, 1, &shaderResourceView);
		break;
	case Shader::SHTYPE_GS:
		GraphicDevice::Inst()->GetDXContext()->GSSetShaderResources(_SetIndex, 1, &shaderResourceView);
		break;
	case Shader::SHTYPE_PS:
		GraphicDevice::Inst()->GetDXContext()->PSSetShaderResources(_SetIndex, 1, &shaderResourceView);
		break;
	default:
		BOOM;
		break;
	}
}



bool Texture::Load()
{
	if (nullptr == GraphicDevice::Inst()->GetDXDevice())
	{
		BOOM;
		return false;
	}

	if (true == file.CheckExtension(L"DDs") || file.CheckExtension(L"dds"))
	{
		if (S_OK != DirectX::LoadFromDDSFile(file.GetFullPathString().c_str(), DirectX::DDS_FLAGS_NONE, nullptr, image))
		{
			BOOM;
			return false;
		}
	}
	else if (true == file.CheckExtension(L"TGA") || file.CheckExtension(L"tga"))
	{
		if (S_OK != DirectX::LoadFromTGAFile(file.GetFullPathString().c_str(), nullptr, image))
		{
			BOOM;
			return false;
		}
	}
	else // if (true == m_File.IsExt(L"Png") || m_File.IsExt(L"png"))
	{
		if (S_OK != DirectX::LoadFromWICFile(file.GetFullPathString().c_str()
			, DirectX::WIC_FLAGS_NONE, nullptr, image))
		{
			BOOM;
			return false;
		}
	}

	if (0 == image.GetImageCount())
	{
		BOOM;
		return false;
	}

	
// 쉐이더에 세팅해줄수 있는 권한을 얻어온다.
	if (S_OK != DirectX::CreateShaderResourceView(GraphicDevice::Inst()->GetDXDevice()
		, image.GetImages()
		, image.GetImageCount()
		, image.GetMetadata()
		, &shaderResourceView))
	{
		BOOM;
		return false;
	}

	return true;
}