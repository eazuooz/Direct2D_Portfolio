#pragma once
#include <SmartPtr.h>

#include "Resources.h"
#include "MeshData.h"
#include "GraphicDevice.h"

#include <vector>

class Mesh : public Resources
{
private:
	//이런 버텍스 버퍼와 인덱스 버퍼가
	//다이렉트의 인터페이스느 ㄴ대부분 그렇게 되어있다.
	//넣어주면 우리가 돌려받는 식으로 되어있다.
	//다이렉트 11부터는 대부분 버퍼 만들때 용도를 버택스 버퍼인지
	//인덱스 버퍼인지 지정해줘

	//버텍스 버퍼와 인덱스 버퍼이다.
	// 인터페이스가 추상클래스처럼 만들어지게 되었다.
	//하나의 다각형을 만들수 있는 버퍼

	// {100, 200, 300} {150, 250, 350} {250, 450, 350}
	// {200, 300, 300} {150, 250, 350} {250, 450, 350}
	// ID3D11Buffer* m_VB;

	// {0, 1, 2}
	// 그 다각형을 만들수 있는 점들을 그리는 순서에 대한 데이터
	// ID3D11Buffer* m_IB;

private:
	class VertexBuffer : public ControlBlock
	{
	public:
		ID3D11Buffer* vtxBuffer;
		D3D11_BUFFER_DESC vtxDesc;
		UINT vtxSize;	//점 하나가 x바이트의 크기이다.
		UINT vtxCount;	//점이 x 개다

		VertexBuffer() :vtxBuffer(nullptr) {}
		~VertexBuffer()
		{
			if (nullptr != vtxBuffer)
			{
				vtxBuffer->Release();
				vtxBuffer = nullptr;
			}
		}
	};

	class IndexBuffer : public ControlBlock
	{
	public:
		ID3D11Buffer* indexBuffer;
		D3D11_BUFFER_DESC indexDesc;
		DXGI_FORMAT indexBufferType;	//인덱스 버퍼 타입 자료형
		UINT indexSize;	//인덱스 버퍼 원소 1개의 사이즈.
		UINT indexCount;	//점이 x 개다 전체 그냥 정수가 몇개냐??

		IndexBuffer() :indexBuffer(nullptr) {}
		~IndexBuffer()
		{
			if (nullptr != indexBuffer)
			{
				indexBuffer->Release();
				indexBuffer = nullptr;
			}
		}
	};


private:
	//이 모드를 바꿔주면 점만 찍거나 뭐 여러가지 가능한데
	//그건 추후 설명
	D3D11_PRIMITIVE_TOPOLOGY drawMode;	//기본도형 위상구조 input assembler

	std::vector<My_Ptr<VertexBuffer>>	arrVB;
	std::vector<My_Ptr<IndexBuffer>>	arrIB;	//인덱스버퍼 없이도 사실은 그릴수 있다.

//public:
//	void DrawModeChange(D3D11_PRIMITIVE_TOPOLOGY _DrawMode)
//	{
//		drawMode = _DrawMode;
//	}
public:
	template<typename VT, typename IT>
	bool Create(std::vector<VT>& _VtxData, D3D11_USAGE _VtxUsage, std::vector<IT>& _IdxData, D3D11_USAGE _IdxUsage)
	{
		bool Check = false;

		Check = CreateVB((int)_VtxData.size(), VT::MemorySize(), _VtxUsage, &_VtxData[0]);

		if (false == Check)
		{
			BOOM;
			return false;
		}

		Check = CreateIB(IT::Format(), (int)_IdxData.size() * IT::MemCount(), IT::MemorySize(), _IdxUsage, &_IdxData[0]);

		if (false == Check)
		{
			BOOM;
			return false;
		}

		return true;
	}

	template<typename VBTYPE>
	bool Create(std::vector<VBTYPE>& _VtxData, D3D11_USAGE _VtxUsage, std::vector<DWORD>& _IdxData, D3D11_USAGE _IdxUsage)
	{
		bool Check = false;

		Check = CreateVB((int)_VtxData.size(), VBTYPE::MemorySize(), _VtxUsage, &_VtxData[0]);

		if (false == Check)
		{
			BOOM;
			return false;
		}

		Check = CreateIB(DXGI_FORMAT_R32_UINT, (int)_IdxData.size(), sizeof(DWORD), _IdxUsage, &_IdxData[0]);

		if (false == Check)
		{
			BOOM;
			return false;
		}

		return true;
	}

public:
	template<typename T>
	bool CreateVB(std::vector<T>& _Data, D3D11_USAGE _VtxUsage)
	{
		if (0 >= _Data.size())
		{
			BOOM;
		}

		return CreateVB((UINT)_Data.size(), T::MemorySize(), _VtxUsage, &_Data[0]);
	}
	bool CreateVB(UINT _VtxCount, UINT _VtxSize, D3D11_USAGE _VtxUsage, void* _Data);

	template<typename T>
	bool CreateIB(std::vector<T>& _Data, D3D11_USAGE _IdxUsage)
	{
		if (0 >= _Data.size())
		{
			BOOM;
		}

		return CreateIB(T::Format(), (UINT)_Data.size() * 3, T::MemorySize(), _IdxUsage, &_Data[0]);
	}

	bool CreateIB(std::vector<DWORD>& _Data, D3D11_USAGE _VtxUsage)
	{
		if (0 >= _Data.size())
		{
			BOOM;
		}

		return	CreateIB(DXGI_FORMAT_R32_UINT , (UINT)_Data.size(), sizeof(DWORD), _VtxUsage, &_Data[0]);
	}

	bool CreateIB(DXGI_FORMAT _IdxFormat, UINT _IdxCount, UINT _IdxSize, D3D11_USAGE _IdxUsage, void* _Data);

public:
	void Update(UINT _VtxIndex, UINT _IdxIndex);
	void Render(UINT _VtxIndex, UINT _IdxIndex);

	void RenderAuto();

public:
	Mesh();
	~Mesh();
};

