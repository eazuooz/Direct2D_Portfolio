#pragma once
#include "Renderer.h"

class Mesh;
class ConstBuffer;
class VtxShader;
class PxlShader;
class Sampler;
class Blender;
class DepthStencil;
class Rasterizer;
class RectRenderer : public Renderer
{
private:
	Vector4				color;
	My_Ptr<Mesh>		mesh;
	My_Ptr<ConstBuffer> constBuffer;
	My_Ptr<ConstBuffer> constColor;
	My_Ptr<VtxShader>	vtxShader;
	My_Ptr<PxlShader>	pxlShader;
	My_Ptr<Sampler>		sampler;
	My_Ptr<Blender>		blender;
	My_Ptr<DepthStencil> depthStencil;
	My_Ptr<Rasterizer> rasterizer;

public:
	void Init() override;
	void Render(const My_Ptr<Camera>& _Camera) override;

public:
	void SetColor(const Vector4& _Color)
	{
		color = _Color;
	}

public:
	RectRenderer();
	~RectRenderer();
};

