#include "StinkyMove.h"
#include <GameWindow.h>
#include "ENUM.h"

#include "CoinList.h"
#include "MonsterList.h"


StinkyMove::StinkyMove() : direction(0.0f), moveSpeed(1.0f), movingTime(Well512Random::Instance().GetFloatValue(0.5f, 3.0f)), spriteRenderer(nullptr), spriteAnimaion(nullptr),
isFast(false), isRotate(true)
{
}


StinkyMove::~StinkyMove()
{
}

bool StinkyMove::GetFishName()
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

void StinkyMove::Init()
{
	windowSize = (GameWindow::Inst()->GetWindowSize() / 100.0f) / 2.0f;
	direction = { -0.1f, 0.1f, 0.0f };
	state = STATE::MOVING;

	GetActor()->GetTransform()->SetPosition({ Well512Random::Instance().GetFloatValue(-3.0f, 3.0f) , -1.9f });


	spriteRenderer	= GetActor()->GetComponent<SpriteRenderer>();
	spriteAnimaion	= GetActor()->GetComponent<SpriteAnimation>();
	collider		= GetActor()->GetComponent<BoundingSphere>();

	collider->RegisterEnterFunction(&StinkyMove::Enter, this);
	collider->RegisterStayFunction(&StinkyMove::Stay, this);
	collider->RegisterExitFunction(&StinkyMove::Exit, this);

	curAniName = spriteAnimaion->GetCurAni()->curAnimationName;

	GetFishName();
}

void StinkyMove::Update()
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

	if (CoinList::GetCoinList().size() > 0)
	{
		std::list<Actor*> tempList = CoinList::GetCoinList();
		std::list<Actor*>::iterator begin = tempList.begin();
		std::list<Actor*>::iterator end = tempList.end();

		for (auto& next : tempList)
		{
			Vector4 coinPos = next->GetTransform()->GetLocalPosition();

			//minVector = 100.0f;
			minDis.z = 0.0f;

			Vector4 tempDir = coinPos - pos;
			tempDir.z = 0.0f;

			coinMap.insert(std::map<float, Actor*>::value_type(tempDir.Distance(), next));
		}

		begin = tempList.begin();
		if (begin == end)
		{
			existCoin = false;
		}
		else
		{
			existCoin = true;
			minDis = coinMap.begin()->second->GetTransform()->GetLocalPosition() - pos;
			//minDis.y = -0.6f;
			coinMap.clear();
		}
	}
	else
	{
		existCoin = false;
	}


	if (MonsterList::GetMonsterList().size() > 0)
	{
		state = STATE::APPERMONSTER;
	}

	switch (state)
	{
	case STATE::MOVING:
		Moving();
		break;
	case STATE::STOP:
		Stop();
		break;
	case STATE::APPERMONSTER:
		AppearMonster();
		break;
	}
}

