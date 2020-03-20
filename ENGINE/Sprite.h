#pragma once
#include <vector>
#include "Texture.h"

class Texture;
class Sprite : public Resources
{
private:
	My_Ptr<Texture>		 texture;
	std::vector<Vector4> cutVector;

private:
	Vector2 spriteCutSize;



public:
	My_Ptr<Texture> GetTexture()
	{
		return texture;
	}

	UINT GetVectorSize()
	{
		return (UINT)cutVector.size();
	}

	Vector2 GetSpriteCutSize()
	{
		return spriteCutSize;
	}

public:
	bool Create(const wchar_t* _TextureName, UINT _XCount, UINT _YCount);
	bool Create(const wchar_t* _TextureName, UINT _XCount, UINT _YCount, UINT _Start, UINT _End);

	void PushCutData(UINT _XCount, UINT _YCount, UINT _Index);
	void PushCutData(Vector4 _CutData, UINT _Index);

public:
	Vector4 GetCutData(UINT _Index);	
	void Update(Shader::SHADERTYPE _ShaderType, int _SetIndex);


public:
	Sprite();
	~Sprite();
};

