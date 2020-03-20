#include "FishLogic.h"



FishLogic::FishLogic() : direction(0.0f), moveSpeed(1.0f), movingTime(Well512Random::Instance().GetFloatValue(0.5f, 3.0f)), spriteRenderer(nullptr), spriteAnimaion(nullptr),
isFast(false), isMonster(false), hitTime(1.0f), isHit(false), MONSTER(false)
{
}


FishLogic::~FishLogic()
{
}

void FishLogic::Init()
{
	
}

void FishLogic::Update()
{

}


void FishLogic::FindDestination(std::list<Actor*> _DestList)
{
	if (_DestList.size() > 0)
	{
		std::list<Actor*> tempList = _DestList;
		std::list<Actor*>::iterator begin = tempList.begin();
		std::list<Actor*>::iterator end = tempList.end();

		for (auto& next : tempList)
		{
			Vector4 coinPos = next->GetTransform()->GetLocalPosition();
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
			findDestMap.clear();
		}
	}
	else
	{
		isInterchange = false;
	}
}

bool FishLogic::GetFishName()
{
	std::wstring originName = curAniName;
	for (int i = 0; i < 4; ++i)
	{
		curAniName.pop_back();
	}
	fishName = curAniName;
	curAniName = originName;


	return true;
}

void FishLogic::InitResource()
{
	prevPos = GetActor()->GetTransform()->GetLocalPosition();
	windowSize = (GameWindow::Inst()->GetWindowSize() / 100.0f) / 2.0f;
	direction = { -0.1f, 0.1f, 0.0f };
	state = STATE::MOVING;

	GetActor()->GetTransform()->SetPosition({ Well512Random::Instance().GetFloatValue(-3.0f, 3.0f) , Well512Random::Instance().GetFloatValue(-2.0f, 2.0f) });

	spriteRenderer = GetActor()->GetComponent<SpriteRenderer>();
	spriteRenderer2= GetActor()->GetComponent<EffectSpriteRenderer>();
	spriteAnimaion = GetActor()->GetComponent<SpriteAnimation>();


	curAniName = spriteAnimaion->GetCurAni()->curAnimationName;

	GetFishName();
}


void FishLogic::InterMoving()
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
				
				if (spriteRenderer2 != nullptr)
				{
					spriteRenderer2->TurnLeft();
				}
				
			}
			else //if(direction.x > 0.0f)
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
			else //if (direction.x > 0.0f)
			{
				spriteRenderer->TurnRight();
				if (spriteRenderer2 != nullptr)
				{
					spriteRenderer2->TurnRight();
				}
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
				if (spriteRenderer2 != nullptr)
				{
					spriteRenderer2->TurnLeft();
				}
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
				if (spriteRenderer2 != nullptr)
				{
					spriteRenderer2->TurnRight();
				}
			}
			break;
		}
		}

		Move(moveSpeed);
	}
}

void FishLogic::ShellMoving()
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
				float y = -0.5f;//Well512Random::Instance().GetFloatValue(-1.0f, 1.0f);
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
				float y = -0.5f;// Well512Random::Instance().GetFloatValue(-1.0f, 1.0f);
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

void FishLogic::Stop()
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
		}
		else
		{
			tempSwim = fishName + L"Swim";
		}


		if (DIR == DIRECTION::LEFT)
		{
			spriteRenderer->TurnLeft();
			if (spriteRenderer2 != nullptr)
			{
				spriteRenderer2->TurnLeft();
			}

			spriteAnimaion->ChangeAnimation(tempSwim.c_str());
		}
		else
		{
			spriteRenderer->TurnRight();
			if (spriteRenderer2 != nullptr)
			{
				spriteRenderer2->TurnRight();
			}
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
		}
		else
		{
			temp = fishName + L"Turn";
		}


		spriteAnimaion->ChangeAnimation(temp.c_str());
	}


	moveSpeed = 0.3f;
	Move(moveSpeed);
}

