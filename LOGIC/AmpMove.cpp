#include "AmpMove.h"

#include "FishMove.h"
#include <Sound.h>

AmpMove::AmpMove() : lightTime(10.0f)
{
}


AmpMove::~AmpMove()
{
}


void AmpMove::Init()
{
	InitResource();

	BoundingBox* ampCollider = GetActor()->GetComponent<BoundingBox>();

	ampCollider->RegisterEnterFunction(&AmpMove::Enter, this);
	ampCollider->RegisterStayFunction(&AmpMove::Stay, this);
	ampCollider->RegisterExitFunction(&AmpMove::Exit, this);

	light = GetActor()->GetComponent<EffectSpriteRenderer>();
	light->UpdateOff();
}

void AmpMove::Update()
{
	lightTime -= Time::DeltaTime();

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

	if (lightTime < 0.0f)
	{
		light->UpdateOn();
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

void AmpMove::Enter(Collider* _This, Collider* _Other)
{

}
void AmpMove::Stay(Collider* _This, Collider* _Other)
{
	if (Input::Down(L"MOUSELEFT") == true)
	{
		lightTime = 10.0f;		
		light->UpdateOff();
		
		GoopyMove::isAmpOn = true;
		//여기서 물고기가 다죽으며ㅑㄴ된다.

		Sound::Play(L"EEL2.wav");

	}
}
void AmpMove::Exit(Collider* _This, Collider* _Other)
{

}
