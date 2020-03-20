#include "TileMap.h"

#include <Sampler.h>
#include <Mesh.h>
#include <ConstantBuffer.h>
#include <VertexShader.h>
#include <PixelShader.h>
#include <Sprite.h>
#include <Blender.h>
#include <DepthStencil.h>
#include <Rasterizer.h>

TileMap::TileMap()
{
}


TileMap::~TileMap()
{
}

void TileMap::Init()
{
	Renderer::Init();

	sampler			= Resources::Find<Sampler>			(L"SAMPLER");
	mesh			= Resources::Find<Mesh>				(L"DTEXMESH");
	constBuffer		= Resources::Find<ConstBuffer>		(L"MATRIXCONSTBUFFER");
	constBuffer_UV	= Resources::Find<ConstBuffer>		(L"UVCONSTBUFFER");
	vtxShader		= Resources::Find<VtxShader>		(L"TextureShader.fx");
	pxlShader		= Resources::Find<PxlShader>		(L"TextureShader.fx");
	blender			= Resources::Find<Blender>			(L"BLEND");
	depthStencil	= Resources::Find<DepthStencil>		(L"DEPTHSTENCIL");
	rasterizer		= Resources::Find<Rasterizer>		(L"RASTERIZER");
}

void TileMap::Render(const My_Ptr<Camera>& _Camera)
{
	UpdateTransform();

	Matrix WorldMatrix = GetWorldMatrix();
	Matrix ViewMatrix = _Camera->GetViewMatrix();
	Matrix ProjectionMatrix = _Camera->GetProjectionMatrix();
	Matrix WVP = WorldMatrix * ViewMatrix * ProjectionMatrix;
		
	vtxShader->Update();
	pxlShader->Update();
	
	GraphicDevice::Inst()->GetDXContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	sampler->Update(Shader::SHADERTYPE::SHTYPE_PS, 0);
	depthStencil->Update();
	rasterizer->Update();
	blender->Update();
	mesh->Update(0, 0);
	   
	Vector4 idx;
	Vector4 floorPos;
	Vector4 leftWallPos;
	Vector4 rightWallPos;

	Matrix posMat;
	Matrix scaleMat;
	Matrix resultMat;


	tileStart = tileMap.begin();
	tileEnd = tileMap.end();
	for (; tileStart != tileEnd; ++tileStart)
	{
		//FLOOR
		tileSprite->Update(Shader::SHADERTYPE::SHTYPE_PS, 0);

		scaleMat.Scaling(tileScale);
		posMat.Translation(tileStart->second->pos);
		resultMat = scaleMat * posMat * WVP;
		resultMat.TransPose();

		constBuffer->DataSetting(&resultMat, sizeof(Matrix));
		constBuffer->Update();
		
		textureUV = tileSprite->GetCutData(tileStart->second->spriteIndex);
		constBuffer_UV->DataSetting(&textureUV, sizeof(textureUV));
		constBuffer_UV->Update();
		mesh->Render(0, 0);

		//LEFT WALL
		floorSprite->Update(Shader::SHADERTYPE::SHTYPE_PS, 0);

		scaleMat.Scaling(floorScale);

		leftWallPos = tileStart->second->pos;
		leftWallPos.x -= floorScale.x * 0.5f;
		leftWallPos.y -= (floorScale.y * 0.5f);

		posMat.Translation(leftWallPos);
		resultMat = scaleMat * posMat * WVP;
		resultMat.TransPose();

		textureUV = floorSprite->GetCutData(tileStart->second->leftWallFloor);
		constBuffer->DataSetting(&resultMat, sizeof(Matrix));
		constBuffer->Update();
				
		constBuffer_UV->DataSetting(&textureUV, sizeof(textureUV));
		constBuffer_UV->Update();
		mesh->Render(0, 0);

		//RIGHT WALL
		

		rightWallPos = tileStart->second->pos;
		rightWallPos.x += floorScale.x * 0.5f;
		rightWallPos.y -= (floorScale.y * 0.5f);

		posMat.Translation(rightWallPos);
		resultMat = scaleMat * posMat * WVP;
		resultMat.TransPose();

		textureUV = floorSprite->GetCutData(tileStart->second->rightWallFloor);
		constBuffer->DataSetting(&resultMat, sizeof(Matrix));
		constBuffer->Update();

		constBuffer_UV->DataSetting(&textureUV, sizeof(textureUV));
		constBuffer_UV->Update();
		mesh->Render(0, 0);
	}
}

void TileMap::SetTileSprite(const wchar_t* _Name)
{
	tileSprite = Resources::Find<Sprite>(_Name);

	if (nullptr == tileSprite)
	{
		BOOM;
	}
}

