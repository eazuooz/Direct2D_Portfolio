#pragma once
#include "Object.h"
#include <Sprite.h>
#include <Texture.h>
#include <SpriteAnimation.h>
#include <SpriteRenderer.h>

#include <BoundingSphere.h>
#include <BoundingBox.h>

class Hatch : public Object
{
private:
	My_Ptr<SpriteRenderer>		spriteRenderer;
	My_Ptr < SpriteAnimation>			spriteAnimation;
	//BoundingBox*		collider;
	My_Ptr < BoundingSphere>				collider;
	My_Ptr < Sprite>						sprite;
	My_Ptr < Texture>					texture;
	bool isAnimation;

	static bool isInit;

	My_Ptr<Actor> hatchGoopy;
	My_Ptr<SpriteAnimation>  hatchGoopyAni;

	int foodLevel;
	int foodCnt;

	bool existBlip;

public:
	bool ExistBlip()
	{
		return existBlip;
	}

public:
	My_Ptr < Actor> GetActor()
	{
		return actor;
	}
	My_Ptr < Sprite> GetSprite()
	{
		return sprite;
	}

public:
	My_Ptr<SpriteRenderer> GetSpriteRenderer()
	{
		return spriteRenderer;
	}

public:
	bool Init(int _ColOrder);
	bool InitResources(int _ColOrder);
	bool InitSpriteAnimation();
	bool InitCollider(int _ColOrder);

private:
	enum SPRITECLASS
	{
		GOOPY,
		FOOD,
		FOODCNT,
		PIRANA,
		ULTRA,
		GUN,
		EGG,
	};

	SPRITECLASS spriteClass;

private:
	int petCount;
public:
	int GetPetCnt()
	{
		return petCount;
	}

public:
	void AddSprite();	

public:
	void Enter(Collider* _This, Collider* _Other);
	void Stay(Collider* _This, Collider* _Other);
	void Exit(Collider* _This, Collider* _Other);

public:
	Hatch(My_Ptr<Scene> _Scene, const wchar_t* _TextureName, Vector4 _CntInfo, int _ColOrder);
	Hatch();
	~Hatch();
};

