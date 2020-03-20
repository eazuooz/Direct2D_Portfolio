#pragma once
#include "Object.h"
#include <Sprite.h>
#include <Texture.h>
#include <SpriteAnimation.h>
#include <SpriteRenderer.h>


class MeryEye : public Object
{
private:
	enum __MERYSTATE
	{

	};

private:
	My_Ptr<SpriteRenderer> spriteRenderer;
	My_Ptr<SpriteAnimation> spriteAnimation;
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
	bool InitResources() ;
	bool CreateAnimations() ;

public:
	MeryEye(My_Ptr<Scene> _Scene, const wchar_t* _Name, Vector4 _CntInfo);
	~MeryEye();
};

class SpriteAnimation;
class SpriteRenderer;
class MeryTail : public Object
{
private:
	enum __MERYSTATE
	{

	};

private:
	My_Ptr<SpriteRenderer> spriteRenderer;
	My_Ptr<SpriteAnimation> spriteAnimation;
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
	bool CreateAnimations();

public:
	MeryTail(My_Ptr<Scene> _Scene, const wchar_t* _Name, Vector4 _CntInfo);
	~MeryTail();
};

