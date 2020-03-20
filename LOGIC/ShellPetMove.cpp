#include "ShellPetMove.h"
//ENGINE
#include <GameWindow.h>
#include <SpriteRenderer.h>
#include <SpriteAnimation.h>

#include "ENUM.h"

ShellPetMove::ShellPetMove() : direction(0.0f), moveSpeed(1.0f), movingTime(Well512Random::Instance().GetFloatValue(0.5f, 3.0f)), spriteRenderer(nullptr), spriteAnimaion(nullptr),
isFast(false), isRotate(true)
{
}


ShellPetMove::~ShellPetMove()
{
}

bool ShellPetMove::GetFishName()
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

void ShellPetMove::Init()
{
	windowSize = (GameWindow::Inst()->GetWindowSize() / 100.0f) / 2.0f;
	direction = { -0.1f, 0.1f, 0.0f };
	STATE = STATE::MOVING;

	GetActor()->GetTransform()->SetPosition({ Well512Random::Instance().GetFloatValue(-3.0f, 3.0f) , Well512Random::Instance().GetFloatValue(-2.0f, 2.0f) });


	spriteRenderer = GetActor()->GetComponent<SpriteRenderer>();
	spriteAnimaion = GetActor()->GetComponent<SpriteAnimation>();
	curAniName = spriteAnimaion->GetCurAni()->curAnimationName;

	GetFishName();
}

void ShellPetMove::Update()
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

	switch (STATE)
	{
	case ShellPetMove::STATE::MOVING:
		Moving();
		break;
	case ShellPetMove::STATE::STOP:
		Stop();
		break;
	case ShellPetMove::STATE::SKILL:
		Skill();
		break;
	}
}

void ShellPetMove::Moving()
{

#pragma region MOVE
	movingTime -= Time::DeltaTime();

	if (movingTime < 0.0f)
	{
		movingTime = Well512Random::Instance().GetFloatValue(0.5f, 5.0f);
		moveSpeed = 1.0f;

		switch (DIR)
		{
		case ShellPetMove::LEFT:
		{
			float x = Well512Random::Instance().GetFloatValue(-1.0f, 1.0f);
			float y = -0.5f;//Well512Random::Instance().GetFloatValue(-1.0f, 1.0f);
			direction = { x, y, -3.0f };
			if (direction.x < 0.0f)
			{
				spriteRenderer->TurnLeft();
				
				


				//if (DIR == RIGHT)
				//{
				//	STATE = STATE::STOP;
				//}
			}
			else if (direction.x > 0.0f)
			{
				//spriteRenderer->TurnRight();
				STATE = STATE::STOP;
			}
			break;
		}
		case ShellPetMove::RIGHT:
		{

			//Well512Random::Instance().GetFloatValue(-1.0f, 1.0f);
			float x = Well512Random::Instance().GetFloatValue(-1.0f, 1.0f);
			float y = -0.5f;//Well512Random::Instance().GetFloatValue(-1.0f, 1.0f);
			direction = { x, y, -3.0f };
			if (direction.x < 0.0f)
			{
				//spriteRenderer->TurnLeft();
				STATE = STATE::STOP;
			}
			else if (direction.x > 0.0f)
			{
				spriteRenderer->TurnRight();
				//if (DIR == LEFT)
				//{
				//	STATE = STATE::STOP;
				//}
			}
			break;
		}

		}

	}
	else
	{
		if (pos.x > windowSize.x - 0.3f)
		{
			direction.x = 0.0f;//SetPostion
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
		///

	}
#pragma endregion
}

void ShellPetMove::Stop()
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

		STATE = STATE::MOVING;
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

void ShellPetMove::Skill()
{

}