#include "MonsterMove.h"

#include "GoopyList.h"
#include "MonsterList.h"

#include "PetList.h"
#include "FoodList.h"

#include "PetList.h"
#include "FoodMove.h"



#include <Sound.h>

MonsterMove::MonsterMove() :isBalog(false)
{
}


MonsterMove::~MonsterMove()
{
}


void MonsterMove::Init()
{
	InitResource();

	collider = GetActor()->GetComponent<BoundingSphere>();
	collider->RegisterEnterFunction(&MonsterMove::Enter, this);
	collider->RegisterStayFunction(&MonsterMove::Stay, this);
	collider->RegisterExitFunction(&MonsterMove::Exit, this);

	GetActor()->GetTransform()->SetPosition(prevPos);

	attPoint = 0.02f;
	hp = 1.0f;

	MONSTER = true;
	
}

void MonsterMove::Update()
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

	if (FoodList::GetFoodList().size() != 0 && PetList::existGus == true)
	{
		std::list<Actor*> tempList = FoodList::GetFoodList();
		std::list<Actor*>::iterator begin = tempList.begin();
		std::list<Actor*>::iterator end = tempList.end();

		for (begin; begin != end; ++begin)
		{
			Vector4 coinPos;
			if (true != (*begin)->IsDeath())
			{
				

				coinPos = (*begin)->GetTransform()->GetLocalPosition();
				minDis.z = 0.0f;

				Vector4 tempDir = coinPos - pos;
				tempDir.z = 0.0f;

				findDestMap.insert(std::map<float, Actor*>::value_type(tempDir.Distance(), (*begin)));
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
			interMoveSpeed = 7.0f;
		}
	}




	switch (state)
	{
	case STATE::MOVING:
		InterMoving();
		break;
	case STATE::STOP:
		Stop();
		break;
	case STATE::HIT:
		Hit();
		break;

	case STATE::GUSEAT:
		Eat();
		break;
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


		Sound::Play(L"explode.wav");
		if (isBalog == true)
		{
			Sound::Stop(L"MonsterBgm");
			Sound::Play(L"AdventureBgm", L"BG Tank 1.wav", 100000);
			//Sound::Play();
			//
			isBalog = false;
		}
		else
		{
			MonsterList::ailenPetCnt -= 1;
			if (MonsterList::ailenPetCnt == 0)
			{
				Sound::Stop(L"MonsterBgm");
				Sound::Play(L"AdventureBgm", L"BG Tank 1.wav", 100000);
			
				GameWindow::Inst()->ChangeScene(L"EndingScene");				
			}
		}

			

		
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


void MonsterMove::Enter(Collider* _This, Collider* _Other)
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

void MonsterMove::Stay(Collider* _This, Collider* _Other)
{
	if (_Other->GetOrder() == CG_MOUSE)
	{
		if (Input::Down(L"MOUSELEFT") == true)
		{
			Sound::Play(L"HIT.wav");
			hp -= attPoint;
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
		//_Other->Die();
		_Other->GetActor()->Die();
		_Other = nullptr;
	}
	
}

void MonsterMove::Exit(Collider* _This, Collider* _Other)
{
	int a = 0;
}


void MonsterMove::Eat()
{
	if (spriteAnimaion->GetCurAni()->aniEnd == true)
	{
		state = STATE::STOP;
	}

	spriteAnimaion->ChangeAnimation(L"Eat");
}