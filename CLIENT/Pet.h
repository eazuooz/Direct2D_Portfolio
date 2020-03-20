#pragma once
#include <SmartPtr.h>

#include <Scene.h>
#include <Actor.h>
#include <Sprite.h>
#include <SpriteAnimation.h>


class Pet
{
private:
	bool isDataLoad;

protected:
	std::wstring name;
	Vector2 spriteCutSize;
	Vector4 spriteCountInfo;

	Scene*			scene;
	Actor*			actor;

	SpriteRenderer* spriteRenderer;
	SpriteAnimation* spriteAnimation;

	Sprite*			sprite;
	Texture*		texture;

	std::wstring animationName;
	std::wstring spriteName;
	std::wstring textureName;
	
	std::wstring fishName;

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
	void Init();
	void AnimationInit();


public:
	Pet(My_Ptr<Scene> _Scene, const wchar_t* _TextureName, Vector4 _CntInfo);
	~Pet();
};

