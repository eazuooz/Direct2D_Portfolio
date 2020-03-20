#include "PixelShader.h"



PxlShader::PxlShader() : Shader(Shader::SHADERTYPE::SHTYPE_PS), pixelShader(nullptr)
{
}


PxlShader::~PxlShader()
{
	if (nullptr != pixelShader)
	{
		pixelShader->Release();
		pixelShader = nullptr;
	}
}

bool PxlShader::Load(UINT _VH, UINT _VL, const char* _FuncName)
{
	versionHigh = _VH;
	versionLow = _VL;

	UINT flag = 0;

#ifdef _DEBUG 
	flag = D3D10_SHADER_DEBUG;
#endif

	sprintf_s(vtxBufferText, "ps_%d_%d", versionHigh, versionLow);


	// 여기단계에서부터 좀 관리를 해줘야 할것으로 보인다.
	if (
		S_OK != D3DCompileFromFile
		(
			file.GetFullPath(),
			nullptr,
			D3D_COMPILE_STANDARD_FILE_INCLUDE,
			_FuncName,
			vtxBufferText,
			flag, // 디버그모드일때 디버그 모드라는 것을 알려준다.
			0, // 뭔지도 모르겠음
			&blob,
			&errorBlob
		)
		)
	{
		std::string ErrorText = (char*)errorBlob->GetBufferPointer();

		Debug::Inst().ConsolePrint(ErrorText.c_str());
		BOOM;
		return false;
	}

	if (
		GraphicDevice::Inst()->GetDXDevice()->CreatePixelShader
		(
			blob->GetBufferPointer(),
			blob->GetBufferSize(),
			nullptr,
			&pixelShader
		)
		)
	{
		BOOM;
		return false;
	}

	return true;
}

void PxlShader::Update()
{
	if (nullptr != pixelShader)
	{
		GraphicDevice::Inst()->GetDXContext()->PSSetShader(pixelShader, nullptr, 0);
	}
}
