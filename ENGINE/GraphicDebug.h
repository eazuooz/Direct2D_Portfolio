#pragma once
#include "GraphicDevice.h"
#include "Camera.h"
#include "Font.h"

class Mesh;
class ConstBuffer;
class VtxShader;
class PxlShader;
class Blender;
class DepthStencil;
class Rasterizer;
class GraphicDebug
{
private:
	enum SHAPETYPE
	{
		FONT,
		SQUARE,
		SPHERE,
		MAX,
	};

	class ShapeInfo
	{
	public:
		SHAPETYPE type;
		Matrix world;
		Matrix view;
		Matrix projection;
		Vector4 color;
	};

	class FontDrawInfo
	{
	public:
		std::wstring fontName;
		std::wstring text;
		Vector4 color;
	};

private:
	// std::vector<>
	static std::vector<FontDrawInfo> debugRenderText;
	static std::vector<ShapeInfo> debugRender_Vector;
	static int shapeCount;
	static int textCount;

	static Vector4 startTextPos;

	static bool isInit;
	static bool isDebug;

	static Vector4				textureUV;
	static My_Ptr<Mesh>			mesh[SHAPETYPE::MAX];
	static My_Ptr<ConstBuffer>	constBuffer;
	static My_Ptr<ConstBuffer>	colorConstBuffer;
	static My_Ptr<VtxShader>	vtxShader;
	static My_Ptr<PxlShader>	pxlShader;
	static My_Ptr<Blender>		blender;
	static My_Ptr<DepthStencil> depthStencil;
	static My_Ptr<Rasterizer>	rasterizer;
	static My_Ptr<Font>			font;

public:
	static bool IsDebugCheck() {
		return isDebug;
	}

	static void DebugON()
	{		
		isDebug = true;
	}
	static void DebugOFF()
	{
		isDebug = false;
	}

public:
	// 전용 매쉬들 만든다.
	static void Init();


	// 전용 매쉬들 만든다.
	static void DebugRender();


public:
	// 카메라 넣어줘야 하는경우.
	static void DrawSquare(My_Ptr<Camera> _Cam, Matrix _WorldMatrix);
	static void DrawSquare(My_Ptr<Camera> _Cam, Vector4 _Pos, Vector4 _Rot, Vector4 _Scale, Vector4 _Color);
	static void DrawSquare(Vector4 _Pos, Vector4 _Rot, Vector4 _Scale, Vector4 _Color);

	static void DrawSphere(My_Ptr<Camera> _Cam, Matrix _WorldMatrix);
	static void DrawSphere(My_Ptr<Camera> _Cam, Vector4 _Pos, Vector4 _Rot, Vector4 _Scale, Vector4 _Color);
	static void DrawSphere(Vector4 _Pos, Vector4 _Rot, Vector4 _Scale, Vector4 _Color);

	static void DrawFontUI(const wchar_t* _Text, Vector4 _Color);

public:
	GraphicDebug();
	~GraphicDebug();
};

