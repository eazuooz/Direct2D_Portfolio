#pragma once
#include "Renderer.h"

class SpriteInstData
{
public:
	Matrix WVP;
	Vector4 SPRITEUV;
	int SpriteIndex;
};

class Mesh;
class ConstBuffer;
class VtxShader;
class PxlShader;
class Sampler;
class Sprite;
class Blender;
class Blender1and1;
class DepthStencil;
class Rasterizer;
class SpriteRenderer :	public Renderer
{
	enum DIRECTION
	{
		RIGHT,
		LEFT,
	};

private:
	Vector4				textureUV;
	My_Ptr<Mesh>		mesh;
	My_Ptr<ConstBuffer> constBuffer;
	My_Ptr<ConstBuffer> constBuffer_UV;
	My_Ptr<ConstBuffer> constBuffer_Blender;
	My_Ptr<ConstBuffer> constBuffer_Hp;
	My_Ptr<VtxShader>	vtxShader;
	My_Ptr<PxlShader>	pxlShader;
	My_Ptr<Sampler>		sampler;

	int spriteIndex;
	My_Ptr<Sprite> sprite;


	My_Ptr<Blender> blender;	
	My_Ptr<DepthStencil> depthStencil;
	My_Ptr<Rasterizer> rasterizer;

private:
	DIRECTION dir;
	bool isRotate;

	bool	alphaGradation;
	Vector4 alphaValue;

	float hpRate;
	

public:
	void RotateOff()
	{
		isRotate = false;
	}

	void AlphaGradationOn()
	{
		alphaGradation = true;
	}

	Vector4 GetAlphaValue()
	{
		return alphaValue;
	}

	void SetRateHp(float _Rate)
	{
		hpRate = _Rate;
	}


public:
	bool OneAndOneBlender;

private:
	void Init() override;
	void Render(const My_Ptr<Camera>& _Camera) override;

public:
	void SetSprite(const wchar_t* _SpriteName, int _SpriteIndex = 0);
	void SetSpriteIndex(int _SpriteIndex) { spriteIndex = _SpriteIndex; }

public:
	void SetBlender(std::wstring _Name);
	

public:
	void TurnLeft()
	{
		dir = DIRECTION::LEFT;
	}
	void TurnRight()
	{
		dir = DIRECTION::RIGHT;
	}

public:
	SpriteRenderer();
	~SpriteRenderer();
};

