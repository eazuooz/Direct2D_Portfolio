#include "VertexShader.h"



VtxShader::VtxShader() : Shader(Shader::SHADERTYPE::SHTYPE_VS), vertexShader(nullptr)
{
	//inputLayout = new InputLayOut();
}


VtxShader::~VtxShader()
{
	if (nullptr != inputLayout)
	{
		inputLayout->Release();
		inputLayout = nullptr;
	}

	if (nullptr != vertexShader)
	{
		vertexShader->Release();
		vertexShader = nullptr;
	}
}


bool VtxShader::Load(UINT _VH, UINT _VL, const char* _FuncName)
{
	versionHigh = _VH;
	versionLow = _VL;

	UINT _Flag = D3D10_SHADER_DEBUG;

#ifdef _DEBUG 
	_Flag = D3D10_SHADER_DEBUG;
#endif

	sprintf_s(vtxBufferText, "vs_%d_%d", versionHigh, versionLow);


	// 여기단계에서부터 좀 관리를 해줘야 할것으로 보인다.
	if (S_OK != D3DCompileFromFile(file.GetFullPath(),nullptr,D3D_COMPILE_STANDARD_FILE_INCLUDE,_FuncName,vtxBufferText,_Flag, // 디버그모드일때 디버그 모드라는 것을 알려준다.
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
		GraphicDevice::Inst()->GetDXDevice()->CreateVertexShader
		(
			blob->GetBufferPointer(),
			blob->GetBufferSize(),
			nullptr,
			&vertexShader
		)
		)
	{
		BOOM;
		return false;
	}

	return true;


}

void VtxShader::Update()
{
	if (nullptr != inputLayout) //VertexShader::InputLayOut LayOut -> 멤버변수LayOut
	{
		GraphicDevice::Inst()->GetDXContext()->IASetInputLayout(inputLayout);
	}

	if (nullptr != vertexShader)
	{
		GraphicDevice::Inst()->GetDXContext()->VSSetShader(vertexShader, nullptr, 0);
	}
}


void VtxShader::AddLayOut(
	const char* _SmtName,
	UINT _Index,
	DXGI_FORMAT _Format,
	UINT _InputSlot,
	UINT _IDSR,
	D3D11_INPUT_CLASSIFICATION _Input 
)
{
	if (layOutVector.size() <= _InputSlot)
	{
		layOutVector.resize(_InputSlot + 1);
		layOutVector[_InputSlot] = new InputLayOut();
	}

	D3D11_INPUT_ELEMENT_DESC inputData;		//http://m.blog.daum.net/tjdgmlrnsk/11
	

	inputData.SemanticName = _SmtName;
	inputData.SemanticIndex = _Index;
	inputData.Format = _Format;
	inputData.InputSlot = _InputSlot;
	inputData.InputSlotClass = _Input;
	inputData.InstanceDataStepRate = _IDSR;
	inputData.AlignedByteOffset = layOutVector[_InputSlot]->offSet;

	UINT size = SizeOfFormat(inputData.Format);

	if (0 == size)
	{
		BOOM;
		return;
	}

	layOutVector[_InputSlot] ->offSet += size;
	layOutVector[_InputSlot] ->inputElementDesc_Vector.push_back(inputData);

}

void VtxShader::EndLayOut(
	const char* _SmName,
	unsigned int _Index,
	DXGI_FORMAT _Format,
	unsigned int _inputSlot,
	unsigned int _IDSR,
	D3D11_INPUT_CLASSIFICATION _Input 
)
{
	AddLayOut(_SmName, _Index, _Format, _inputSlot, _IDSR, _Input);


	std::vector<D3D11_INPUT_ELEMENT_DESC> AllLayOut;
	AllLayOut.reserve(layOutVector.size() * layOutVector[0]->inputElementDesc_Vector.size());

	//for (auto& layout : layOutVector)
	//{
	//	for (auto& inputElemDesc : layout->inputElementDesc_Vector)
	//	{
	//		AllLayOut.push_back(inputElemDesc);
	//	}
	//}

	for (size_t i = 0; i < layOutVector.size(); i++)
	{
		for (size_t j = 0; j < layOutVector[i]->inputElementDesc_Vector.size(); j++)
		{
			AllLayOut.push_back(layOutVector[i]->inputElementDesc_Vector[j]);
		}
	}

	if (S_OK != GraphicDevice::Inst()->GetDXDevice()->CreateInputLayout
			(&AllLayOut[0], (UINT)AllLayOut.size(), blob->GetBufferPointer(), blob->GetBufferSize(), &inputLayout))
	{
		BOOM;
		return;
	}
}
