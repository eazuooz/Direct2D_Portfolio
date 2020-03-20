#pragma once
#include "Shader.h"

class VtxShader : public Shader
{
private:
	ID3D11VertexShader* vertexShader;

public:
	bool Load(UINT _VH, UINT _VL, const char* _FuncName);
	void Update() override;

private:
	class InputLayOut : public ControlBlock	//input layout 설정은 inputassembler에서 이루어진다
	{
	public:
		UINT offSet;
		std::vector<D3D11_INPUT_ELEMENT_DESC> inputElementDesc_Vector;

	public:
		InputLayOut() : offSet(0) {}
		~InputLayOut() 
		{

		}
	};
	

	ID3D11InputLayout* inputLayout;
	std::vector<My_Ptr<InputLayOut>> layOutVector;

public:
	void AddLayOut(
		const char* _SmtName,
		UINT _Index,
		DXGI_FORMAT _Format,
		UINT _InputSlot,
		UINT _IDSR,
		D3D11_INPUT_CLASSIFICATION _Input = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA
	);

	void EndLayOut(
		const char* _SmName,
		unsigned int _Index,
		DXGI_FORMAT _Format,
		unsigned int _inputSlot,
		unsigned int _IDSR,
		D3D11_INPUT_CLASSIFICATION _Input = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA
	);

public:
	VtxShader();
	~VtxShader();
};

