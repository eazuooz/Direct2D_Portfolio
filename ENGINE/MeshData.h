#pragma once
#include <Maths.h>
#include <d3d11_4.h>


class Vertex
{
public:
	class Vtx2D
	{
	public:
		Vector4 pos;
		Vector2 uv;
		Vector4 color;

	public:
		static UINT MemorySize()
		{
			return (UINT)sizeof(Vtx2D);
		}			
	};

	class VtxDebug
	{
	public:
		Vector4 pos;

	public:
		static UINT MemorySize()
		{
			return (UINT)sizeof(VtxDebug);
		}
	};

private:
	Vertex() {};
	~Vertex() {};
};

class Index
{
public:
	class IDX16
	{
		WORD _0, _1, _2;
	};

	class IDX32
	{
	public:
		UINT _0, _1, _2;

		static UINT MemCount()
		{
			return 3;
		}

		static UINT MemorySize()
		{
			return (UINT)sizeof(UINT);
		}

		static DXGI_FORMAT Format()
		{
			return DXGI_FORMAT_R32_UINT;
		}

	public:
		IDX32(UINT __0, UINT __1, UINT __2) : _0(__0), _1(__1), _2(__2)
		{

		}

	};

private:
	Index() {}
	~Index() {}
};

