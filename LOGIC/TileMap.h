#pragma once
#include <map>
#include <SmartPtr.h>
#include <Renderer.h>

class TileInstData
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
class SpriteAnimation;
class Blender;
class Blender1and1;
class DepthStencil;
class Rasterizer;
class TileMap : public Renderer
{
public:
	class Tile : public ControlBlock
	{
	public:
		Vector4 basePos;
		Vector4 pos;

		bool	isMove;
		int		spriteIndex;
		int		floor;
		int		leftWallFloor;
		int		rightWallFloor;

	public:
		Tile() : isMove(true), spriteIndex(0), floor(0), leftWallFloor(0), rightWallFloor(0) {}
	};

private:
	Vector4					textureUV;
	My_Ptr<Mesh>			mesh;
	My_Ptr<ConstBuffer>		constBuffer;
	My_Ptr<ConstBuffer>		constBuffer_UV;
	My_Ptr<VtxShader>		vtxShader;
	My_Ptr<PxlShader>		pxlShader;
	My_Ptr<Sampler>			sampler;
	My_Ptr<Sprite>			tileSprite;
	My_Ptr<Sprite>			floorSprite;
	My_Ptr<SpriteAnimation>	spriteAnimation;
	My_Ptr<Blender>			blender;
	My_Ptr<DepthStencil>	depthStencil;
	My_Ptr<Rasterizer>		rasterizer;

	// 타일 좌표계 비율
	Vector4 tileSize;
	Vector4 tileScale;
	Vector4 floorScale;

public:	
	std::map<__int64, My_Ptr<Tile>>::iterator tileStart;
	std::map<__int64, My_Ptr<Tile>>::iterator tileEnd;
	std::map<__int64, My_Ptr<Tile>> tileMap;

public:
	void Init() override;
	void Render(const My_Ptr<Camera>& _Camera) override;

public:
	void SetTileSize(Vector4 _TileMoveSize) 
	{ 
		tileScale = _TileMoveSize;
		tileScale *= 2.0f;
		tileSize = _TileMoveSize; 
	}

	void SetFloorScale(Vector4 _FloorScale)
	{
		floorScale = _FloorScale;
	}
	void SetTileSprite(const wchar_t* _Name);
	void SetFloorSprite(const wchar_t* _Name);

	void AddTileWorld(Vector4 _Index);
	void AddTileF(Vector4 _Index);
	void AddTile(int _X, int _Y);

	
private:
	//std::list<My_Ptr<Tile>> AstarPathFind(Vector4 _Start, Vector4 _End);

	void AddTile(Vector4 _Pos);
	void AddTile(__int64 _Key);

public:
	My_Ptr<Tile> FindTile(Vector4 _Pos);
	void ChangeFloor(Vector4 _Pos, int _Floor);
	void ChangeLeftWall(Vector4 _Pos, int _Floor);
	void ChangeRightWall(Vector4 _Pos, int _Floor);

public:
	TileMap();
	~TileMap();
};

