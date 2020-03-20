#include "DentacleMove.h"
#include "GoopyList.h"
#include "MonsterList.h"

#include "PetList.h"
#include "FoodList.h"

#include "PetList.h"
#include "FoodMove.h"
#include <Sound.h>


DentacleMove::DentacleMove() : hp (1.0f)
{
}


DentacleMove::~DentacleMove()
{
}

void DentacleMove::Init()
{
	InitResource();

	collider = GetActor()->GetComponent<BoundingSphere>();
	collider->RegisterEnterFunction(&DentacleMove::Enter, this);
	collider->RegisterStayFunction(&DentacleMove::Stay, this);
	collider->RegisterExitFunction(&DentacleMove::Exit, this);

	GetActor()->GetTransform()->SetPosition(prevPos);

	attPoint = 0.02f / 2.0f;
	//hp = 3.0f;

	changeTime = 1.0f;

	MONSTER = true;
}

void DentacleMove::Update()
{
	changeTime -= Time::DeltaTime();

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
	if (GoopyList::GetGoopyList().size() > 0)
	{
		std::list<Actor*> tempList = GoopyList::GetGoopyList();
		std::list<Actor*>::iterator begin = tempList.begin();
		std::list<Actor*>::iterator end = tempList.end();

		for (auto& next : tempList)
		{
			Vector4 coinPos;
			if (true != next->IsDeath())
			{
				coinPos = next->GetTransform()->GetLocalPosition();
				minDis.z = 0.0f;

				Vector4 tempDir = coinPos - pos;
				tempDir.z = 0.0f;

				findDestMap.insert(std::map<float, Actor*>::value_type(tempDir.Distance(), next));
			}
			else
			{
				int a = 0;
			}
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
			interMoveSpeed = 5.0f;
		}
	}
	else
	{
		isInterchange = false;
	}	



	switch (state)
	{
	case STATE::MOVING:
		InterMoving();
		break;
	case STATE::STOP:
		Stop();
		break;
	case STATE::CHANGE:
		Change();
		break;
	case STATE::CHANGESTOP:
		ChangeStop();
		break;

	case STATE::HIT:
		Hit();
		break;
	}

	pos = GetActor()->GetTransform()->GetLocalPosition();
	if (changeTime < 0.0f)
	{
		if (isChange == false)
		{
			isChange = true;
		}
		else
		{
			isChange = false;
		}


		state = STATE::CHANGE;

		changeTime = 5.0f;
	}

	if (chompAni != nullptr && chompAni->GetCurAni()->aniEnd == true)
	{
		chomp->Die();
	}

	if (hp < 0.0f)
	{
		PetList::existGus = false;
		GetActor()->Die();
		MonsterList::PopMonster(GetActor());
		//
		Sound::Stop(L"MonsterBgm");
		Sound::Play(L"AdventureBgm", L"BG Tank 1.wav", 100000);
		Sound::Play(L"explode.wav");

		for (int i = 0; i < 5; ++i)
		{
			smoke = GetScene()->CreateActor(L"SMOKE");

			Vector4 pos = { GetActor()->GetTransform()->GetLocalPosition() };
			pos.z = __UI + (0.1f*i);

			pos.x += Well512Random::Instance().GetFloatValue(-0.5f, 0.5f);
			pos.y += Well512Random::Instance().GetFloatValue(-0.5f, 0.5f);

			smoke->GetTransform()->SetLocalPosition(pos);
			smoke->GetTransform()->LocalScaleMultiple(0.45f);
			smokeRender = smoke->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
			smokeRender->SetSprite(L"smoke.png");

			smokeAni = smoke->AddComponent<SpriteAnimation>();
			smokeAni->CreateAnimation(L"smoke", L"smoke.png", 0, 20, 0.06f, false);
		}
	}
}

