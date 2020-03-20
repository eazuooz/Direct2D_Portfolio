#pragma once
#include <Logic.h>

//ENGINE
#include <Actor.h>
#include <SpriteAnimation.h>


class GoopyAnimation : public Logic
{
private:
	enum DIRECTION
	{
		LEFT,
		CENTER,
		RIGHT,
	};

private:
	Actor*			 actor;
	SpriteAnimation* spriteAnimation;

	DIRECTION dir;

public:
	void Init()		override;
	void Update()	override;

public:
	GoopyAnimation();
	~GoopyAnimation();
};

