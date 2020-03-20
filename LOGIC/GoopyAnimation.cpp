#include "GoopyAnimation.h"



GoopyAnimation::GoopyAnimation()
{
}


GoopyAnimation::~GoopyAnimation()
{
}

void GoopyAnimation::Init()
{
	actor = GetActor();
	spriteAnimation = actor->GetComponent<SpriteAnimation>();

	
}

void GoopyAnimation::Update()
{
	
}
