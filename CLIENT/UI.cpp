#include "UI.h"

#include <Input.h>
//==============ENGINE================//
#include <GameWindow.h>
#include <Resources.h>
#include <Scene.h>
#include <Actor.h>
#include <Sprite.h>
#include <Texture.h>
//===============ENGINESUB===============//
//#include <SpriteAnimation.h>
#include <SpriteRenderer.h>
#include <GoopyList.h>
//=====================================//
#include "ENUM.h"

//SpriteAnimation*	spriteAnimation;;
#include "Goopy.h"
#include "Food.h"

//PET///////
//FISH
#pragma region PET

#include "Zorf.h"
#include "Walter.h"
#include "Wadsworth.h"
#include "Vert.h"
#include "Stanley.h"
#include "Shrapnel.h"
#include "Seymour.h"
#include "Presto.h"
#include "Prego.h"
#include "Nostradamus.h"
#include "Nimbus.h"
#include "Meryl.h"
#include "Itchy.h"
#include "Gumbo.h"
#include "Gash.h"
#include "Clyde.h"
#include "Blip.h"
#include "Angie.h"
#include "Amp.h"
//SHELL
#include "Stinky.h"
#include "Rufus.h"
#include "Rhubarb.h"
#include "Niko.h"
#include "Brinkley.h"
#pragma endregion

#include <CoinBox.h>
#include <Sound.h>


bool Hatch::isInit = false;
Hatch::Hatch(My_Ptr<Scene> _Scene, const wchar_t* _TextureName, Vector4 _CntInfo, int _ColOrder) : Object(_Scene, _TextureName, _CntInfo)
,isAnimation(false), collider(nullptr), foodLevel(0), foodCnt(1)
{
	if (_CntInfo.w != 0)
	{
		isAnimation = true;
	}

	Init(_ColOrder);
}

Hatch::Hatch()
{

}


Hatch::~Hatch()
{

}


bool Hatch::Init(int _ColOrder)
{
	this->InitResources(_ColOrder);
	
	if (true == isAnimation)
	{
		InitSpriteAnimation();
	}

	spriteClass = (SPRITECLASS)(_ColOrder - 10);
	AddSprite();
	return true;
}

bool Hatch::InitResources(int _ColOrder)
{
	if (isInit == false)
	{
		Resources::Load<Texture>(Path::JoinPath(scene->GetName(), name.c_str()));
		sprite = Resources::Create<Sprite>(name.c_str(), name.c_str(),
			(int)spriteCountInfo.x, (int)spriteCountInfo.y, (int)spriteCountInfo.z, (int)spriteCountInfo.w);
		isInit = true;
	}
	else
	{
		sprite = Resources::Find<Sprite>(name.c_str());
	}

	spriteCutSize = sprite->GetSpriteCutSize();
	texture = (sprite->GetTexture());


	actor->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, 0.0f });
	actor->GetTransform()->SetLocalScale({ spriteCutSize.x / GameWindow::Inst()->GetWindowSize().y , spriteCutSize.y / GameWindow::Inst()->GetWindowSize().y });
	//actor->GetTransform()->SetScale ({ 2.0f, 1.0f });
	actor->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);



	actor->GetTransform()->SetPosition({ 0.0f, 0.0f, -1.0f });

	spriteRenderer = actor->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);// 1 == player
	spriteRenderer->SetSprite(name.c_str());

	InitCollider(_ColOrder);
	return true;
}

bool Hatch::InitSpriteAnimation()
{
	spriteAnimation = actor->AddComponent<SpriteAnimation>();
	

	spriteAnimation->CreateAnimation(L"HatchOn", L"hatchanimation2.png", 3, 3, 0.1f, false);
	spriteAnimation->CreateAnimation(L"HatchMouseOn", L"hatchanimation2.png", 5, 5, 0.1f, false);
	spriteAnimation->CreateAnimation(L"HatchClick", L"hatchanimation2.png", 4, 4, 0.1f, false);


	return true;
}

bool Hatch::InitCollider(int _ColOrder)
{
	collider = actor->AddComponent<BoundingSphere>(_ColOrder);
	collider->RegisterEnterFunction(&Hatch::Enter, this);
	collider->RegisterStayFunction(&Hatch::Stay, this);
	collider->RegisterExitFunction(&Hatch::Exit, this);

	scene->colliderMgr.Link(_ColOrder, COLGROUP::CG_MOUSE);

	return true;
}


