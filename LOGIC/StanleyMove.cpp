#include "StanleyMove.h"

#include "MonsterList.h"
#include "BallMove.h"
#include "ItchyMove.h"

StanleyMove::StanleyMove():isAngry(false), attTime(5.0f)
{
}


StanleyMove::~StanleyMove()
{
}


void StanleyMove::Init()
{
	InitResource();
}

void StanleyMove::Update()
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

	if (MonsterList::GetMonsterList().size() > 0 && isAngry == false)
	{
		state = STATE::CHANGE;
		isAngry = true;
	}
	else if(MonsterList::GetMonsterList().size() == 0)
	{
		isAngry = false;
	}

	if (isAngry == true)
	{
		attTime -= Time::DeltaTime();
	}

	if (attTime < 0.0f)
	{
		state = STATE::SKILL;
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

	case STATE::CHANGE:
	{
		Change();
	}
	break;
	
	case STATE::SKILL:
	{
		Skill();
	}
	break;


	}
}

void StanleyMove::Stop()
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
			if (isAngry == true)
			{
				tempSwim += L"Change";
			}
		}
		else
		{
			tempSwim = fishName + L"Swim";
			if (isAngry == true)
			{
				tempSwim += L"Change";
			}
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
			if (isAngry == true)
			{
				temp += L"Change";
			}
		}
		else
		{
			temp = fishName + L"Turn";
			if (isAngry == true)
			{
				temp += L"Change";
			}
		}


		spriteAnimaion->ChangeAnimation(temp.c_str());
	}


	moveSpeed = 0.3f;
	Move(moveSpeed);
}



void StanleyMove::Change()
{
	if (spriteAnimaion->GetCurAni()->aniEnd == true)
	{
		state = STATE::STOP;
		return;
	}

	spriteAnimaion->ChangeAnimation(L"stanleyChange");

	Move(moveSpeed);
}

void StanleyMove::Skill()
{
	if (spriteAnimaion->GetCurAni()->aniEnd == true)
	{
		state = STATE::STOP;
		attTime = 5.0f;

		coin = GetScene()->CreateActor(L"Coin");


		coin->GetTransform()->SetLocalScale({ 50.0f / GameWindow::Inst()->GetWindowSize().y , 50.0f / GameWindow::Inst()->GetWindowSize().y });
		coin->GetTransform()->LocalScaleMultiple(GameWindow::Inst()->GetWindowSize().y / 100.0f);
		Vector4 coinpos = GetActor()->GetTransform()->GetLocalPosition();

		if (DIR == DIRECTION::LEFT)
		{
			coinpos.x -= 0.3f;
		}
		else
		{
			coinpos.x += 0.3f;
		}


		coinpos.z = pos.z - 10.0f;
		coin->GetTransform()->SetLocalPosition(coinpos);


		My_Ptr<SpriteRenderer> punchSprite = coin->AddComponent<SpriteRenderer>(RENDERGROUP::RG_COIN);
		punchSprite->SetSprite(L"balls.png");

		if (DIR == DIRECTION::LEFT)
		{
			punchSprite->TurnLeft();
		}
		else
		{
			punchSprite->TurnRight();
		}

		My_Ptr<SpriteAnimation> punchAni = coin->AddComponent<SpriteAnimation>();

		int num = Well512Random::Instance().GetValue(0, 3);

		switch (num)
		{
		case 0:
		{
			punchAni->CreateAnimation(L"base1", L"balls.png", 0, 9, 0.1f, true);
		}
			break;
		case 1:
		{
			punchAni->CreateAnimation(L"base2", L"balls.png", 10, 19, 0.1f, true);
		}
			break;
		case 2:
		{
			punchAni->CreateAnimation(L"base3", L"balls.png", 20, 29, 0.1f, true);
		}
			break;
		case 3:
		{
			punchAni->CreateAnimation(L"base4", L"balls.png", 30, 39, 0.1f, true);
		}
			break;
		}
		


		My_Ptr <BoundingSphere> punchCol = coin->AddComponent<BoundingSphere>(COLGROUP::CG_BALL);
		punchCol->SetLocalScale(0.5f);

		coin->AddComponent<BallMove>();

	}

	spriteAnimaion->ChangeAnimation(L"stanleyAttack");

	//if (isPunch == false)
	//{
	//	coin = GetScene()->CreateActor(L"Coin");


	//	coin->GetTransform()->SetLocalScale({ 160.0f / GameWindow::Inst()->GetWindowSize().y , 80.0f / GameWindow::Inst()->GetWindowSize().y });
	//	coin->GetTransform()->LocalScaleMultiple(GameWindow::Inst()->GetWindowSize().y / 100.0f);
	//	Vector4 coinpos = GetActor()->GetTransform()->GetLocalPosition();

	//	if (DIR == DIRECTION::LEFT)
	//	{
	//		coinpos.x -= 0.9f;
	//	}
	//	else
	//	{
	//		coinpos.x += 0.9f;
	//	}


	//	//coinpos.z = __UI;
	//	coin->GetTransform()->SetLocalPosition(coinpos);


	//	My_Ptr<SpriteRenderer> punchSprite = coin->AddComponent<SpriteRenderer>(RENDERGROUP::RG_COIN);
	//	punchSprite->SetSprite(L"punch.png");

	//	if (DIR == DIRECTION::LEFT)
	//	{
	//		punchSprite->TurnLeft();
	//	}
	//	else
	//	{
	//		punchSprite->TurnRight();
	//	}

	//	My_Ptr<SpriteAnimation> punchAni = coin->AddComponent<SpriteAnimation>();


	//	punchAni->CreateAnimation(L"base", L"punch.png", 0, 7, 0.15f, false);


	//	My_Ptr < BoundingBox> punchCol = coin->AddComponent<BoundingBox>(COLGROUP::CG_PUNCH);
	//	punchCol->SetLocalScale(0.5f);

	//	isPunch = true;
	//}

	//if (spriteAnimaion->GetCurAni()->aniEnd == true)
	//{
	//	state = STATE::STOP;
	//	coin->Die();
	//	coin = nullptr;
	//	isPunch = false;
	//}
	//spriteAnimaion->ChangeAnimation(L"walterSkill");


}

void StanleyMove::Enter(Collider* _This, Collider* _Other)
{
	int a = 0;
}
void StanleyMove::Stay(Collider* _This, Collider* _Other)
{


}
void StanleyMove::Exit(Collider* _This, Collider* _Other)
{

}