void FishLogic::Move(float _Speed)
{
	float floorY = 0.0f;
	float minus = 0.0f;
	if (MONSTER == true)
	{
		floorY = 1.0f;
		minus = 0.5f;
	}
	else
	{
		minus = 0.0f;
		floorY = 0.5f;
	}
	

	moveSpeed = _Speed;

	if (pos.x > windowSize.x - 0.3f)
	{
		direction.x = 0.0f;
		GetActor()->GetTransform()->SetPosition({ windowSize.x - 0.3f, pos.y });
		GetActor()->GetTransform()->Move2D((direction * moveSpeed * Time::DeltaTime()), __PET);

		if (pos.y > windowSize.y - 1.2f)
		{
			direction.y = 0.0f;
			GetActor()->GetTransform()->SetPosition({ windowSize.x - 0.3f, windowSize.y - 1.2f });
		}
		else if (pos.y < -windowSize.y + 0.5f)
		{
			direction.y = 0.0f;
			GetActor()->GetTransform()->SetPosition({ windowSize.x - 0.3f, -windowSize.y + 0.5f });
		}
	}
	else if (pos.x < -windowSize.x + 0.3f)
	{
		direction.x = 0.0f;
		GetActor()->GetTransform()->SetPosition({ -windowSize.x + 0.3f, pos.y });
		GetActor()->GetTransform()->Move2D((direction * moveSpeed * Time::DeltaTime()), __PET);

		if (pos.y > windowSize.y - 1.2f)
		{
			direction.y = 0.0f;
			GetActor()->GetTransform()->SetPosition({ -windowSize.x + 0.3f, windowSize.y - 1.2f });
		}
		else if (pos.y < -windowSize.y + 0.5f)
		{
			direction.y = 0.0f;
			GetActor()->GetTransform()->SetPosition({ -windowSize.x + 0.3f, -windowSize.y + 0.5f });
		}
	}
	else if (pos.y > windowSize.y - 1.2f)
	{
		direction.y = 0.0f;
		GetActor()->GetTransform()->SetPosition({ pos.x, windowSize.y - 1.2f });
		GetActor()->GetTransform()->Move2D((direction * moveSpeed * Time::DeltaTime()), __PET);

		if (pos.x > windowSize.x - 0.3f)
		{
			direction.x = 0.0f;
			GetActor()->GetTransform()->SetPosition({ windowSize.x - 0.3f, windowSize.y - 1.2f });
		}
		else if (pos.x < -windowSize.x + 0.3f)
		{
			direction.x = 0.0f;
			GetActor()->GetTransform()->SetPosition({ -windowSize.x + 0.3f, windowSize.y - 1.2f });
		}
	}
	else if (pos.y < -windowSize.y + floorY)
	{
		direction.y = 0.0f;
		GetActor()->GetTransform()->SetPosition({ pos.x, -windowSize.y + floorY });
		GetActor()->GetTransform()->Move2D((direction * moveSpeed * Time::DeltaTime()), __PET);

		if (pos.x > windowSize.x - 0.3f)
		{
			direction.x = 0.0f;
			GetActor()->GetTransform()->SetPosition({ windowSize.x - 0.3f,-windowSize.y + floorY });
		}
		else if (pos.x < -windowSize.x + 0.3f)
		{
			direction.x = 0.0f;
			GetActor()->GetTransform()->SetPosition({ -windowSize.x + 0.3f, -windowSize.y + floorY });
		}
	}
	else
	{
		GetActor()->GetTransform()->Move2D((direction * moveSpeed * Time::DeltaTime()), __PET);
	}
}

void FishLogic::SkillMoving()
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
				direction.z = 1.0f;
			}
			else
			{
				float x = Well512Random::Instance().GetFloatValue(-1.0f, 1.0f);
				float y = Well512Random::Instance().GetFloatValue(-1.0f, 1.0f);
				direction = { x, y, 1.0f };
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
				direction.z = 1.0f;
			}
			else
			{
				float x = Well512Random::Instance().GetFloatValue(-1.0f, 1.0f);
				float y = Well512Random::Instance().GetFloatValue(-1.0f, 1.0f);
				direction = { x, y, 1.0f };
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
				direction.z = 1.0f;
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
				direction.z = 1.0f;
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

void FishLogic::SkillStop()
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

void FishLogic::Hit()
{
	hitTime -= Time::DeltaTime();

	if (hitTime < 0.0f)
	{
		hitTime = 1.5f;
		state = STATE::STOP;
		isHit = false;
	}



	direction = -(hitDir - pos);
	
	Move(1.0f);
}