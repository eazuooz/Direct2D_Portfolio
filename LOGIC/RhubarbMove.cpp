#include "RhubarbMove.h"



RhubarbMove::RhubarbMove()
{
}


RhubarbMove::~RhubarbMove()
{
}

void RhubarbMove::Init()
{
	InitResource();

	GetActor()->GetTransform()->SetPosition({ Well512Random::Instance().GetFloatValue(-3.0f, 3.0f) , -2.0f });
	//GetActor()->GetTransform()->SetLocalPosition();

	rhCollider = GetActor()->GetComponent<BoundingSphere>();

	rhCollider->RegisterEnterFunction(&RhubarbMove::Enter, this);
	rhCollider->RegisterStayFunction(&RhubarbMove::Stay, this);
	rhCollider->RegisterExitFunction(&RhubarbMove::Exit, this);
}

void RhubarbMove::Update()
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
		ShellMoving();
	}
	break;
	case STATE::STOP:
	{
		Stop();
	}
	break;
	case STATE::SKILL:
	{
		Skill();
	}
	break;
	}
}

void RhubarbMove::Skill()
{
	if (spriteAnimaion->GetCurAni()->aniEnd == true)
	{
		state = STATE::STOP;
	}

	spriteAnimaion->ChangeAnimation(L"rhubarbSkill");
}

void RhubarbMove::Enter(Collider* _This, Collider* _Other)
{
	state = STATE::SKILL;


}

void RhubarbMove::Stay(Collider* _This, Collider* _Other)
{
	state = STATE::SKILL;
}

void RhubarbMove::Exit(Collider* _This, Collider* _Other)
{

}