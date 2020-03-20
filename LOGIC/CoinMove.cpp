#include "CoinMove.h"
#include "CoinList.h"

#include "ENUM.h"

#include <SpriteAnimation.h>
#include <Scene.h>
#include "GoopyList.h"
#include <Sound.h>

bool CoinMove::resetCoin = false;
float CoinMove::coinSpeed = 0.5f;

CoinMove::CoinMove() : goCoinBox(false), coinLevel(0) , eraseTime(3.0f), isBomb(false), nimbusTime(1.0f), nimbusMoveSpeed(1.5f), coinSoundCheck(false)
{
}


CoinMove::~CoinMove()
{
}


void CoinMove::Init()
{
	dir = { 0.0f, -1.0f, 0.0f };
	speed = 0.5f;

	spriteRenderer = GetActor()->GetComponent<SpriteRenderer>();
	collider = GetActor()->GetComponent<BoundingSphere>();

	collider->RegisterEnterFunction(&CoinMove::Enter, this);
	collider->RegisterStayFunction(&CoinMove::Stay, this);
	collider->RegisterExitFunction(&CoinMove::Exit, this);

	coinLevel = (int)GetActor()->GetGoopy();

}

void CoinMove::Update()
{
	if (isStop == true)
	{
		return;
	}

	pos = GetActor()->GetTransform()->GetLocalPosition();
	coinLevel = (int)GetActor()->GetGoopy();



	if (GetActor()->GetTransform()->GetPosition().y < -2.0f)
	{
		if (resetCoin == true)
		{
			eraseTime -= Time::DeltaTime();
			eraseTime /= 2.0f;
		}
		else
		{
			eraseTime -= Time::DeltaTime();
		}
		

		if (goCoinBox == true)
		{
			Vector4 dest = { 2.65f, 1.88f, 0.0f };
			dir = dest - pos;
			dir.Normalization();

			speed = 100.0f;
		}
		else
		{
			dir = { 0.0f, 0.0f, 0.0f };
			speed = 0.5f;
		}

		
		if (eraseTime < 0.0f)
		{

			if (nullptr != collider)
			{
				//PopFoodActor(collider);
				collider->Die();		//충돌체를 꺼준다
				collider = nullptr;
			}


			if (spriteRenderer->GetAlphaValue().w < 0.0f)
			{
				Actor* actor = GetActor();
				CoinList::PopMonster(actor);
				actor->Die();
				//Actor* foodActor = GetActor();
				//FoodList::PopFood(foodActor);

				//엑터 사라진다		
			}

			spriteRenderer->AlphaGradationOn();
			return;
		}		
	}
	else
	{
		if (goCoinBox == true || isStinky == true)
		{
			Vector4 dest = { 2.65f, 1.88f, 0.0f };
			dir = dest - pos;
			dir.Normalization();

			speed = 100.0f;
		}
		else
		{
			dir = { 0.0f, -1.0f, 0.0f };
			speed = coinSpeed;
		}		
	}

	if (isNimbus == true)
	{
		nimbusTime -= Time::DeltaTime();
		if (nimbusTime < 0.0f)
		{
			nimbusTime = 1.0f;
			nimbusMoveSpeed = 1.5f;
			isNimbus = false;
		}
	}


	if (isNimbus == false)
	{
		GetActor()->GetTransform()->Move2D((dir * speed * Time::DeltaTime()), 50.0f);
	}
	else
	{
		Nimbus();
	}

	


}

void CoinMove::Nimbus()
{
	nimbusMoveSpeed += 0.02f;
	GetActor()->GetTransform()->Move2D((Vector4::UP * nimbusMoveSpeed * Time::DeltaTime()), 50.0f);
}



///COL

void CoinMove::Enter(Collider* _This, Collider* _Other)
{
	switch (_Other->GetOrder())
	{
	case CG_MOUSE:
	{
		int a = 0;
		//isBomb = false;
	}
	break;

	case CG_STINKY:
	{
		goCoinBox = true;
		isBomb = false;
	}
	break;

	case CG_COINBOX:
	{
		Actor* actor = _This->GetActor();
		//actor->Die();

		CoinList::PopMonster(actor);
	}
	break;
	case CG_NIMBUS:
	{
		isNimbus = true;
	}
	break;

	/*case CG_LITTLEGOOPY:
	case CG_MIDDLEGOOPY:
	case CG_BIGGOOPY:
	case CG_CROWNGOOPY:
	case CG_PIRANA:
	case CG_ULTRAGOOPY:
	{
		if (isBomb == true)
		{
			if (goCoinBox != true)
			{
				_This->GetActor()->Die();
				_Other->GetActor()->Die();

				GoopyList::PopGoopy(_Other->GetActor());

				My_Ptr<Actor> smoke = GetScene()->CreateActor(L"SMOKE");
				Vector4 pos = { GetActor()->GetTransform()->GetLocalPosition() };
				pos.z = __UI;
				pos.x += Well512Random::Instance().GetFloatValue(-0.5f, 0.5f);
				pos.y += Well512Random::Instance().GetFloatValue(-0.5f, 0.5f);
				smoke->GetTransform()->SetLocalPosition(pos);
				smoke->GetTransform()->LocalScaleMultiple(0.45f);
				My_Ptr<SpriteRenderer>  smokeRender = smoke->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
				smokeRender->SetSprite(L"smoke.png");

				My_Ptr<SpriteAnimation> smokeAni = smoke->AddComponent<SpriteAnimation>();
				smokeAni->CreateAnimation(L"smoke", L"smoke.png", 0, 19, 0.06f, false);
			}
		}
	}
	break;*/
	}
}

void CoinMove::Stay(Collider* _This, Collider* _Other)
{
	switch (_Other->GetOrder())
	{
	case CG_MOUSE:
		{
			if (Input::Down(L"MOUSELEFT") == true)
			{
				//{ 2.65f, 1.88f, __UI } 목적지 위치벡터
				isStop = false;
				goCoinBox = true;
				if (coinSoundCheck == false)
				{
					Sound::Play(L"POINTS.wav");
					coinSoundCheck = true;
				}
				isBomb = false;
			}
		}
		break;

	case CG_STINKY:
	case CG_CLYDE:
		{
			if (coinSoundCheck == false)
			{
				Sound::Play(L"POINTS.wav");
				coinSoundCheck = true;
			}
			goCoinBox = true;
			isBomb = false;
		}
		break;

	case CG_COINBOX:
		{
			Actor* actor = _This->GetActor();
			actor->Die();

			CoinList::PopMonster(actor);
		}
		break;
	}	
}

void CoinMove::Exit(Collider* _This, Collider* _Other)
{
	int a = 0;
}