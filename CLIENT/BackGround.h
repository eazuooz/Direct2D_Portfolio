#pragma once
#include "Object.h"
#include <Sprite.h>
#include <Texture.h>
#include <SpriteAnimation.h>
#include <SpriteRenderer.h>
#include <Sprite.h>
#include <Texture.h>


class BackGround : public Object
{
private:
	SpriteRenderer* spriteRenderer;
	SpriteAnimation* spriteAnimation;
	Sprite*			sprite;
	Texture*		texture;

public:
	Actor* GetActor()
	{
		return actor;
	}
	Sprite* GetSprite()
	{
		return sprite;
	}
public:
	bool Init();
	bool InitResources();

public:
	BackGround(My_Ptr<Scene> _Scene, const wchar_t* _TextureName, Vector4 _CntInfo);
	~BackGround();
};

