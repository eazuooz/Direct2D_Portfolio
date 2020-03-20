#pragma once
#include <Logic.h>
#include <GameWindow.h>
#include <SpriteRenderer.h>
#include <SpriteAnimation.h>
#include <EffectSpriteRenderer.h>


#include "ENUM.h"



class FishLogic : public Logic
{
protected:
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
		SKILL2,
		SKILL3,
		HIT,
		GUSEAT,
		CHANGE,
		CHANGESTOP,
	};
	   
protected:
	Vector4		direction;
	Vector4		prevPos;
	Vector4		pos;
	Vector4		windowSize;
	float		moveSpeed;
	float		movingTime;
	DIRECTION	DIR;
	STATE		state;
	Vector4 minDis;
	std::wstring fishName;
	std::wstring curAniName;
	bool isFast;
	bool isInterchange;

	float interMoveSpeed;

	bool isMonster;

	Vector4 hitDir;
	float hitTime;

	bool isHit;

	bool MONSTER;

protected:

	SpriteRenderer* spriteRenderer;
	SpriteAnimation* spriteAnimaion;
	EffectSpriteRenderer* spriteRenderer2;

	std::map<float, Actor*> findDestMap;


public:
	void Init()		override;
	void Update()	override;

protected:	
	virtual void FindDestination(std::list<Actor*> _DestList);
	bool GetFishName();
	void InitResource();
	
	
	virtual void InterMoving();
	virtual void ShellMoving();
	virtual void Stop();


	
	void SkillMoving();
	void SkillStop();

	void Hit();

	void Move(float _Speed);

public:
	FishLogic();
	~FishLogic();
};

