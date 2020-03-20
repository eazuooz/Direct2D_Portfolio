#pragma once
#include "Resources.h"
#include "GraphicDevice.h"

//그거다 
//버텍스
//헐
//도메인쉐이더
//지오 쉐이더
//픽셀쉐이더



class Shader : public Resources
{
public:
	enum SHADERTYPE
	{
		SHTYPE_VS,
		SHTYPE_HS,
		SHTYPE_DS,
		SHTYPE_GS,
		SHTYPE_PS,
	};

public:
	static UINT SizeOfFormat(DXGI_FORMAT _Format);

protected:
	static char vtxBufferText[256];

	//쉐이더란 렌더링의 스크립트 언어라고 생각해도 된다.
	//그럼 스크립트 언어란
	//어떤 메인 프로세스나 프로그램에 끼어서 좀더 쉽고
	//구현하려는 내용에 특화된 언어를
	//아예 ㅣ가자 대화에 관련된 부분으 니가짜
	// 스크립트 언어는 인터프린터 언어로 이루어진다.
	//중간중간 새롭게 읽어서 새로운 코드 뭉치를 만들어낸다/
	// 쉐이더도 버전이 있다.
	//그래픽카드마다 지원하지 못하는 버전이 있을수 있다.
	//쉐이더 버전은 일단 5.0을 사용할건데

	SHADERTYPE Type;

	ID3DBlob* blob;
	ID3DBlob* errorBlob;

	UINT versionHigh;//version high	//5
	UINT versionLow;//version low	//0

public:
	virtual void Update() = 0;

public:
	Shader(SHADERTYPE _Type);
	~Shader();
};