void Hatch::AddSprite()
{
	switch (spriteClass)
	{
		case Hatch::GOOPY:
		{
			Resources::Create<Sprite>(L"HatchGoopy.png", L"Goopy.png", 10, 35);
			My_Ptr<Actor> hatchGoopy = scene->CreateActor(L"HatchGoopy");
			My_Ptr<SpriteRenderer> hatchGoopyRenderer = hatchGoopy->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
			hatchGoopyRenderer->SetSprite(L"HatchGoopy.png");
			
			hatchGoopyAni = hatchGoopy->AddComponent<SpriteAnimation>();
			hatchGoopyAni->CreateAnimation(L"Goopy1Swim", L"HatchGoopy.png", 0, 9, 0.1f, true);
			hatchGoopy->GetTransform()->SetLocalPosition({ -2.73f, 2.15f, -4.0f });
			hatchGoopy->GetTransform()->SetLocalScale({ 80.0f / GameWindow::Inst()->GetWindowSize().y , 80.0f / GameWindow::Inst()->GetWindowSize().y });
			hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);
			hatchGoopy->GetTransform()->LocalScaleMultiple(0.9f);



			My_Ptr<Actor> hatchBubble = scene->CreateActor(L"HatchBubble");

			My_Ptr<SpriteRenderer> hatchBubbleRender = hatchBubble->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
			hatchBubbleRender->SetSprite(L"HatchBubble.gif");

			hatchBubble->GetTransform()->SetLocalPosition({ -2.73f, 2.15f, -6.0f });
			hatchBubble->GetTransform()->LocalScaleMultiple(0.45f);
			hatchBubbleRender->SetBlender(L"BLEND1TO1");
		}
		break;
		case Hatch::FOOD:
		{
			//Resources::Create<Sprite>(L"HatchGoopy.png", L"Goopy.png", 10, 35);
			My_Ptr<Actor> hatchGoopy = scene->CreateActor(L"FoodUI");
			My_Ptr<SpriteRenderer> foodUIRender = hatchGoopy->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
			foodUIRender->SetSprite(L"food.png");
			
			hatchGoopyAni = hatchGoopy->AddComponent<SpriteAnimation>();
			hatchGoopyAni->CreateAnimation(L"Level1UI", L"food.png", 0, 9,		0.1f, true);
			hatchGoopyAni->CreateAnimation(L"Level2UI", L"food.png", 10, 19,	0.1f, true);
			hatchGoopyAni->CreateAnimation(L"Level3UI", L"food.png", 20, 29,	0.1f, true);
			hatchGoopyAni->CreateAnimation(L"Level4UI", L"food.png", 30, 39,	0.1f, true);
			hatchGoopyAni->CreateAnimation(L"Level5UI", L"food.png", 40, 49,	0.1f, true);

			hatchGoopy->GetTransform()->SetLocalPosition({ -2.04f, 2.15f, -4.0f });
			hatchGoopy->GetTransform()->SetLocalScale({ 80.0f / GameWindow::Inst()->GetWindowSize().y , 80.0f / GameWindow::Inst()->GetWindowSize().y });
			hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);
			hatchGoopy->GetTransform()->LocalScaleMultiple(0.5f);

			//Resources::Load<Texture>(Path::JoinPath(L"AdventureScene", L"HatchBubble.gif"));
			//Resources::Create<Sprite>(L"HatchBubble.gif", L"HatchBubble.gif", 1, 1);

			My_Ptr<Actor> hatchBubble = scene->CreateActor(L"HatchBubble");

			My_Ptr<SpriteRenderer> hatchBubbleRender = hatchBubble->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
			hatchBubbleRender->SetSprite(L"HatchBubble.gif");

			hatchBubble->GetTransform()->SetLocalPosition({ -2.04f, 2.15f, -6.0f });
			hatchBubble->GetTransform()->LocalScaleMultiple(0.45f);
			hatchBubbleRender->SetBlender(L"BLEND1TO1");
		}
		break;
		case Hatch::FOODCNT:
		{
			//My_Ptr<Actor> hatchGoopy = scene->CreateActor(L"FoodUI");
			//My_Ptr<SpriteRenderer> hatchGoopyRenderer = hatchGoopy->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
			//hatchGoopyRenderer->SetSprite(L"food.png");
			//My_Ptr<SpriteAnimation>  hatchGoopyAni = hatchGoopy->AddComponent<SpriteAnimation>();
			//hatchGoopyAni->CreateAnimation(L"Level1UI", L"food.png", 0, 9, 0.1f, true);
			//hatchGoopy->GetTransform()->SetLocalPosition({ -1.47f, 2.15f, -4.0f });
			//hatchGoopy->GetTransform()->SetLocalScale({ 80.0f / GameWindow::Inst()->GetWindowSize().y , 80.0f / GameWindow::Inst()->GetWindowSize().y });
			//hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);
			//hatchGoopy->GetTransform()->LocalScaleMultiple(0.5f);

			//My_Ptr<Actor> hatchBubble = scene->CreateActor(L"HatchBubble");
			//My_Ptr<SpriteRenderer> hatchBubbleRender = hatchBubble->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
			//hatchBubbleRender->SetSprite(L"HatchBubble.gif");

			//hatchBubble->GetTransform()->SetLocalPosition({ -1.47f, 2.15f, -6.0f });
			//hatchBubble->GetTransform()->LocalScaleMultiple(0.45f);
			//hatchBubbleRender->SetBlender(L"BLEND1TO1");
		}
		break;
		case Hatch::PIRANA:
		{
			float uiXPos = -0.74f;
			//Resources::Create<Sprite>(L"HatchGoopy.png", L"Goopy.png", 10, 35);
			hatchGoopy = scene->CreateActor(L"FoodUI");
			My_Ptr<SpriteRenderer> hatchGoopyRenderer = hatchGoopy->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
			hatchGoopyRenderer->SetSprite(L"HatchGoopy.png");
			
			hatchGoopyAni = hatchGoopy->AddComponent<SpriteAnimation>();
			hatchGoopyAni->CreateAnimation(L"HatchGoopy", L"HatchGoopy.png", 40, 49, 0.1f, true);
			hatchGoopy->GetTransform()->SetLocalPosition({ uiXPos, 2.15f, -4.0f });
			hatchGoopy->GetTransform()->SetLocalScale({ 80.0f / GameWindow::Inst()->GetWindowSize().y , 80.0f / GameWindow::Inst()->GetWindowSize().y });
			hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);
			hatchGoopy->GetTransform()->LocalScaleMultiple(0.45f);

			//Resources::Load<Texture>(Path::JoinPath(L"AdventureScene", L"HatchBubble.gif"));
			//Resources::Create<Sprite>(L"HatchBubble.gif", L"HatchBubble.gif", 1, 1);

			My_Ptr<Actor> hatchBubble = scene->CreateActor(L"HatchBubble");

			My_Ptr<SpriteRenderer> hatchBubbleRender = hatchBubble->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
			hatchBubbleRender->SetSprite(L"HatchBubble.gif");

			hatchBubble->GetTransform()->SetLocalPosition({ uiXPos, 2.15f, -6.0f });
			hatchBubble->GetTransform()->LocalScaleMultiple(0.45f);
			hatchBubbleRender->SetBlender(L"BLEND1TO1");
			//My_Ptr<BoundingSphere> hatchBubbleSphere = hatchBubble->AddComponent<BoundingSphere>(COLGROUP::CG_UI_PIRANA);
		}
		break;
		case Hatch::ULTRA:
		{
			float uiXPos = -0.005f;
			//Resources::Create<Sprite>(L"HatchGoopy.png", L"Goopy.png", 10, 35);
			hatchGoopy = scene->CreateActor(L"UltraFishUI");
			My_Ptr<SpriteRenderer> hatchGoopyRenderer = hatchGoopy->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
			hatchGoopyRenderer->SetSprite(L"UltraFish.png");
			
			hatchGoopyAni = hatchGoopy->AddComponent<SpriteAnimation>();
			hatchGoopyAni->CreateAnimation(L"UltraFish.png", L"UltraFish.png", 0, 9, 0.1f, true);
			hatchGoopy->GetTransform()->SetLocalPosition({ uiXPos, 2.15f, -4.0f });
			hatchGoopy->GetTransform()->SetLocalScale({ 80.0f / GameWindow::Inst()->GetWindowSize().y , 80.0f / GameWindow::Inst()->GetWindowSize().y });
			hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);
			hatchGoopy->GetTransform()->LocalScaleMultiple(0.5f);

			//Resources::Load<Texture>(Path::JoinPath(L"AdventureScene", L"HatchBubble.gif"));
			//Resources::Create<Sprite>(L"HatchBubble.gif", L"HatchBubble.gif", 1, 1);

			My_Ptr<Actor> hatchBubble = scene->CreateActor(L"HatchBubble");

			My_Ptr<SpriteRenderer> hatchBubbleRender = hatchBubble->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
			hatchBubbleRender->SetSprite(L"HatchBubble.gif");

			hatchBubble->GetTransform()->SetLocalPosition({ uiXPos, 2.15f, -6.0f });
			hatchBubble->GetTransform()->LocalScaleMultiple(0.45f);
			hatchBubbleRender->SetBlender(L"BLEND1TO1");
			//My_Ptr<BoundingSphere> hatchBubbleSphere = hatchBubble->AddComponent<BoundingSphere>(COLGROUP::CG_UI_KINGFISH);
		}
		break;
		case Hatch::GUN:
		{
			float uiXPos = 0.71f;
			//Resources::Create<Sprite>(L"HatchGoopy.png", L"Goopy.png", 10, 35);
			hatchGoopy = scene->CreateActor(L"lazergunz");
			My_Ptr<SpriteRenderer> hatchGoopyRenderer = hatchGoopy->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
			hatchGoopyRenderer->SetSprite(L"lazergunz.png");
			
			hatchGoopyAni = hatchGoopy->AddComponent<SpriteAnimation>();
			hatchGoopyAni->CreateAnimation(L"lazergunz1", L"lazergunz.png", 0, 0, 0.1f, false);
			hatchGoopyAni->CreateAnimation(L"lazergunz2", L"lazergunz.png", 1, 1, 0.1f, false);
			hatchGoopyAni->CreateAnimation(L"lazergunz3", L"lazergunz.png", 2, 2, 0.1f, false);
			hatchGoopyAni->CreateAnimation(L"lazergunz4", L"lazergunz.png", 3, 3, 0.1f, false);
			hatchGoopyAni->CreateAnimation(L"lazergunz5", L"lazergunz.png", 4, 4, 0.1f, false);
			hatchGoopyAni->CreateAnimation(L"lazergunz6", L"lazergunz.png", 5, 5, 0.1f, false);
			hatchGoopyAni->CreateAnimation(L"lazergunz7", L"lazergunz.png", 6, 6, 0.1f, false);
			hatchGoopyAni->CreateAnimation(L"lazergunz8", L"lazergunz.png", 7, 7, 0.1f, false);
			hatchGoopyAni->CreateAnimation(L"lazergunz9", L"lazergunz.png", 8, 8, 0.1f, false);
			hatchGoopyAni->CreateAnimation(L"lazergunz10", L"lazergunz.png", 9, 9, 0.1f, false);
			hatchGoopy->GetTransform()->SetLocalPosition({ uiXPos, 2.15f, -4.0f });
			hatchGoopy->GetTransform()->SetLocalScale({ 80.0f / GameWindow::Inst()->GetWindowSize().y , 80.0f / GameWindow::Inst()->GetWindowSize().y });
			hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);
			hatchGoopy->GetTransform()->LocalScaleMultiple(0.5f);

			//Resources::Load<Texture>(Path::JoinPath(L"AdventureScene", L"HatchBubble.gif"));
			//Resources::Create<Sprite>(L"HatchBubble.gif", L"HatchBubble.gif", 1, 1);

			My_Ptr<Actor> hatchBubble = scene->CreateActor(L"HatchBubble");

			My_Ptr<SpriteRenderer> hatchBubbleRender = hatchBubble->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
			hatchBubbleRender->SetSprite(L"HatchBubble.gif");

			hatchBubble->GetTransform()->SetLocalPosition({ uiXPos, 2.15f, -6.0f });
			hatchBubble->GetTransform()->LocalScaleMultiple(0.45f);
			hatchBubbleRender->SetBlender(L"BLEND1TO1");
			//My_Ptr<BoundingSphere> hatchBubbleSphere = hatchBubble->AddComponent<BoundingSphere>(COLGROUP::CG_UI_GUN);
		}
		break;
		case Hatch::EGG:
		{
			float uiXPos = 1.45f;
			//Resources::Create<Sprite>(L"HatchGoopy.png", L"Goopy.png", 10, 35);
			hatchGoopy = scene->CreateActor(L"egg");
			My_Ptr<SpriteRenderer> hatchGoopyRenderer = hatchGoopy->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
			hatchGoopyRenderer->SetSprite(L"egg.png");
			hatchGoopyAni = hatchGoopy->AddComponent<SpriteAnimation>();
			//hatchGoopyAni->CreateAnimation(L"egg1", L"egg.png", 0, 0, 0.1f, false);
			hatchGoopyAni->CreateAnimation(L"egg2", L"egg.png", 0, 38, 0.1f, true);
			hatchGoopy->GetTransform()->SetLocalPosition({ uiXPos, 2.15f, -4.0f });
			hatchGoopy->GetTransform()->SetLocalScale({ 80.0f / GameWindow::Inst()->GetWindowSize().y , 80.0f / GameWindow::Inst()->GetWindowSize().y });
			hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);
			hatchGoopy->GetTransform()->LocalScaleMultiple(0.5f);

			My_Ptr<Actor> hatchBubble = scene->CreateActor(L"HatchBubble");

			My_Ptr<SpriteRenderer> hatchBubbleRender = hatchBubble->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
			hatchBubbleRender->SetSprite(L"HatchBubble.gif");

			hatchBubble->GetTransform()->SetLocalPosition({ uiXPos, 2.15f, -6.0f });
			hatchBubble->GetTransform()->LocalScaleMultiple(0.45f);
			hatchBubbleRender->SetBlender(L"BLEND1TO1");
			//My_Ptr<BoundingSphere> hatchBubbleSphere = hatchBubble->AddComponent<BoundingSphere>(COLGROUP::CG_UI_PETAGG);
		}
		break;
	}
}

