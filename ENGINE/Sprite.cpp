#include "Sprite.h"



Sprite::Sprite() : texture(nullptr)
{

}


Sprite::~Sprite()
{

}
bool Sprite::Create(const wchar_t* _TextureName, UINT _XCount, UINT _YCount)
{
	return Create(_TextureName, _XCount, _YCount, 0, (_XCount * _YCount)-1 );	
}

bool Sprite::Create(const wchar_t* _TextureName, UINT _XCount, UINT _YCount, UINT _Start, UINT _End)
{
	++_End;

	if (_Start > _End)
	{
		BOOM;
		return false;
	}

	if (nullptr == _TextureName)
	{
		BOOM;
		return false;
	}

	texture = Resources::Find<Texture>(_TextureName);
	if (nullptr == texture)
	{
		BOOM;
		return false;
	}


	if (_End >= (UINT)cutVector.size())
	{
		cutVector.resize(_End + 1);
	}

	//0보다 작으면 터트러야 하는데
	//여러분들이 직접만드세요

	//12, 5, 5, 20

	for (UINT i = _Start; i < _End; ++i)
	{
		PushCutData(_XCount, _YCount, i);
	}

	spriteCutSize.x = float(texture->Width() / _XCount);
	spriteCutSize.y = float(texture->Height() / _YCount);


	return true;
}

void Sprite::PushCutData(UINT _XCount, UINT _YCount, UINT _Index)
{
	UINT X = _Index % _XCount;
	UINT Y = _Index / _XCount;

	Vector4 Data;


	Data.size.x = (1.0f / (float)_XCount);
	Data.size.y = (1.0f / (float)_YCount);
	Data.x = Data.size.x * X;
	Data.y = Data.size.y * Y;

	

	PushCutData(Data, _Index);
}

void Sprite::PushCutData(Vector4 _CutData, UINT _Index)
{
	if (_Index >= (UINT)cutVector.size())
	{
		cutVector.resize(_Index);
	}

	cutVector[_Index] = _CutData;
}

Vector4 Sprite::GetCutData(UINT _Index)
{
	if (_Index >= (unsigned int)cutVector.size())
	{
		BOOM;
		return { 0.0F };
	}

	return cutVector[_Index];
}

void Sprite::Update(Shader::SHADERTYPE _ShaderType, int _SetIndex)
{
	if (nullptr == texture)
	{
		BOOM;
	}

	texture->Update(_ShaderType, _SetIndex);
}
