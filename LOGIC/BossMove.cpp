#include "BossMove.h"

#include "GoopyList.h"
#include "MonsterList.h"

#include "PetList.h"
#include "FoodList.h"

#include "PetList.h"
#include "FoodMove.h"
#include "MonsterMove.h"
#include <Sound.h>



BossMove::BossMove() : alienTime(3.0f), hp(1.0f)
{
}


BossMove::~BossMove()
{
}

void BossMove::Init()
{
	InitResource();

	collider = GetActor()->GetComponent<BoundingSphere>();
	collider->RegisterEnterFunction(&BossMove::Enter, this);
	collider->RegisterStayFunction(&BossMove::Stay, this);
	collider->RegisterExitFunction(&BossMove::Exit, this);

	GetActor()->GetTransform()->SetPosition(prevPos);

	attPoint = 0.02f / 3.0f;
	//hp = 1.0f;

	MONSTER = true;
}

void BossMove::Update()
{
	alienTime -= Time::DeltaTime();

	if (alienTime < 0.0f)
	{
		MonsterList::ailenPetCnt++;
		My_Ptr<Actor> monster = GetScene()->CreateActor();
		monster->GetTransform()->SetLocalPosition(pos);
		monster->GetTransform()->SetLocalScale({ 80.0f / GameWindow::Inst()->GetWindowSize().y , 80.0f / GameWindow::Inst()->GetWindowSize().y });
		monster->GetTransform()->LocalScaleMultiple(GameWindow::Inst()->GetWindowSize().y / 100.0f);
		My_Ptr<SpriteRenderer> monsterRender = monster->AddComponent<SpriteRenderer>(RENDERGROUP::RG_MONSTER);
		//Render->SetBlendOption();
		monsterRender->SetSprite(L"smallsylv.png");


		My_Ptr<SpriteRenderer>  hpRender = monster->AddComponent<SpriteRenderer>(RENDERGROUP::RG_MONSTER);
		hpRender->SetSprite(L"healthbar.png");
		hpRender->SetLocalPosition({ 0.0f, -0.5f, 0.0f });
		hpRender->UpdateOff();

		My_Ptr<SpriteAnimation> monsterAni = monster->AddComponent<SpriteAnimation>();
		monsterAni->CreateAnimation(L"Swim", L"smallsylv.png", 0, 9, 0.1f, true);
		monsterAni->CreateAnimation(L"Turn", L"smallsylv.png", 10, 19, 0.1f, false);
		monsterAni->CreateAnimation(L"Swimfast", L"smallsylv.png", 0, 9, 0.06f, true);
		monsterAni->CreateAnimation(L"Turnfast", L"smallsylv.png", 10, 19, 0.06f, false);


		My_Ptr<BoundingSphere> monsterCollider = monster->AddComponent<BoundingSphere>(CG_MONSTER);
		monsterCollider->MultipleRadius(0.7f);
		My_Ptr<MonsterMove>  monsterLogic = monster->AddComponent<MonsterMove>();
		monsterLogic->attPoint = 0.05f;
		
		MonsterList::PushMonster(monster);

		alienTime = 3.0f;
	}

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
		ShellMoving();
		break;
	case STATE::STOP:
		Stop();
		break;

	case STATE::HIT:
		//Hit();
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

		//Sound::Stop(L"MonsterBgm");
		//Sound::Play(L"AdventureBgm", L"BG Tank 1.wav", 100000);

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







void BossMove::Enter(Collider* _This, Collider* _Other)
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

void BossMove::Stay(Collider* _This, Collider* _Other)
{
	if (_Other->GetOrder() == CG_MOUSE)
	{
		if (Input::Down(L"MOUSELEFT") == true)
		{

			hp -= attPoint;
			Sound::Play(L"HIT.wav");


			hitDir = _Other->GetActor()->GetTransform()->GetLocalPosition();

			//if (state != STATE::STOP)
			//{
			//	//state = STATE::HIT;
			//	isHit = true;
			//}
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

void BossMove::Exit(Collider* _This, Collider* _Other)
{
	int a = 0;
}

