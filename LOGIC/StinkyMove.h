#pragma once
#include <Logic.h>
#include <SpriteRenderer.h>
#include <SpriteAnimation.h>
#include <BoundingSphere.h>


class StinkyMove : public Logic
{
private:
	enum DIRECTION
	{
		LEFT,
		RIGHT,
	};

	enum STATE
	{
		MOVING,
		STOP,
		APPERMONSTER,
	};
		
private:
	Vector4		direction;
	Vector4		pos;
	Vector4		windowSize;
	float		moveSpeed;
	float		movingTime;
	DIRECTION	DIR;
	STATE		state;

	std::wstring fishName;
	std::wstring curAniName;

	bool isRotate;
	bool isFast;

private:
	std::map<float, Actor*> coinMap;

	Vector4 minDis;
	bool existCoin;

private:
	SpriteRenderer* spriteRenderer;
	SpriteAnimation* spriteAnimaion;
	BoundingSphere*		collider;

public:
	SpriteRenderer* GetSpriteRenderer()
	{
		return spriteRenderer;
	}

private:
	bool GetFishName();


public:
	void Init()		override;
	void Update()	override;

public:
	void Moving();
	void Stop();
	void AppearMonster();

	void Move(float _Speed);

public:
	void Enter(Collider* _This, Collider* _Other);
	void Stay(Collider* _This, Collider* _Other);
	void Exit(Collider* _This, Collider* _Other);

public:
	StinkyMove();
	~StinkyMove();
};

