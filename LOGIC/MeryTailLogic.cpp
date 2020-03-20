#include "MeryTailLogic.h"



MeryTailLogic::MeryTailLogic() : tailingTime(3.0f)
{
}


MeryTailLogic::~MeryTailLogic()
{
}


void MeryTailLogic::Init()
{
	spriteAni = GetActor()->GetComponent<SpriteAnimation>();
}


void MeryTailLogic::Update()
{
	tailingTime -= Time::DeltaTime();



	if (spriteAni->IsAnimationEnd() == true)
	{
		spriteAni->ChangeAnimation(L"MeryTailBase");
		tailingTime = 3.0f;
		isTail = false;
	}
	else if (tailingTime < 0.0f && isTail == false)
	{
		isTail = true;
		spriteAni->ChangeAnimation(L"MeryTailBlink");
	}
}