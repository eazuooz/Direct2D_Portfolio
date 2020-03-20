#include "Mesh.h"



Mesh::Mesh() : drawMode(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
{
}


Mesh::~Mesh()
{
}

bool Mesh::CreateVB(UINT _VtxCount, UINT _VtxSize, D3D11_USAGE _VtxUsage, void* _Data)
{
	arrVB.resize(arrVB.size() + 1);					//배열의 카파시티를 늘리되 원소는 늘어나지 않는게 리저브
	VertexBuffer* newVB = new VertexBuffer();		//배열을 늘리는것이 아니라 원소 그자체를 늘리는것이 리사이즈
	arrVB[arrVB.size() - 1] = newVB;

	newVB->vtxCount = _VtxCount;	//4개다	
	newVB->vtxSize = _VtxSize;		//16바이트

	newVB->vtxDesc.ByteWidth = _VtxCount * _VtxSize;
	newVB->vtxDesc.Usage = _VtxUsage;

	if (D3D11_USAGE::D3D11_USAGE_DYNAMIC == newVB->vtxDesc.Usage)
	{
		newVB->vtxDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	newVB->vtxDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	//초기 데이터를 넣어줄때 세팅해주는 구조체
	D3D11_SUBRESOURCE_DATA dataStruct = D3D11_SUBRESOURCE_DATA();
	dataStruct.pSysMem = _Data;

	if (S_OK != GraphicDevice::Inst()->GetDXDevice()->CreateBuffer(&newVB->vtxDesc, &dataStruct, &newVB->vtxBuffer))
	{
		BOOM;
		return false;
	}

	return true;
}

bool Mesh::CreateIB(DXGI_FORMAT _IdxFormat, UINT _IdxCount, UINT _IdxSize, D3D11_USAGE _IdxUsage, void* _Data)
{
	// 배열의 카파시티를 늘리되 원소는 늘어나지 않는게
// 리저브.

// 배열을 늘리는것이 아니라 원소 그자체를 늘리는것이
// 리사이즈
	arrIB.resize(arrIB.size() + 1);
	IndexBuffer* newIB = new IndexBuffer();
	arrIB[arrIB.size() - 1] = newIB;

	newIB->indexCount = _IdxCount; // 4개다
	newIB->indexSize = _IdxSize; // 16바이트
	newIB->indexBufferType = _IdxFormat; // 16바이트

	// 초기화가 어떻게 될지 걱정됨 현재.
	// 이상하면 내가 
	// NewVB->m_Desc

	newIB->indexDesc.ByteWidth = _IdxCount * _IdxSize;
	// 이거 그래픽카드가 관리할까 아니면 CPU에 할당할까 뭐 이런것들
	// 그리고 관리할때 수정할수 있게 할거야????
	newIB->indexDesc.Usage = _IdxUsage;

	if (D3D11_USAGE::D3D11_USAGE_DYNAMIC == newIB->indexDesc.Usage)
	{
		newIB->indexDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}

	newIB->indexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	// 초기데이터를 넣어줄때 세팅해주는 구조체
	D3D11_SUBRESOURCE_DATA DataStruct = D3D11_SUBRESOURCE_DATA();
	DataStruct.pSysMem = _Data;

	if (S_OK != GraphicDevice::Inst()->GetDXDevice()->CreateBuffer(&newIB->indexDesc, &DataStruct, &newIB->indexBuffer))
	{
		BOOM;
		return false;
	}

	return true;
}
void Mesh::Update(UINT _VtxIndex, UINT _IdxIndex)
{
	UINT offSet = 0;
	UINT idxOffSet = 0;

	GraphicDevice::Inst()->GetDXContext()->IASetVertexBuffers(0, 1, &arrVB[_VtxIndex]->vtxBuffer, &arrVB[_VtxIndex]->vtxSize, &offSet);
	GraphicDevice::Inst()->GetDXContext()->IASetIndexBuffer(arrIB[_IdxIndex]->indexBuffer, arrIB[_IdxIndex]->indexBufferType, idxOffSet);
}

void Mesh::Render(UINT _VtxIndex, UINT _IdxIndex)
{
	//여기서 해야하나 생각해보자
	//if (D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED == drawMode)
	//{
	//	BOOM;
	//}
	////정보가 다 세팅 되었다.
	////렌더링 파이프라인을 시작하겠다.
	//GraphicDevice::Inst()->GetDXContext()->IASetPrimitiveTopology(drawMode);
	

	//버텍스 버퍼와 인덱스 버퍼를 세팅해줘야한다.
	// 이건왜 2중포인터냐면 2차원배열을 넣어달라는 의미
	//0 4개짜리 버텍스정보
	//1 3개짜리 버텍스정보
	//Offset이건 리턴되는값
	//offset 네개짜리 중에서 3번을 그려라

	//0, 0번 세팅하겠다
	//1, 내가 세팅해주려는것은 vb 1개짜리다.
	// &m_ArrVB[_VtxIndex]->m_VB 그녀석의 vb의 시작주소
	// &m_ArrVB[_VtxIndex]->m_VTXSize m_ArrVB[_VtxIndex]->m_VTXSize 사이즈
	// &Offset 시작점
	
	// 이녀석이 인덱스 버퍼를 사용하서 그리겠다는 이야기

	// 
	GraphicDevice::Inst()->GetDXContext()->DrawIndexed(arrIB[_IdxIndex]->indexCount, 0, 0);
}

void Mesh::RenderAuto()
{
	GraphicDevice::Inst()->GetDXContext()->DrawAuto();
}