////////COL
void Hatch::Enter(Collider* _This, Collider* _Other)
{
	switch (_This->GetOrder())
	{
	case COLGROUP::CG_UI_FISH:
	{
		int a = 0;
	}
	break;
	case COLGROUP::CG_UI_FOOD:
	{
		int a = 0;
	}
	break;
	case COLGROUP::CG_UI_FOODCNT:
	{
		int a = 0;
	}
	break;
	case COLGROUP::CG_UI_PIRANA:
	{
		int a = 0;
	}
	break;
	case COLGROUP::CG_UI_KINGFISH:
	{
		int a = 0;
	}
	break;
	case COLGROUP::CG_UI_GUN:
	{
		int a = 0;
	}
	break;
	case COLGROUP::CG_UI_PETAGG:
	{
		int a = 0;
	}
	break;
	}
}

void Hatch::Stay(Collider* _This, Collider* _Other)
{
	switch (_This->GetOrder())
	{
	case COLGROUP::CG_UI_FISH:
	{
		int a = 0;
		//spriteAnimation = _This->GetActor()->GetComponent<SpriteAnimation>();//->ChangeAnimation(L"HatchMouseOn");
		spriteAnimation->ChangeAnimation(L"HatchMouseOn");
		if (Input::Press(L"MOUSELEFT"))
		{
			spriteAnimation->ChangeAnimation(L"HatchClick");
			
		}
		if (Input::Up(L"MOUSELEFT"))
		{
			CoinBox::money -= 100;
			Goopy goopy = Goopy(scene, L"Goopy.png", { 10, 35, 0, 349 });
			GoopyList::PushGoopy(goopy.GetActor());

			Sound::Play(L"BUY.wav");
			Sound::Play(L"splash.wav");
		}
	}
	break;
	case COLGROUP::CG_UI_FOOD:
	{
		int a = 0;
		//spriteAnimation = _This->GetActor()->GetComponent<SpriteAnimation>();//->ChangeAnimation(L"HatchMouseOn");
		spriteAnimation->ChangeAnimation(L"HatchMouseOn");
		if (Input::Press(L"MOUSELEFT"))
		{
			spriteAnimation->ChangeAnimation(L"HatchClick");

			//hatchGoopyAni->ChangeAnimation();

		}
		if (Input::Up(L"MOUSELEFT"))
		{
			++foodLevel;
			CoinBox::money -= 200;
			Sound::Play(L"BUY.wav");
			switch (foodLevel)
			{
				case 0:
				{
					hatchGoopyAni->ChangeAnimation(L"Level1UI");
					Food::FoodLevelUp();
				}
					break;
				case 1:
				{
					hatchGoopyAni->ChangeAnimation(L"Level2UI");
					Food::FoodLevelUp();
				}
					break;
				case 2:
				{
					hatchGoopyAni->ChangeAnimation(L"Level3UI");
					Food::FoodLevelUp();
				}
					break;
				//case 3:
				//{
				//	//hatchGoopyAni->ChangeAnimation(L"Level4UI");
				//	Food::FoodLevelUp();
				//}
				//	break;
				//case 4:
				//{
				//	//hatchGoopyAni->ChangeAnimation(L"Level5UI");
				//	Food::FoodLevelUp();
				//}
				//	break;
			}
			
		}
	}
	break;
	case COLGROUP::CG_UI_FOODCNT:
	{
		int a = 0;
		//spriteAnimation = _This->GetActor()->GetComponent<SpriteAnimation>();//->ChangeAnimation(L"HatchMouseOn");
		spriteAnimation->ChangeAnimation(L"HatchMouseOn");
		if (Input::Down(L"MOUSELEFT"))
		{
			Sound::Play(L"BUY.wav");
			CoinBox::money -= 200;
			foodCnt++;
			if (foodCnt > 9)
			{
				foodCnt--;
			}
			Food::SetMaxFoodCount(foodCnt);
			spriteAnimation->ChangeAnimation(L"HatchClick");
		}
	}
	break;
	case COLGROUP::CG_UI_PIRANA:
	{

		int a = 0;
		//spriteAnimation = _This->GetActor()->GetComponent<SpriteAnimation>();//->ChangeAnimation(L"HatchMouseOn");
		spriteAnimation->ChangeAnimation(L"HatchMouseOn");
		if (Input::Press(L"MOUSELEFT"))
		{
			spriteAnimation->ChangeAnimation(L"HatchClick");
		}
		if (Input::Up(L"MOUSELEFT"))
		{
			Sound::Play(L"BUY.wav");
			Sound::Play(L"splash3.wav");
			CoinBox::money -= 1000;
			Goopy goopy = Goopy(scene, L"Goopy.png", { 10, 35, 0, 349 }, 20001, COLGROUP::CG_PIRANA);			
			
			GoopyList::PushGoopy(goopy.GetActor());
			//goopy.GetLogic()->SetPoint(2001);
		}
	}
	break;
	case COLGROUP::CG_UI_KINGFISH:
	{
		int a = 0;
		//spriteAnimation = _This->GetActor()->GetComponent<SpriteAnimation>();//->ChangeAnimation(L"HatchMouseOn");
		spriteAnimation->ChangeAnimation(L"HatchMouseOn");
		if (Input::Press(L"MOUSELEFT"))
		{
			spriteAnimation->ChangeAnimation(L"HatchClick");
		}
		if (Input::Up(L"MOUSELEFT"))
		{
			Sound::Play(L"SPLASHBIG.wav");

			CoinBox::money -= 5000;
			Goopy goopy = Goopy(scene, L"Goopy.png", { 10, 35, 0, 349 }, 2000001, COLGROUP::CG_ULTRAGOOPY);
			goopy.GetActor()->DebugOn();

			GoopyList::PushGoopy(goopy.GetActor());
			//goopy.GetLogic()->SetPoint(2001);
		}
	}
	break;
	case COLGROUP::CG_UI_GUN:
	{
		int a = 0;
		//spriteAnimation = _This->GetActor()->GetComponent<SpriteAnimation>();//->ChangeAnimation(L"HatchMouseOn");
		spriteAnimation->ChangeAnimation(L"HatchMouseOn");
		if (Input::Press(L"MOUSELEFT"))
		{
			CoinBox::money -= 1000;
			spriteAnimation->ChangeAnimation(L"HatchClick");
		}
	}
	break;
	case COLGROUP::CG_UI_PETAGG:
	{
		int a = 0;
		//spriteAnimation = _This->GetActor()->GetComponent<SpriteAnimation>();//->ChangeAnimation(L"HatchMouseOn");
		spriteAnimation->ChangeAnimation(L"HatchMouseOn");

		if (Input::Press(L"MOUSELEFT"))
		{
			spriteAnimation->ChangeAnimation(L"HatchClick");
		}

		if (Input::Up(L"MOUSELEFT"))
		{
			Sound::Play(L"BUY.wav");
			CoinBox::money -= 3000;

			switch (petCount)
			{
			case 0:
			{
				Stinky stinky			= Stinky	(scene,	L"stinky.png",			{ 10, 3 });
				++petCount;
			}
			break;

			case 1:
			{
				Niko	niko = Niko(scene , L"niko.png", { 10, 3 });
				++petCount;
			}
			break;
			case 2:
			{
				Itchy		itchy = Itchy(scene, L"itchy.png", { 10, 4 });
				++petCount;
			}
			break;
			case 3:
			{
				Prego		prego = Prego(scene, L"prego.png", { 10, 4 });
				++petCount;
			}
			break;
			case 4:
			{
				Zorf		zolf = Zorf(scene, L"zorf.png", { 10, 3 });
				++petCount;
			}
			break;
			case 5:
			{
				Clyde		clyde = Clyde(scene, L"clyde.png", { 10, 2 });
				++petCount;
			}
			break;
			case 6:
			{
				Vert		vert = Vert(scene, L"vert.png", { 10, 2 });
				++petCount;
				++petCount;
			}
			break;
			case 7:
			{
				//Rufus	rufus = Rufus(scene, L"rufus.png", { 10, 3 });				
			}
			break;
			case 8:
			{
				Meryl		meryl = Meryl(scene, L"meryl.png", { 10, 4 });
				++petCount;
			}
			break;
			case 9:
			{
				Wadsworth	wadsworth = Wadsworth(scene, L"wadsworth.png", { 10, 3 });
				++petCount;
			}
			break;
			case 10:
			{
				Seymour		seymour = Seymour(scene, L"seymour.png", { 10, 2 });
				++petCount;
			}
			break;
			case 11:
			{
				shrapnel	sharpnel = shrapnel(scene, L"shrapnel.png", { 10, 2 });
				++petCount;
			}
			break;
			case 12:
			{
				Gumbo		gumbo = Gumbo(scene, L"gumbo.png", { 10, 4 });
				++petCount;
			}
			break;
			case 13:
			{
				existBlip = true;
				Blip		blip = Blip(scene, L"blip.png", { 10, 2 });
				++petCount;
			}
			break;
			case 14:
			{
				Rhubarb	rhubarb = Rhubarb(scene, L"rhubarb.png", { 10, 3 });
				++petCount;
			}
			break;
			case 15:
			{
				Nimbus		nimbus = Nimbus(scene, L"nimbus.png", { 10, 2 });
				++petCount;
			}
			break;
			case 16:
			{
				Amp			amp = Amp(scene, L"amp.png", { 10, 2 });
				++petCount;
				++petCount;
			}
			break;
			case 17:
			{
				//Gash		gash = Gash(scene, L"gash.png", { 10, 3 });
				
			}
			break;
			case 18:
			{
				Angie		angie = Angie(scene, L"angie.png", { 10, 2 });
				++petCount;
				++petCount;
				++petCount;
				++petCount;
			}
			break;
			case 19:
			{
				//Presto		presto = Presto(scene, L"presto.png", { 10, 3 });
				
			}
			break;
			case 20:
			{
				//Brinkley	brinkley = Brinkley(scene, L"brink.png", { 10, 2 });
				
			}
			break;
			case 21:
			{
				//Nostradamus nostradamus = Nostradamus(scene, L"nostradamus.png", { 10, 2 });
				
			}
			break;
			case 22:
			{
				Stanley		stanley = Stanley(scene, L"stanley.png", { 10, 6 });
				++petCount;
			}
			break;
			case 23:
			{
				Walter		walter = Walter(scene, L"walter.png", { 10, 3 });
				++petCount;
			}
			break;
			case 24:
			{
				++petCount;
			}
			break;			
			}
			//Zorf			zolf		= Zorf		(GetScene(),	L"zorf.png",			{ 10, 3 });
			//Walter		walter		= Walter	(GetScene(),	L"walter.png",		{ 10, 3 });
			//Wadsworth		wadsworth	= Wadsworth	(GetScene(),	L"wadsworth.png",		{ 10, 3 });
			//Vert			vert		= Vert		(GetScene(),	L"vert.png",			{ 10, 2 });
			//Stanley		stanley		= Stanley	(GetScene(),	L"stanley.png",		{ 10, 6 });
			//shrapnel		sharpnel	= shrapnel	(GetScene(),	L"shrapnel.png",		{ 10, 2 });
			//Seymour		seymour		= Seymour	(GetScene(),	L"seymour.png",		{ 10, 2 });
			//Presto		resto		= Presto	(GetScene(),	L"presto.png",		{ 10, 3 });
			//Prego			prego		= Prego		(GetScene(),	L"prego.png",			{ 10, 4 });
			//Nostradamus	nostradamus = Nostradamus(GetScene(),	L"nostradamus.png",		{ 10, 2 });
			//Nimbus		nimbus		= Nimbus	(GetScene(),	L"nimbus.png",		{ 10, 2 });
			//Meryl			meryl		= Meryl		(GetScene(),	L"meryl.png",			{ 10, 4 });
			//Itchy			itchy		= Itchy		(GetScene(),	L"itchy.png",			{ 10, 4 });
			//Gumbo			gumbo		= Gumbo		(GetScene(),	L"gumbo.png",			{ 10, 2 });
			//Gash			gash		= Gash		(GetScene(),	L"gash.png",			{ 10, 3 });
			//Clyde			clyde		= Clyde		(GetScene(),	L"clyde.png",			{ 10, 2 });
			//Blip			blip		= Blip		(GetScene(),	L"blip.png",			{ 10, 2 });
			//Angie			angie		= Angie		(GetScene(),	L"angie.png",			{ 10, 2 });
			//Amp			amp			= Amp		(GetScene(),	L"amp.png",			{ 10, 2 });

			////SHELL
			
			//Rufus			rufus			= Rufus		(GetScene(),	L"rufus.png",			{ 10, 3 });
			//Rhubarb		rhubarb			= Rhubarb	(GetScene(),	L"rhubarb.png",		{ 10, 3 });
			//Niko			niko			= Niko		(GetScene(),	L"niko.png",			{ 10, 3 });
			//Brinkley		brinkley	= Brinkley	(GetScene(),	L"brink.png",			{ 10, 2 });


		}
	}
	break;
	}
}

