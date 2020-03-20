#pragma once
#include "Object.h"
#include <Sprite.h>
#include <Texture.h>
#include <SpriteAnimation.h>
#include <SpriteRenderer.h>
#include <BoundingSphere.h>
#include <FishMove.h>

#include <PregoMove.h>

class Goopy : public Object
{
private:
	enum __GOOPYANISTATE
	{
		LEFT,
		RIGHT,
		CENTER,
	};
	
private:
	SpriteRenderer* spriteRenderer;
	SpriteAnimation* spriteAnimation;
	BoundingSphere* collider;
	GoopyMove* logic;

	Sprite*			sprite;
	Texture*		texture;



	std::wstring animationName;
	std::wstring spriteName;

	static std::wstring textureName;
	static int textureLoadCnt;
	static int fishCnt;

	int point;



public:
	void PregoOn()
	{
		logic->SetStateMoving();
		GetActor()->GetTransform()->SetLocalPosition(PregoMove::GetPos());
	}

public:
	Actor* GetActor()
	{
		return actor;
	}
	Sprite* GetSprite()
	{
		return sprite;
	}
	GoopyMove* GetLogic()
	{
		return logic;
	}
	BoundingSphere* GetCollider()
	{
		return collider;
	}

public:
	bool Init(int _Point, int _Collider);
	bool InitResources(int _Collider);
	bool CreateAnimations();


//private:
//	static std::list<BoundingSphere*> littleGoopyList;
//	static std::list < BoundingSphere*>::iterator littleGoopyBegin;
//	static std::list < BoundingSphere*>::iterator littleGoopyEnd;
//
//public:
//	static void LittleGoopyList_Update();
//	static void PushLittleGoopy(BoundingSphere* _Collider);
//	static void PopLittleGoopy(const BoundingSphere* _Collider);
//	static void PopLittleGoopy(const Collider* _Collider);





public:
	Goopy(My_Ptr<Scene> _Scene, const wchar_t* _TextureName, Vector4 _CntInfo , int _Point = 0 , int _Collider = 0) ;
	~Goopy();
};

