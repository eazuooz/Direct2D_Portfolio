#include "StartBubbleMove.h"


#include "ENUM.h"

StartBubbleMove::StartBubbleMove(): state(START), dir ({ 0.0f, -2.0f, 0.0f })
{
}


StartBubbleMove::~StartBubbleMove()
{
}

void StartBubbleMove::Init()
{

}

void StartBubbleMove::Update()
{
	switch (state)
	{
	case StartBubbleMove::START:
		Start();
		break;
	case StartBubbleMove::END:
		End();
		break;	
	}
}

void StartBubbleMove::Start()
{
	if (GetActor()->GetTransform()->GetLocalPosition().y > 1.4f)
	{
		GetActor()->Die();
	}

	if (xCheck == false)
	{
		dir.x = 3.0f;
	}
	else
	{
		dir.x = -3.0f;
	}

	dir.y += 1.5f * Time::DeltaTime();

	GetActor()->GetTransform()->Move2D((dir* 1.0f * Time::DeltaTime()), Well512Random::Instance().GetFloatValue(50.0f, 60.0f));

	if (xCheck == true)
	{
		xCheck = false;
	}
	else
	{
		xCheck = true;
	}
}

void StartBubbleMove::End()
{
	if (GetActor()->GetTransform()->GetLocalPosition().y > 1.4f)
	{
		GetActor()->Die();
	}

	if (xCheck == false)
	{
		dir = { 3.0f, 1.0f, 1.0f };
	}
	else
	{
		dir = { -3.0f, 1.0f, 1.0f };
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

