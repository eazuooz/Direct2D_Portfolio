#pragma once
#include <Logic.h>



class SpriteAnimation;
class SpriteRenderer;
class PetFishMove : public Logic
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
	STATE		state;

	std::wstring fishName;
	std::wstring curAniName;

	bool isFast;

protected:
	bool isInterchange;
	Vector4 minDis;

protected:
	SpriteRenderer* spriteRenderer;
	SpriteAnimation* spriteAnimaion;

private:
	bool GetFishName();
	
public:
	void Init()		override;
	void Update()	override;

private:
	void Moving();
	void Stop();
	void Skill();
	
protected:
	void InterMoving();
	void Move(float _Speed);

public:
	PetFishMove();
	~PetFishMove();
};