void TileMap::SetFloorSprite(const wchar_t* _Name)
{
	floorSprite = Resources::Find<Sprite>(_Name);
}

void TileMap::AddTileWorld(Vector4 _Pos)
{
	Vector4 idx;
	idx.x = (_Pos.x / tileSize.x + _Pos.y / tileSize.y) / 2.0f;
	idx.y = (_Pos.y / tileSize.y + -(_Pos.x / tileSize.x)) / 2.0f;

	idx.ix = std::lroundf(idx.x);
	idx.iy = std::lroundf(idx.y);

	AddTile(idx.ix, idx.iy);
}

void TileMap::AddTileF(Vector4 _Index)
{
	_Index.ConToInt();
	//_Index.ix, _Index.iy;
	
	AddTile(_Index.ix, _Index.iy);
}

void TileMap::AddTile(int _X, int _Y)
{
	__int64 Key = 0;
	int* pKey = (int*)&Key;
	(*pKey) = _X;
	++pKey;
	(*pKey) = _Y;

	//HVEC4 Key = {0,};
	//Key.ix = _X;
	//Key.iy = _Y;

	//AddTile(std::pair<int, int>(_X, _Y));

	AddTile(Key);
}

//std::list<My_Ptr<TileMap::Tile>> TileMap::AstarPathFind(Vector4 _Start, Vector4 _End)
//{
//
//
//	return NULL;
//}

void TileMap::AddTile(Vector4 _Pos)
{	   	 
	Vector4 Idx;
	Idx.x = (_Pos.x / tileSize.x + _Pos.y / tileSize.y) / 2.0f;
	Idx.y = (_Pos.y / tileSize.y + -(_Pos.x / tileSize.x)) / 2.0f;
	

	Idx.ix = std::lroundf(Idx.x);
	Idx.iy = std::lroundf(Idx.y);

	AddTile(Idx.keyPos);
}

void TileMap::AddTile(__int64 _Index)
{
	if (nullptr == tileSprite)
	{
		BOOM;
	}

	if (tileMap.end() != tileMap.find(_Index))
	{
		return;
	}

	My_Ptr<Tile> value = new Tile();

	Vector4 Idx;
	Idx.keyPos = _Index;
	Vector4 Pos;
	// floor과 상관없는 z값이다.
	Pos.x = (Idx.ix - Idx.iy) * tileSize.x;
	Pos.y = (Idx.ix + Idx.iy) * tileSize.y;
	// Pos.y += 0 * m_TileMoveSize.y;
	Pos.z = Pos.y;

	value->basePos = Pos;
	value->pos = Pos;

	tileMap.insert( std::map<__int64, My_Ptr<Tile>>::value_type(_Index, value) );
}


My_Ptr<TileMap::Tile> TileMap::FindTile(Vector4 _Pos)
{
	Vector4 Idx;
	Idx.x = (_Pos.x / tileSize.x + _Pos.y / tileSize.y) / 2.0f;
	Idx.y = (_Pos.y / tileSize.y + -(_Pos.x / tileSize.x)) / 2.0f;

	Idx.ix = std::lroundf(Idx.x);
	Idx.iy = std::lroundf(Idx.y);

	std::map<__int64, My_Ptr<Tile>>::iterator FindIter = tileMap.find(Idx.keyPos);

	if (FindIter == tileMap.end())
	{
		return nullptr;
	}

	return FindIter->second;
}

void TileMap::ChangeFloor(Vector4 _Pos, int _Floor)
{
	My_Ptr<Tile> Tile = FindTile(_Pos);

	if (nullptr != Tile)
	{
		Tile->floor = _Floor;
		Tile->pos = Tile->basePos;
		Tile->pos.y = Tile->basePos.y + Tile->floor * tileSize.y;
		// Value 값형 복사생성자 혹은 대입 연산자가 자동으로 호출될 것이다.
		// 특히나 내가 만들어주지 않았으니까.
	}
}

void TileMap::ChangeLeftWall(Vector4 _Pos, int _Floor)
{
	My_Ptr<Tile> Tile = FindTile(_Pos);

	if (nullptr != Tile)
	{
		Tile->leftWallFloor = _Floor;
		// Value 값형 복사생성자 혹은 대입 연산자가 자동으로 호출될 것이다.
		// 특히나 내가 만들어주지 않았으니까.
	}
}

void TileMap::ChangeRightWall(Vector4 _Pos, int _Floor)
{
	My_Ptr<Tile> Tile = FindTile(_Pos);

	if (nullptr != Tile)
	{
		Tile->rightWallFloor= _Floor;
		// Value 값형 복사생성자 혹은 대입 연산자가 자동으로 호출될 것이다.
		// 특히나 내가 만들어주지 않았으니까.
	}
}