void StinkyMove::Moving()
{
	movingTime -= Time::DeltaTime();
	if (movingTime < 0.0f && existCoin == false)		//먹이가 존재하지않고 무빙타임이 0보다 작아졌을때
	{
		movingTime = Well512Random::Instance().GetFloatValue(0.5f, 5.0f);
		moveSpeed = 1.0f;

		switch (DIR)
		{
		case DIRECTION::LEFT:
		{
			if (existCoin == true)
			{
				direction = minDis.ReturnNormalization();
			}
			else
			{
				float x = Well512Random::Instance().GetFloatValue(-1.0f, 1.0f);
				float y = -0.5f;
				direction = { x, y, 5.0f };
			}

			if (direction.x < 0.0f)
			{
				spriteRenderer->TurnLeft();
			}
			else if (direction.x > 0.0f)
			{
				state = STATE::STOP;
			}
			break;
		}
		case DIRECTION::RIGHT:
		{
			if (existCoin == true)
			{
				direction = minDis.ReturnNormalization();
			}
			else
			{
				float x = Well512Random::Instance().GetFloatValue(-1.0f, 1.0f);
				float y = -0.5f;
				direction = { x, y, 5.0f };
			}

			if (direction.x < 0.0f)
			{
				//spriteRenderer->TurnLeft();
				state = STATE::STOP;
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
		if (existCoin == true)
		{
			moveSpeed = 10.0f;
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
			if (existCoin == true)
			{
				direction = minDis.ReturnNormalization();
				direction.y = 0.0f;
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
				state = STATE::STOP;
			}
			break;
		}
		case DIRECTION::RIGHT:
		{
			if (existCoin == true)
			{
				direction = minDis.ReturnNormalization();
				direction.y = 0.0f;
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
				state = STATE::STOP;
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



void StinkyMove::Stop()
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
		}
		else
		{
			temp = fishName + L"Turn";
		}


		spriteAnimaion->ChangeAnimation(temp.c_str());
	}

#pragma region SLOWMOVE
	moveSpeed = 0.25f;
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
	else if (pos.y < -windowSize.y + 0.5f)
	{
		direction.y = 0.0f;
		GetActor()->GetTransform()->SetPosition({ pos.x, -windowSize.y + 0.5f });
		GetActor()->GetTransform()->Move2D((direction * moveSpeed * Time::DeltaTime()), __PET);

		if (pos.x > windowSize.x - 0.3f)
		{
			direction.x = 0.0f;
			GetActor()->GetTransform()->SetPosition({ windowSize.x - 0.3f,-windowSize.y + 0.5f });
		}
		else if (pos.x < -windowSize.x + 0.3f)
		{
			direction.x = 0.0f;
			GetActor()->GetTransform()->SetPosition({ -windowSize.x + 0.3f, -windowSize.y + 0.5f });
		}
	}
	else
	{
		GetActor()->GetTransform()->Move2D((direction * moveSpeed * Time::DeltaTime()), __PET);
	}
#pragma endregion

	//spriteAnimaion->ChangeAnimation(L"Goopy1Swim");
}

void StinkyMove::AppearMonster()
{
	std::wstring createAniName;
	createAniName = fishName + L"Skill";

	spriteAnimaion->ChangeAnimation(createAniName.c_str());

	if (MonsterList::GetMonsterList().size() == 0)
	{
		state = STATE::MOVING;
	}
}

void StinkyMove::Move(float _Speed)
{
	moveSpeed = _Speed;

	if (pos.x > windowSize.x - 0.3f)
	{
		direction.x = 0.0f;
		GetActor()->GetTransform()->SetPosition({ windowSize.x - 0.3f, pos.y });
		GetActor()->GetTransform()->Move2D((direction * moveSpeed * Time::DeltaTime()), __GOOPY);

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
		GetActor()->GetTransform()->Move2D((direction * moveSpeed * Time::DeltaTime()), __GOOPY);

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
		GetActor()->GetTransform()->Move2D((direction * moveSpeed * Time::DeltaTime()), __GOOPY);

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
	else if (pos.y < -windowSize.y + 0.5f)
	{
		direction.y = 0.0f;
		GetActor()->GetTransform()->SetPosition({ pos.x, -windowSize.y + 0.5f });
		GetActor()->GetTransform()->Move2D((direction * moveSpeed * Time::DeltaTime()), __GOOPY);

		if (pos.x > windowSize.x - 0.3f)
		{
			direction.x = 0.0f;
			GetActor()->GetTransform()->SetPosition({ windowSize.x - 0.3f,-windowSize.y + 0.5f });
		}
		else if (pos.x < -windowSize.x + 0.3f)
		{
			direction.x = 0.0f;
			GetActor()->GetTransform()->SetPosition({ -windowSize.x + 0.3f, -windowSize.y + 0.5f });
		}
	}
	else
	{
		GetActor()->GetTransform()->Move2D((direction * moveSpeed * Time::DeltaTime()), __GOOPY);
	}
}

void StinkyMove::Enter(Collider* _This, Collider* _Other)
{
	int a = 0;
}
void StinkyMove::Stay(Collider* _This, Collider* _Other)
{
	int a = 0;
}
void StinkyMove::Exit(Collider* _This, Collider* _Other)
{
	int a = 0;
}