#include "GumboMove.h"

#include "PetList.h"
#include "MonsterList.h"

Vector4 GumboMove::returnPos;
BoundingSphere* GumboMove::collider;

GumboMove::GumboMove() : existMonster(false)
{
}


GumboMove::~GumboMove()
{
}

void GumboMove::Init()
{
	InitResource();


	collider = GetActor()->GetComponent<BoundingSphere>();

	PetList::existGumbo = true;
}

void GumboMove::Update()
{

	FindDestination(MonsterList::GetMonsterList());		
	


	pos = GetActor()->GetTransform()->GetLocalPosition();
	returnPos = pos;
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
	}
}

void GumboMove::FindDestination(std::list<Actor*> _DestList)
{
	if (_DestList.size() > 0)
	{
		std::list<Actor*> tempList = _DestList;
		std::list<Actor*>::iterator begin = tempList.begin();
		std::list<Actor*>::iterator end = tempList.end();

		Vector4 coinPos;
		for (auto& next : tempList)
		{
			coinPos = next->GetTransform()->GetLocalPosition();
			//minVector = 100.0f;
			minDis.z = 0.0f;
			Vector4 tempDir = coinPos - pos;
			tempDir.z = 0.0f;
			findDestMap.insert(std::map<float, Actor*>::value_type(tempDir.Distance(), next));
		}

		begin = tempList.begin();
		if (begin == end)
		{
			isInterchange = false;
		}
		else
		{
			isInterchange = true;
			minDis = findDestMap.begin()->second->GetTransform()->GetLocalPosition() - pos;
			
			
			minDis *= -1.0f;
			minDis.z *= -1.0f;

			if (coinPos.y > 0.0f)
			{
				if (minDis.y < 0.0f)
				{
					//minDis.y *=
				}
				else
				{
					minDis.y *= -1.0f;
				}				
			}
			else
			{
				if (minDis.y < 0.0f)
				{
					minDis.y *= -1.0f;
				}
				else
				{
					//minDis.y *= -1.0f;
				}
			}

			if (coinPos.x > 0.0f)
			{
				if (minDis.x < 0.0f)
				{
					//minDis.y *=
				}
				else
				{
					minDis.x *= -1.0f;
				}
			}
			else
			{
				if (minDis.x < 0.0f)
				{
					minDis.x *= -1.0f;
				}
				else
				{
					//minDis.y *= -1.0f;
				}
			}

			existMonster = true;
			interMoveSpeed = 5.0f;
			findDestMap.clear();
		}
	}
	else
	{
		existMonster = false;
		isInterchange = false;
	}
}

void GumboMove::InterMoving()
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
				float y = Well512Random::Instance().GetFloatValue(-1.0f, 1.0f);
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

void GumboMove::Stop()
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
			
			tempSwim = fishName + L"Swimfast";

			if (existMonster == true)
			{
				tempSwim += L"light";
			}
		}
		else
		{
			tempSwim = fishName + L"Swim";

			if (existMonster == true)
			{
				tempSwim += L"light";
			}
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

		state = STATE::MOVING;
	}
	else
	{
		std::wstring temp; //= fishName + L"Turn";
		if (isFast == true)
		{
			temp = fishName + L"Turnfast";

			if (existMonster == true)
			{
				temp += L"light";
			}
		}
		else
		{
			temp = fishName + L"Turn";

			if (existMonster == true)
			{
				temp += L"light";
			}
		}


		spriteAnimaion->ChangeAnimation(temp.c_str());
	}


	moveSpeed = 0.3f;
	Move(moveSpeed);
}