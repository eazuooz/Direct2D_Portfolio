#include "CreateCoin.h"
#include <Scene.h>
#include <GameWindow.h>

#include <SpriteRenderer.h>
#include <SpriteAnimation.h>
#include <BoundingSphere.h>

#include "CoinMove.h"
#include "CoinList.h"


#include "ENUM.h"

bool CreateCoin::makeCoin = false;

CreateCoin::CreateCoin(int _Level)
{
	coinLevel = _Level;
}

CreateCoin::CreateCoin() :  coinLevel(0)
{
}


CreateCoin::~CreateCoin()
{
}


void CreateCoin::Init()
{
	crateTime = 10.0f;
	coinLevel = (int)GetActor()->GetGoopy();
}

void CreateCoin::Update()
{
	crateTime -= Time::DeltaTime();
	
	if (makeCoin == true)
	{
		crateTime = -1.0f;

		//makeCoin = false;
	}
	

	if (crateTime < 0.0f)
	{
		if (GetActor()->GetGoopy() > 0)
		{
			coin = GetScene()->CreateActor(L"Coin");
			coin->SetGoopy(GetActor()->GetGoopy());

			coin->GetTransform()->SetLocalScale({ 72.0f / GameWindow::Inst()->GetWindowSize().y , 72.0f / GameWindow::Inst()->GetWindowSize().y });
			coin->GetTransform()->LocalScaleMultiple(GameWindow::Inst()->GetWindowSize().y / 100.0f);
			Vector4 pos = GetActor()->GetTransform()->GetLocalPosition();
			pos.z = __UI;
			coin->GetTransform()->SetLocalPosition(pos);


			My_Ptr<SpriteRenderer> spriteRenderer = coin->AddComponent<SpriteRenderer>(RENDERGROUP::RG_COIN);
			spriteRenderer->SetSprite(L"money.png");

			My_Ptr<SpriteAnimation> spriteAnimation = coin->AddComponent<SpriteAnimation>();

			coinLevel = GetActor()->GetGoopy();
			switch (coinLevel)
			{
			case 1:
			{
				spriteAnimation->CreateAnimation(L"Level1", L"money.png", 0, 9, 0.08f, true);
			}
			break;
			case 2:
			{
				spriteAnimation->CreateAnimation(L"Level2", L"money.png", 10, 19, 0.08f, true);
			}
			break;
			case 3:
			{
				spriteAnimation->CreateAnimation(L"Level3", L"money.png", 20, 29, 0.08f, true);
			}
			break;
			case 4:
			{
				spriteAnimation->CreateAnimation(L"Level4", L"money.png", 30, 39, 0.08f, true);
			}
			break;
			case 5:
			{
				spriteAnimation->CreateAnimation(L"Level5", L"money.png", 40, 49, 0.08f, true);
			}
			break;
			case 6:
			{
				spriteAnimation->CreateAnimation(L"Level6", L"money.png", 50, 59, 0.08f, true);
			}
			break;
			}


			My_Ptr < BoundingSphere> collider = coin->AddComponent<BoundingSphere>(COLGROUP::CG_COIN);
			collider->MultipleRadius(0.5f);


			coin->AddComponent<CoinMove>();

			CoinList::PushCoin(coin);
			//foodMove = actor->AddComponent<FoodMove>();
		}

		crateTime = 10.0f;
	}
}
