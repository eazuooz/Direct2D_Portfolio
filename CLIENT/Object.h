#pragma once
#include <Maths.h>
#include <SmartPtr.h>

#include <Scene.h>
#include <Actor.h>



class Object
{
protected:	
	std::wstring name;
	Vector2 spriteCutSize;
	Vector4 spriteCountInfo;

	Scene*			scene;
	Actor*			actor;
	/*Sprite*			sprite;
	Texture*		texture;*/





public:
	bool Init();

	void SetScaleMul(const float _Value)
	{
		actor->GetTransform()->MultipleScale(_Value);
	}


public:
	Object();
	Object(My_Ptr<Scene> _Scene, const wchar_t* _Name, Vector4 _CntInfo);
	virtual ~Object();
};

