#include "AngieMove.h"



AngieMove::AngieMove()
{
}


AngieMove::~AngieMove()
{
}


void AngieMove::Init()
{
	InitResource();
}

void AngieMove::Update()
{
	pos = GetActor()->GetTransform()->GetLocalPosition();
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

	}
	break;

	break;
	}
}
