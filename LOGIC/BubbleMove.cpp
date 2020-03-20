#include "BubbleMove.h"

#include "ENUM.h"

bool BubbleMove::isEndingScene = false;

BubbleMove::BubbleMove()
{
}


BubbleMove::~BubbleMove()
{
}

void BubbleMove::Init()
{

}

void BubbleMove::Update()
{

	if (GetActor()->GetTransform()->GetLocalPosition().y > 1.4f && isEndingScene == false)
	{
		GetActor()->Die();
	}

	if (isEndingScene == true)
	{
		if (GetActor()->GetTransform()->GetLocalPosition().y > 3.0f && isEndingScene == true)
		{
			GetActor()->Die();
		}
	}





	if (xCheck == false)
	{
		dir = { 1.5f, 1.0f, 1.0f };
	}
	else
	{
		dir = { -1.5f, 1.0f, 1.0f };
	}

	GetActor()->GetTransform()->Move2D((dir* 1.5f * Time::DeltaTime()), Well512Random::Instance().GetFloatValue(50.0f, 60.0f));
	//GetActor()->GetTransform()->SetLocalPosition();
	
	if (xCheck == true)
	{
		xCheck = false;
	}
	else
	{
		xCheck = true;
	}

}
