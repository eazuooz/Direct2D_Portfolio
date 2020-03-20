#include "ItchyMove.h"
#include "MonsterList.h"


ItchyMove::ItchyMove() : findTime(1.0f), isChange(false)
{
}


ItchyMove::~ItchyMove()
{
}

void ItchyMove::Init()
{
	InitResource();

	interMoveSpeed = 3.0f;
}

void ItchyMove::Update()
{
	findTime -= Time::DeltaTime();

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

	if(findTime < 0.0f)
	{
		FindDestination(MonsterList::GetMonsterList());

		findTime = 1.0f;

		if (MonsterList::GetMonsterList().size() > 0 && isChange == false)
		{
			isChange = true;
			state = STATE::SKILL;
		}
		else if(MonsterList::GetMonsterList().size() == 0 && isChange == true)
		{
			isChange = false;
			state = STATE::MOVING;
		}
		
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
		SkillMove();
	}
		break;
	case STATE::SKILL2:
	{
		SkillStop();
	}
	break;
	}
}

void ItchyMove::SkillMove()
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
				float y = Well512Random::Instance().GetFloatValue(-1.0f, 1.0f);
				direction = { x, y, 5.0f };
			}

			if (direction.x < 0.0f)
			{
				spriteRenderer->TurnLeft();
			}
			else if (direction.x > 0.0f)
			{
				state = STATE::SKILL2;
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
				float y = Well512Random::Instance().GetFloatValue(-1.0f, 1.0f);
				direction = { x, y, 5.0f };
			}

			if (direction.x < 0.0f)
			{
				//spriteRenderer->TurnLeft();
				state = STATE::SKILL2;
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
				state = STATE::SKILL2;
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
				state = STATE::SKILL2;
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

void ItchyMove::SkillStop()
{
	Vector4 fast;
	fast.x = abs(direction.x);
	fast.y = abs(direction.y);

	float maxf = fast.x + fast.y;
	if (maxf > 1.0f)
	{
		isFast = true;
	}
	else
	{
		isFast = false;
	}

	if (spriteAnimaion->GetCurAni()->aniEnd == true)
	{
		std::wstring tempSwim; //= fishName + L"Swim";
		if (isFast == true)
		{
			tempSwim = fishName + L"Skill";
		}
		else
		{
			tempSwim = fishName + L"Skill";
		}


		if (DIR == DIRECTION::LEFT)
		{
			spriteRenderer->TurnLeft();
			spriteAnimaion->ChangeAnimation(tempSwim.c_str());
		}
		else
		{
			spriteRenderer->TurnRight();
			spriteAnimaion->ChangeAnimation(tempSwim.c_str());
		}

		state = STATE::SKILL;
	}
	else
	{
		std::wstring temp; //= fishName + L"Turn";
		if (isFast == true)
		{
			temp = fishName + L"Skill2";
		}
		else
		{
			temp = fishName + L"Skill2";
		}


		spriteAnimaion->ChangeAnimation(temp.c_str());
	}


	moveSpeed = 0.3f;
	Move(moveSpeed);
}
