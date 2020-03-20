#include "PregoMove.h"

int PregoMove::birthCnt = 0;
Vector4 PregoMove::pregoPos;

PregoMove::PregoMove() : birthTime(10.0f)
{
}


PregoMove::~PregoMove()
{
}


void PregoMove::Init()
{
	InitResource();

}

void PregoMove::Update()
{
	birthTime -= Time::DeltaTime();

	pos = GetActor()->GetTransform()->GetLocalPosition();
	pregoPos = pos;
	if (direction.x < 0.0f)
	{
		DIR = DIRECTION::LEFT;
	}
	else if (direction.x > 0.0f)
	{
		DIR = DIRECTION::RIGHT;
	}
	else //0.0f 일때는 그냥 그대로
	{
		//
	}

	if (birthTime < 0.0f)
	{
		
		birthTime = 10.0f;

		state = STATE::SKILL;
	}

	switch (state)
	{
	case STATE::MOVING:
	{
		InterMoving();
	}
	break;
	case STATE::STOP:
	{
		Stop();
	}
	break;
	case STATE::SKILL:
	{
		Birth();
	}
	break;

	break;
	}
}

void PregoMove::Birth()
{
	if (spriteAnimaion->GetCurAni()->aniEnd == true)
	{
		birthCnt++;
		state = STATE::MOVING;
		spriteAnimaion->ChangeAnimation(L"pregoSwim");

		return;
	}
	birthTime = 10.0f;
	spriteAnimaion->ChangeAnimation(L"pregoSkill");

	Move(moveSpeed);
}