void DentacleMove::Stop()
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
		if (isChange == true)
		{
			tempSwim = L"Change";
		}

		if (isFast == true)
		{
	
			tempSwim += fishName + L"Swimfast";


		}
		else
		{
			tempSwim += fishName + L"Swim";
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
		if (isChange == true)
		{
			temp = L"Change";
		}
		if (isFast == true)
		{
			temp += fishName + L"Turnfast";
		}
		else
		{
			temp += fishName + L"Turn";
		}

		if (DIR == DIRECTION::LEFT)
		{
			spriteRenderer->TurnLeft();			
		}
		else
		{
			spriteRenderer->TurnRight();			
		}

		spriteAnimaion->ChangeAnimation(temp.c_str());
	}


	moveSpeed = 0.3f;
	Move(moveSpeed);
}

void DentacleMove::Change()
{
	if (spriteAnimaion->GetCurAni()->aniEnd == true)
	{
		state = STATE::STOP;
	}


	if (isChange == true)
	{
		if (DIR == DIRECTION::LEFT)
		{
			spriteRenderer->TurnLeft();
		}
		else
		{
			spriteRenderer->TurnRight();
		}
		spriteAnimaion->ChangeAnimation(L"Change");
	}
	else
	{
		if (DIR == DIRECTION::LEFT)
		{
			spriteRenderer->TurnLeft();
		}
		else
		{
			spriteRenderer->TurnRight();
		}
		spriteAnimaion->ChangeAnimation(L"Change2");
	}
	
}

void DentacleMove::ChangeStop()
{

}

void DentacleMove::Enter(Collider* _This, Collider* _Other)
{

	if (_Other->GetOrder() == CG_MOUSE)
	{
		if (Input::Down(L"MOUSELEFT") == true)
		{
			hp -= attPoint;
		}

		return;
	}

	if (_Other->GetOrder() == CG_BALL)
	{
		hp -= (attPoint * 2.0f);
		_Other->Die();
		_Other->GetActor()->Die();
		_Other = nullptr;

		return;
	}


	if (PetList::existGus != true)
	{

		Sound::Play(L"chomp.wav");

		chomp = GetScene()->CreateActor(L"Chomp");
		My_Ptr<SpriteRenderer> chompRender = chomp->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
		chompRender->SetSprite(L"chomp.png");
		Vector4 pos = { _Other->GetTransform()->GetLocalPosition() };
		pos.z = __UI;
		chompRender->GetTransform()->SetLocalPosition(pos);
		chompRender->GetTransform()->LocalScaleMultiple(0.45f);
		chompAni = chomp->AddComponent<SpriteAnimation>();
		chompAni->CreateAnimation(L"chomp", L"chomp.png", 0, 5, 0.1f, false);



		GoopyList::PopGoopy(_Other->GetActor());
		_Other->Die();
		_Other->GetActor()->Die();
		_Other = nullptr;
	}

}

void DentacleMove::Stay(Collider* _This, Collider* _Other)
{
	if (_Other->GetOrder() == CG_MOUSE)
	{
		if (Input::Down(L"MOUSELEFT") == true)
		{
			Sound::Play(L"HIT.wav");
			if (isChange == true)
			{
				hp += attPoint;
			}
			else
			{
				hp -= attPoint;
			}
			
			
			hitDir = _Other->GetActor()->GetTransform()->GetLocalPosition();

			if (state != STATE::STOP)
			{
				state = STATE::HIT;
				isHit = true;
			}
		}

		return;
	}


	if (PetList::existGus != true)
	{
		Sound::Play(L"chomp.wav");

		chomp = GetScene()->CreateActor(L"Chomp");
		My_Ptr<SpriteRenderer> chompRender = chomp->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
		chompRender->SetSprite(L"chomp.png");
		Vector4 pos = { _Other->GetTransform()->GetLocalPosition() };
		pos.z = __UI;
		chompRender->GetTransform()->SetLocalPosition(pos);
		chompRender->GetTransform()->LocalScaleMultiple(0.45f);
		chompAni = chomp->AddComponent<SpriteAnimation>();
		chompAni->CreateAnimation(L"chomp", L"chomp.png", 0, 5, 0.1f, false);



		GoopyList::PopGoopy(_Other->GetActor());
		_Other->Die();
		_Other->GetActor()->Die();
		_Other = nullptr;
	}

}

void DentacleMove::Exit(Collider* _This, Collider* _Other)
{
	int a = 0;
}