void Hatch::Exit(Collider* _This, Collider* _Other)
{
	switch (_This->GetOrder())
	{
	case COLGROUP::CG_UI_FISH:
	{
		int a = 0;
		//spriteAnimation = _This->GetActor()->GetComponent<SpriteAnimation>();//->ChangeAnimation(L"HatchMouseOn");
		spriteAnimation->ChangeAnimation(L"HatchOn");
	}
	break;
	case COLGROUP::CG_UI_FOOD:
	{
		int a = 0;
		//spriteAnimation = _This->GetActor()->GetComponent<SpriteAnimation>();//->ChangeAnimation(L"HatchMouseOn");
		spriteAnimation->ChangeAnimation(L"HatchOn");
		
	}
	break;
	case COLGROUP::CG_UI_FOODCNT:
	{
		int a = 0;
		//spriteAnimation = _This->GetActor()->GetComponent<SpriteAnimation>();//->ChangeAnimation(L"HatchMouseOn");
		spriteAnimation->ChangeAnimation(L"HatchOn");
	}
	break;
	case COLGROUP::CG_UI_PIRANA:
	{
		int a = 0;
		//spriteAnimation = _This->GetActor()->GetComponent<SpriteAnimation>();//->ChangeAnimation(L"HatchMouseOn");
		spriteAnimation->ChangeAnimation(L"HatchOn");
	}
	break;
	case COLGROUP::CG_UI_KINGFISH:
	{
		int a = 0;
		//spriteAnimation = _This->GetActor()->GetComponent<SpriteAnimation>();//->ChangeAnimation(L"HatchMouseOn");
		spriteAnimation->ChangeAnimation(L"HatchOn");
	}
	break;
	case COLGROUP::CG_UI_GUN:
	{
		int a = 0;
		//spriteAnimation = _This->GetActor()->GetComponent<SpriteAnimation>();//->ChangeAnimation(L"HatchMouseOn");
		spriteAnimation->ChangeAnimation(L"HatchOn");
	}
	break;
	case COLGROUP::CG_UI_PETAGG:
	{
		int a = 0;
		//spriteAnimation = _This->GetActor()->GetComponent<SpriteAnimation>();//->ChangeAnimation(L"HatchMouseOn");
		spriteAnimation->ChangeAnimation(L"HatchOn");
	}
	break;
	}
}