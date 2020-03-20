#include "MeryEyeLogic.h"
#include <MyTime.h>



MeryEyeLogic::MeryEyeLogic() : blinkTime(3.0f), isBlink(false)
{
}


MeryEyeLogic::~MeryEyeLogic()
{
}


void MeryEyeLogic::Init()
{
	spriteAni = GetActor()->GetComponent<SpriteAnimation>();
}


void MeryEyeLogic::Update()
{


	blinkTime -= Time::DeltaTime();



	if (spriteAni->IsAnimationEnd() == true)
	{
		spriteAni->ChangeAnimation(L"MeryEyeBase");
		blinkTime = 3.0f;
		isBlink = false;
	}
	else if (blinkTime < 0.0f && isBlink == false)
	{
		isBlink = true;
		spriteAni->ChangeAnimation(L"MeryEyeBlink");		
	}	
}
