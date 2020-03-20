#include "ConstantBuffer.h"



ConstBuffer::ConstBuffer() : constantBuffer(nullptr), Data(nullptr), reg(0)
{
}


ConstBuffer::~ConstBuffer()
{
	if (nullptr != Data)
	{
		delete[](char*)Data;
		Data = nullptr;
	}

	if (nullptr != constantBuffer)
	{
		constantBuffer->Release();
		constantBuffer = nullptr;
	}
}

bool ConstBuffer::Create(Shader::SHADERTYPE _SHType, UINT _Byte, UINT _Reg)
{
	reg = _Reg;

	switch (_SHType)
	{
	case Shader::SHTYPE_VS:
		SHUpdateFunc = &ConstBuffer::VSUpdate;
		break;
	case Shader::SHTYPE_HS:
		SHUpdateFunc = &ConstBuffer::HSUpdate;
		break;
	case Shader::SHTYPE_DS:
		SHUpdateFunc = &ConstBuffer::DSUpdate;
		break;
	case Shader::SHTYPE_GS:
		SHUpdateFunc = &ConstBuffer::GSUpdate;
		break;
	case Shader::SHTYPE_PS:
		SHUpdateFunc = &ConstBuffer::PSUpdate;
		break;
	default:
		break;
	}

	//데이터를 동적할당으로 가지고 있는다.
	bufferDesc.ByteWidth = _Byte;
	Data = new char[_Byte];
	//이거 그래픽카드가 관리할까 아니면 CPU에 할당할까 말까 이런것들
	//그리고  관리할때 수정할수 있게 할꺼야??

	bufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
	if (bufferDesc.Usage == D3D11_USAGE::D3D11_USAGE_DYNAMIC)
	{
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}

	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	subResouceData.pSysMem = Data;
	mapSubResource.pData = Data;

	if (S_OK != GraphicDevice::Inst()->GetDXDevice()->CreateBuffer(&bufferDesc, &subResouceData, &constantBuffer))
	{
		BOOM;
		return false;
	}

	return true;
}

void ConstBuffer::DataSetting(void* _Data, UINT _Size)
{
	//존재하는 것이 디바이스 이기 떄문에
	//컨텍스트에게 요청해야 한다.
	//잠깐 디바이스에게 멈추고 내 데이터를 세팅해줘
	//이 세팅한 행렬을 넣어줘라/
	GraphicDevice::Inst()->GetDXContext()->Map(constantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapSubResource);
	memcpy_s(mapSubResource.pData, bufferDesc.ByteWidth, _Data, _Size);	//헹렬 세팅
	GraphicDevice::Inst()->GetDXContext()->Unmap(constantBuffer, 0);
}

void ConstBuffer::Update()
{
		

	(this->*SHUpdateFunc)();
}

void ConstBuffer::VSUpdate() { GraphicDevice::Inst()->GetDXContext()->VSSetConstantBuffers(reg, 1, &constantBuffer); }
void ConstBuffer::HSUpdate() { GraphicDevice::Inst()->GetDXContext()->HSSetConstantBuffers(reg, 1, &constantBuffer); }
void ConstBuffer::DSUpdate() { GraphicDevice::Inst()->GetDXContext()->DSSetConstantBuffers(reg, 1, &constantBuffer); }
void ConstBuffer::GSUpdate() { GraphicDevice::Inst()->GetDXContext()->GSSetConstantBuffers(reg, 1, &constantBuffer); }
void ConstBuffer::PSUpdate() { GraphicDevice::Inst()->GetDXContext()->PSSetConstantBuffers(reg, 1, &constantBuffer); }