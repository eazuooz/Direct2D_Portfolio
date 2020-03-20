#pragma once
#include <Logic.h>


class SpriteAnimation;
class SpriteRenderer;
class ShellPetMove : public Logic
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
		SKILL,
	};



private:
	Vector4		direction;
	Vector4		pos;
	Vector4		windowSize;
	float		moveSpeed;
	float		movingTime;
	DIRECTION	DIR;
	STATE		STATE;

	std::wstring fishName;
	std::wstring curAniName;

	bool isRotate;
	bool isFast;

private:
	SpriteRenderer* spriteRenderer;
	SpriteAnimation* spriteAnimaion;

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
	void Skill();

public:
	ShellPetMove();
	~ShellPetMove();
};

