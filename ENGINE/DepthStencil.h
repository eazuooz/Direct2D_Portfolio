#pragma once
#include "Resources.h"


class DepthStencil : public Resources
{
private:
	D3D11_DEPTH_STENCIL_DESC desc;
	ID3D11DepthStencilState* state;

public:
	bool Create();
	bool Create(const D3D11_DEPTH_STENCIL_DESC& _Desc);
	void Update();

public:
	DepthStencil();
	~DepthStencil();
};

