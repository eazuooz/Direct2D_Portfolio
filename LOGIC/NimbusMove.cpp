#include "NimbusMove.h"



NimbusMove::NimbusMove()
{
}


NimbusMove::~NimbusMove()
{
}


void NimbusMove::Init()
{
	InitResource();

	GetActor()->GetTransform()->SetPosition({ Well512Random::Instance().GetFloatValue(-3.0f, 3.0f) , -1.5f });
	//GetActor()->GetTransform()->SetLocalPosition();

	niCollider = GetActor()->GetComponent<BoundingSphere>();

	niCollider->RegisterEnterFunction(&NimbusMove::Enter, this);
	niCollider->RegisterStayFunction(&NimbusMove::Stay, this);
	niCollider->RegisterExitFunction(&NimbusMove::Exit, this);
}

void NimbusMove::Update()
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
		
	}
	break;
	}
}

void NimbusMove::ShellMoving()
{
	movingTime -= Time::DeltaTime();
	if (movingTime < 0.0f && isInterchange == false)		//먹이가 존재하지않고 무빙타임이 0보다 작아졌을때
	{
		movingTime = Well512Random::Instance().GetFloatValue(0.5f, 5.0f);
		moveSpeed = 1.0f;

		switch (DIR)
		{
		case DIRECTION::LEFT:
		{
			if (isInterchange == true)
			{
				direction = minDis.ReturnNormalization();
			}
			else
			{
				float x = Well512Random::Instance().GetFloatValue(-1.0f, 1.0f);
				float y = 0.0f;//Well512Random::Instance().GetFloatValue(-1.0f, 1.0f);
				direction = { x, y, 5.0f };
			}

			if (direction.x < 0.0f)
			{
				spriteRenderer->TurnLeft();
			}
			else if (direction.x > 0.0f)
			{
				if (isHit != true)
				{
					state = STATE::STOP;
				}
			}
			break;
		}
		case DIRECTION::RIGHT:
		{
			if (isInterchange == true)
			{
				direction = minDis.ReturnNormalization();
			}
			else
			{
				float x = Well512Random::Instance().GetFloatValue(-1.0f, 1.0f);
				float y = 0.0f;;// Well512Random::Instance().GetFloatValue(-1.0f, 1.0f);
				direction = { x, y, 5.0f };
			}

			if (direction.x < 0.0f)
			{
				//spriteRenderer->TurnLeft();
				if (isHit != true)
				{
					state = STATE::STOP;
				}
			}
			else if (direction.x > 0.0f)
			{
				spriteRenderer->TurnRight();
			}
			break;
		}
		}
	}
	else // 먹이가 존재할때 또는 무빙타임이 0.0보다 클때
	{
		if (isInterchange == true)
		{
			moveSpeed = interMoveSpeed;
			//moveSpeed += 0.5f * Time::DeltaTime();		

		}
		else
		{
			moveSpeed = 1.0f;
		}
		switch (DIR)
		{
		case DIRECTION::LEFT:
		{
			if (isInterchange == true)
			{
				direction = minDis.ReturnNormalization();
				//direction.y = 0.0f;
			}
			else
			{
				/*float x = Well512Random::Instance().GetFloatValue(-1.0f, 1.0f);
				float y = Well512Random::Instance().GetFloatValue(-1.0f, 1.0f);
				direction = { x, y, 5.0f };*/
			}

			if (direction.x < 0.0f)
			{
				spriteRenderer->TurnLeft();
			}
			else if (direction.x > 0.0f)
			{
				if (isHit != true)
				{
					state = STATE::STOP;
				}
			}
			break;
		}
		case DIRECTION::RIGHT:
		{
			if (isInterchange == true)
			{
				direction = minDis.ReturnNormalization();
				//direction.y = 0.0f;
			}
			else
			{
				//float x = Well512Random::Instance().GetFloatValue(-1.0f, 1.0f);
				//float y = Well512Random::Instance().GetFloatValue(-1.0f, 1.0f);
				//direction = { x, y, 5.0f };
			}

			if (direction.x < 0.0f)
			{
				//spriteRenderer->TurnLeft();
				if (isHit != true)
				{
					state = STATE::STOP;
				}
			}
			else if (direction.x > 0.0f)
			{
				spriteRenderer->TurnRight();
			}
			break;
		}
		}

		Move(moveSpeed);
	}
}

void NimbusMove::Enter(Collider* _This, Collider* _Other)
{

}
	
void NimbusMove::Stay(Collider* _This, Collider* _Other)
{

}

void NimbusMove::Exit(Collider* _This, Collider* _Other)
{

}
