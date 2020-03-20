#pragma once
#include "Resources.h"

class Blender :	public Resources
{
private:
	D3D11_BLEND_DESC	desc;
	ID3D11BlendState*	state;
	Vector4				color;

public:
	void SetBlendOneAndOne();

	bool Create();
	bool Create(D3D11_BLEND _Src, D3D11_BLEND _Dest, D3D11_BLEND _SrcAlpha, D3D11_BLEND _DestAlpha);
	bool Create(const D3D11_BLEND_DESC& _Desc);
	void Update();

public:
	Blender();
	~Blender();
};

