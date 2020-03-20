#include "EndingUpdater.h"
#include <Input.h>
#include <GameWindow.h>

#include <Camera.h>
#include <SpriteRenderer.h>
#include <Texture.h>
#include <Sprite.h>
#include <SpriteAnimation.h>
#include <RectRenderer.h>
#include <BoundingBox.h>
#include <BoundingSphere.h>
#include <GraphicDebug.h>
#include <BubbleMove.h>

#include <FontRenderer.h>

#include "ENUM.h"

#include <CreditMove.h>
#include <EndAngieMove.h>

#include "Rufus.h"
#include "Gash.h"
#include "Presto.h"
#include "Brinkley.h"
#include "Nostradamus.h"

#include <Sound.h>

//class Test
//{
//private:
//	int HP = 1000000;
//
//public:
//	void Enter(Collider* _This, Collider* _Other)
//	{
//		//GameWindow::MainGameWindow()->ChangeScene(L"EndingScene");
//
//		std::cout << "충돌했습니다." << std::endl;
//		_Other->GetActor()->Die();
//	}
//
//	void Exit(Collider* _This, Collider* _Other)
//	{
//		std::cout << "충돌 끝났습니다." << std::endl;
//	}
//
//	void Stay(Collider* _This, Collider* _Other)
//	{
//		--HP;
//		std::cout << "충돌 중입니다." << HP << std::endl;
//	}
//};

EndingUpdater::EndingUpdater()
{
}


EndingUpdater::~EndingUpdater()
{
}

void EndingUpdater::Loading()
{
	Sound::Stop(L"AdventureBgm");

	Sound::Play(L"EndingBgm", L"BG BonusRound.wav", 10000);


	GraphicDebug::DebugOFF();
	Path::CreatePath(L"EndingScene", L"Texture\\EndingScene");
	//CAMERA
	//CAMERA
	My_Ptr<Actor> mainCam = GetScene()->CreateActor(L"PLAYERCAMERA");
	mainCam->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, -100.0f });
	My_Ptr<Camera> playerCamera = mainCam->AddComponent<Camera>(RENDERGROUP::RG_BACKGROUND, RENDERGROUP::RG_FOOD, RENDERGROUP::RG_PLAYER,
		RENDERGROUP::RG_PET, RENDERGROUP::RG_MONSTER, RENDERGROUP::RG_UI, RENDERGROUP::RG_COIN);
	playerCamera->SetProjMode(PROJMODE::ORTHOGONAL);
	playerCamera->SetArea(GameWindow::Inst()->GetWindowSize().x / 100.0f, GameWindow::Inst()->GetWindowSize().y / 100.0f);



	BubbleMove::EndingSceneOn();


	My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");

	My_Ptr<FontRenderer> font = hatchGoopy->AddComponent< FontRenderer>(RG_BACKGROUND);
	font->SetFont(L"Silkscreen");
	std::wstring text;
	text += L"CONGRATULATIONS!\n\n YOUVE SUCCESSFULLYVANQUISHED THE ALIEN HORDES!\n";
	text += L"(축하합니다! 당신은 외계인무리로 부터 성공적으로 물고기를 지켜냈습니다!)\n";

	text += L"THE EPIC CONFLICT BETWEEN FISH AND EVIL \nFINALLY COME TO A CLOSE\n";
	text += L"(물고기와 에일리언 사이의 전쟁은 마침내 끝이 났습니다.)\n";

	text += L"THANKS TO YOU, AQUARIUM OWNERS CAN\n SLEEP EASY TONIGHT! \n ";
	text += L"(감사합니다, 이것으로 광란의 수족관은 평화로워 졌습니다.) \n\n\n ";

	text += L"MANY A PET GAVE THEIR LIVES IN THE FINAL BATTLE,\n BUT DO NOT GRIEVE, LIITLE ONE!\n ";
	text += L"(많은 물고기들이 전투에서 그들에게 목숨을 잃었습니다.)\n (그러나 포기하지 마십시오.)\n\n";

	text += L"ANGIE PURPOSE FULLY SAT OUT OF THE FIGHT, AND\n ";
	text += L"WORD IS SHE'S GOT A FEW TRICKS UP HER SLEEVES...\n\n";
	text += L"ALSO, YOU SAVED A FAIR NUMBER OF PETS YOURSELF\n GOOD JOB!!\n\n\n\n THANKS FOR PLAYING!\nWE'LL SEE YOU NEXT GAME!\n\n";
	text += L"(당신은 여러 물고기들을 구해냈습니다. 정말 잘하셨습니다.)\n";
	text += L"(플레이 해주셔서 감사합니다. 다음게임에서 또봅시다!)\n\n\n\n";

	text += L"I N S A N I Q U A R I U M\n(  광  란  의  수  족  관  )\n\n\n\n";

	text += L"CAST";

	font->SetText(text, 18.0f, Vector4::WHITE);


	hatchGoopy->GetTransform()->SetLocalPosition({ 0.0f, -4.0f, __GOOPY });
	hatchGoopy->GetTransform()->SetLocalScale({ 80.0f / GameWindow::Inst()->GetWindowSize().y , 80.0f / GameWindow::Inst()->GetWindowSize().y });
	hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);
	hatchGoopy->GetTransform()->LocalScaleMultiple(0.3f);
	hatchGoopy->AddComponent<CreditMove>();
	//hatchGoopy->GetTransform()->SetLocalPosition({ 1.0f, 0.0f, __GOOPY });



	Rufus		rufus = Rufus(GetScene(), L"rufus.png", { 10, 3 });			
	rufus.GetActor()->GetTransform()->SetLocalPosition({5.0f, 5.0f, 5.0f});
	Gash		gash = Gash(GetScene(), L"gash.png", { 10, 3 });
	gash.GetActor()->GetTransform()->SetLocalPosition({ 5.0f, 5.0f, 5.0f });
	Presto		presto = Presto(GetScene(), L"presto.png", { 10, 3 });
	presto.GetActor()->GetTransform()->SetLocalPosition({ 5.0f, 5.0f, 5.0f });
	Brinkley	brinkley = Brinkley(GetScene(), L"brink.png", { 10, 2 });
	brinkley.GetActor()->GetTransform()->SetLocalPosition({ 5.0f, 5.0f, 5.0f });
	Nostradamus nostradamus = Nostradamus(GetScene(), L"nostradamus.png", { 10, 2 });
	nostradamus.GetActor()->GetTransform()->SetLocalPosition({ 5.0f, 5.0f, 5.0f });



#pragma region GOPPY MONSTER
	
	float tempValue = -2.0f;

	{
		My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");
		My_Ptr<SpriteRenderer> hatchGoopyRenderer = hatchGoopy->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
		hatchGoopyRenderer->SetSprite(L"Goopy0.png");
		//hatchGoopyRenderer->SetBlender(L"BLEND1TO1");
		My_Ptr<SpriteAnimation>  hatchGoopyAni = hatchGoopy->AddComponent<SpriteAnimation>();
		//hatchGoopyAni->CreateAnimation(L"egg1", L"egg.png", 0, 0, 0.1f, false);
		hatchGoopyAni->CreateAnimation(L"basic", L"Goopy0.png", 0, 9, 0.1f, true);
		hatchGoopy->GetTransform()->SetLocalPosition({ -1.0f, -12.0f + tempValue, __UI });
		hatchGoopy->GetTransform()->SetLocalScale({ 80.0f / GameWindow::Inst()->GetWindowSize().y , 80.0f / GameWindow::Inst()->GetWindowSize().y });
		hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);

		My_Ptr<FontRenderer> font = hatchGoopy->AddComponent< FontRenderer>(RG_BACKGROUND);
		font->SetFont(L"Silkscreen");
		font->SetText(L"GUPPY", 18.0f, Vector4::WHITE);
		font->SetPos({0.0f, 40.0f, 0.0f, 0.0f});

		//hatchGoopy->GetTransform()->LocalScaleMultiple(0.3f);
		hatchGoopy->AddComponent<CreditMove>();
	}
	{
		My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");
		My_Ptr<SpriteRenderer> hatchGoopyRenderer = hatchGoopy->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
		hatchGoopyRenderer->SetSprite(L"Goopy0.png");
		//hatchGoopyRenderer->SetBlender(L"BLEND1TO1");
		My_Ptr<SpriteAnimation>  hatchGoopyAni = hatchGoopy->AddComponent<SpriteAnimation>();
		//hatchGoopyAni->CreateAnimation(L"egg1", L"egg.png", 0, 0, 0.1f, false);
		hatchGoopyAni->CreateAnimation(L"basic", L"Goopy0.png", 40, 49, 0.1f, true);
		hatchGoopy->GetTransform()->SetLocalPosition({ 1.0f, -12.0f + tempValue, __UI });
		hatchGoopy->GetTransform()->SetLocalScale({ 80.0f / GameWindow::Inst()->GetWindowSize().y , 80.0f / GameWindow::Inst()->GetWindowSize().y });
		hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);

		My_Ptr<FontRenderer> font = hatchGoopy->AddComponent< FontRenderer>(RG_BACKGROUND);
		font->SetFont(L"Silkscreen");
		font->SetText(L"CANIVORE", 18.0f, Vector4::WHITE);
		font->SetPos({ 0.0f, 40.0f, 0.0f, 0.0f });

		//hatchGoopy->GetTransform()->LocalScaleMultiple(0.3f);
		hatchGoopy->AddComponent<CreditMove>();
	}
	{
		My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");
		My_Ptr<SpriteRenderer> hatchGoopyRenderer = hatchGoopy->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
		hatchGoopyRenderer->SetSprite(L"Goopy0.png");
		//hatchGoopyRenderer->SetBlender(L"BLEND1TO1");
		My_Ptr<SpriteAnimation>  hatchGoopyAni = hatchGoopy->AddComponent<SpriteAnimation>();
		//hatchGoopyAni->CreateAnimation(L"egg1", L"egg.png", 0, 0, 0.1f, false);
		hatchGoopyAni->CreateAnimation(L"basic", L"Goopy0.png", 30, 39, 0.1f, true);
		hatchGoopy->GetTransform()->SetLocalPosition({ -1.0f, -14.0f + tempValue, __UI });
		hatchGoopy->GetTransform()->SetLocalScale({ 80.0f / GameWindow::Inst()->GetWindowSize().y , 80.0f / GameWindow::Inst()->GetWindowSize().y });
		hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);

		My_Ptr<FontRenderer> font = hatchGoopy->AddComponent< FontRenderer>(RG_BACKGROUND);
		font->SetFont(L"Silkscreen");
		font->SetText(L"CROWN GUPPY", 18.0f, Vector4::WHITE);
		font->SetPos({ 0.0f, 40.0f, 0.0f, 0.0f });

		//hatchGoopy->GetTransform()->LocalScaleMultiple(0.3f);
		hatchGoopy->AddComponent<CreditMove>();
	}
	{
		My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");
		My_Ptr<SpriteRenderer> hatchGoopyRenderer = hatchGoopy->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
		hatchGoopyRenderer->SetSprite(L"UltraFish.png");
		//hatchGoopyRenderer->SetBlender(L"BLEND1TO1");
		My_Ptr<SpriteAnimation>  hatchGoopyAni = hatchGoopy->AddComponent<SpriteAnimation>();
		//hatchGoopyAni->CreateAnimation(L"egg1", L"egg.png", 0, 0, 0.1f, false);
		hatchGoopyAni->CreateAnimation(L"basic", L"UltraFish.png", 0, 9, 0.1f, true);
		hatchGoopy->GetTransform()->SetLocalPosition({ 1.0f, -14.0f + tempValue, __UI });
		hatchGoopy->GetTransform()->SetLocalScale({ 160.0f / GameWindow::Inst()->GetWindowSize().y , 160.0f / GameWindow::Inst()->GetWindowSize().y });
		hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);

		My_Ptr<FontRenderer> font = hatchGoopy->AddComponent< FontRenderer>(RG_BACKGROUND);
		font->SetFont(L"Silkscreen");
		font->SetText(L"ULTRA VORE", 18.0f, Vector4::WHITE);
		font->SetPos({ 0.0f, 40.0f, 0.0f, 0.0f });

		//hatchGoopy->GetTransform()->LocalScaleMultiple(0.3f);
		hatchGoopy->AddComponent<CreditMove>();
	}
	//MONSTER

	{
		My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");
		My_Ptr<SpriteRenderer> hatchGoopyRenderer = hatchGoopy->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
		hatchGoopyRenderer->SetSprite(L"balrog.png");
		//hatchGoopyRenderer->SetBlender(L"BLEND1TO1");
		My_Ptr<SpriteAnimation>  hatchGoopyAni = hatchGoopy->AddComponent<SpriteAnimation>();
		//hatchGoopyAni->CreateAnimation(L"egg1", L"egg.png", 0, 0, 0.1f, false);
		hatchGoopyAni->CreateAnimation(L"basic", L"balrog.png", 0, 9, 0.1f, true);
		hatchGoopy->GetTransform()->SetLocalPosition({ -1.0f, -16.0f + tempValue, __UI });
		hatchGoopy->GetTransform()->SetLocalScale({ 160.0f / GameWindow::Inst()->GetWindowSize().y , 160.0f / GameWindow::Inst()->GetWindowSize().y });
		hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);

		My_Ptr<FontRenderer> font = hatchGoopy->AddComponent< FontRenderer>(RG_BACKGROUND);
		font->SetFont(L"Silkscreen");
		font->SetText(L"BALOG", 18.0f, Vector4::WHITE);
		font->SetPos({ 0.0f, 70.0f, 0.0f, 0.0f });

		//hatchGoopy->GetTransform()->LocalScaleMultiple(0.3f);
		hatchGoopy->AddComponent<CreditMove>();
	}
	{
		My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");
		My_Ptr<SpriteRenderer> hatchGoopyRenderer = hatchGoopy->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
		hatchGoopyRenderer->SetSprite(L"gus.png");
		//hatchGoopyRenderer->SetBlender(L"BLEND1TO1");
		My_Ptr<SpriteAnimation>  hatchGoopyAni = hatchGoopy->AddComponent<SpriteAnimation>();
		//hatchGoopyAni->CreateAnimation(L"egg1", L"egg.png", 0, 0, 0.1f, false);
		hatchGoopyAni->CreateAnimation(L"basic", L"gus.png", 0, 9, 0.1f, true);
		hatchGoopy->GetTransform()->SetLocalPosition({ 1.0f, -16.0f + tempValue, __UI });
		hatchGoopy->GetTransform()->SetLocalScale({ 160.0f / GameWindow::Inst()->GetWindowSize().y , 160.0f / GameWindow::Inst()->GetWindowSize().y });
		hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);

		My_Ptr<FontRenderer> font = hatchGoopy->AddComponent< FontRenderer>(RG_BACKGROUND);
		font->SetFont(L"Silkscreen");
		font->SetText(L"GUS", 18.0f, Vector4::WHITE);
		font->SetPos({ 0.0f, 70.0f, 0.0f, 0.0f });

		//hatchGoopy->GetTransform()->LocalScaleMultiple(0.3f);
		hatchGoopy->AddComponent<CreditMove>();
	}


	{
		My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");
		My_Ptr<SpriteRenderer> hatchGoopyRenderer = hatchGoopy->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
		hatchGoopyRenderer->SetSprite(L"psychosquid.png");
		//hatchGoopyRenderer->SetBlender(L"BLEND1TO1");
		My_Ptr<SpriteAnimation>  hatchGoopyAni = hatchGoopy->AddComponent<SpriteAnimation>();
		//hatchGoopyAni->CreateAnimation(L"egg1", L"egg.png", 0, 0, 0.1f, false);
		hatchGoopyAni->CreateAnimation(L"basic", L"psychosquid.png", 0, 9, 0.1f, true);
		hatchGoopy->GetTransform()->SetLocalPosition({ -1.0f, -18.0f + tempValue, __UI });
		hatchGoopy->GetTransform()->SetLocalScale({ 160.0f / GameWindow::Inst()->GetWindowSize().y , 160.0f / GameWindow::Inst()->GetWindowSize().y });
		hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);

		My_Ptr<FontRenderer> font = hatchGoopy->AddComponent< FontRenderer>(RG_BACKGROUND);
		font->SetFont(L"Silkscreen");
		font->SetText(L"PSYCHOSQUID", 18.0f, Vector4::WHITE);
		font->SetPos({ 0.0f, 70.0f, 0.0f, 0.0f });

		//hatchGoopy->GetTransform()->LocalScaleMultiple(0.3f);
		hatchGoopy->AddComponent<CreditMove>();
	}
	{
		My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");
		My_Ptr<SpriteRenderer> hatchGoopyRenderer = hatchGoopy->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
		hatchGoopyRenderer->SetSprite(L"ulysses.png");
		//hatchGoopyRenderer->SetBlender(L"BLEND1TO1");
		My_Ptr<SpriteAnimation>  hatchGoopyAni = hatchGoopy->AddComponent<SpriteAnimation>();
		//hatchGoopyAni->CreateAnimation(L"egg1", L"egg.png", 0, 0, 0.1f, false);
		hatchGoopyAni->CreateAnimation(L"basic", L"ulysses.png", 0, 9, 0.1f, true);
		hatchGoopy->GetTransform()->SetLocalPosition({ 1.0f, -18.0f + tempValue, __UI });
		hatchGoopy->GetTransform()->SetLocalScale({ 160.0f / GameWindow::Inst()->GetWindowSize().y , 160.0f / GameWindow::Inst()->GetWindowSize().y });
		hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);

		My_Ptr<FontRenderer> font = hatchGoopy->AddComponent< FontRenderer>(RG_BACKGROUND);
		font->SetFont(L"Silkscreen");
		font->SetText(L"ULYSSES", 18.0f, Vector4::WHITE);
		font->SetPos({ 0.0f, 70.0f, 0.0f, 0.0f });

		//hatchGoopy->GetTransform()->LocalScaleMultiple(0.3f);
		hatchGoopy->AddComponent<CreditMove>();
	}

	{
		My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");
		My_Ptr<SpriteRenderer> hatchGoopyRenderer = hatchGoopy->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
		hatchGoopyRenderer->SetSprite(L"boss.png");
		//hatchGoopyRenderer->SetBlender(L"BLEND1TO1");
		My_Ptr<SpriteAnimation>  hatchGoopyAni = hatchGoopy->AddComponent<SpriteAnimation>();
		//hatchGoopyAni->CreateAnimation(L"egg1", L"egg.png", 0, 0, 0.1f, false);
		hatchGoopyAni->CreateAnimation(L"basic", L"boss.png", 0, 9, 0.1f, true);
		hatchGoopy->GetTransform()->SetLocalPosition({ -1.0f, -20.0f + tempValue, __UI });
		hatchGoopy->GetTransform()->SetLocalScale({ 160.0f / GameWindow::Inst()->GetWindowSize().y , 160.0f / GameWindow::Inst()->GetWindowSize().y });
		hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);

		My_Ptr<FontRenderer> font = hatchGoopy->AddComponent< FontRenderer>(RG_BACKGROUND);
		font->SetFont(L"Silkscreen");
		font->SetText(L"CYRAX", 18.0f, Vector4::WHITE);
		font->SetPos({ 0.0f, 70.0f, 0.0f, 0.0f });

		//hatchGoopy->GetTransform()->LocalScaleMultiple(0.3f);
		hatchGoopy->AddComponent<CreditMove>();
	}



#pragma endregion

	{
		My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");
		My_Ptr<SpriteRenderer> hatchGoopyRenderer = hatchGoopy->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
		hatchGoopyRenderer->SetSprite(L"stinky.png");
		//hatchGoopyRenderer->SetBlender(L"BLEND1TO1");
		My_Ptr<SpriteAnimation>  hatchGoopyAni = hatchGoopy->AddComponent<SpriteAnimation>();
		//hatchGoopyAni->CreateAnimation(L"egg1", L"egg.png", 0, 0, 0.1f, false);
		hatchGoopyAni->CreateAnimation(L"basic", L"stinky.png", 0, 9, 0.1f, true);
		hatchGoopy->GetTransform()->SetLocalPosition({ 1.0f, -22.0f + tempValue, __UI });
		hatchGoopy->GetTransform()->SetLocalScale({ 80.0f / GameWindow::Inst()->GetWindowSize().y , 80.0f / GameWindow::Inst()->GetWindowSize().y });
		hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);

		My_Ptr<FontRenderer> font = hatchGoopy->AddComponent< FontRenderer>(RG_BACKGROUND);
		font->SetFont(L"Silkscreen");
		font->SetText(L"STINKY", 18.0f, Vector4::WHITE);
		font->SetPos({ 0.0f, 40.0f, 0.0f, 0.0f });

		//hatchGoopy->GetTransform()->LocalScaleMultiple(0.3f);
		hatchGoopy->AddComponent<CreditMove>();
	}
	 
	{
		My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");
		My_Ptr<SpriteRenderer> hatchGoopyRenderer = hatchGoopy->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
		hatchGoopyRenderer->SetSprite(L"niko.png");
		//hatchGoopyRenderer->SetBlender(L"BLEND1TO1");
		My_Ptr<SpriteAnimation>  hatchGoopyAni = hatchGoopy->AddComponent<SpriteAnimation>();
		//hatchGoopyAni->CreateAnimation(L"egg1", L"egg.png", 0, 0, 0.1f, false);
		hatchGoopyAni->CreateAnimation(L"basic", L"niko.png", 0, 9, 0.1f, true);
		hatchGoopy->GetTransform()->SetLocalPosition({ -1.0f, -22.0f + tempValue, __UI });
		hatchGoopy->GetTransform()->SetLocalScale({ 80.0f / GameWindow::Inst()->GetWindowSize().y , 80.0f / GameWindow::Inst()->GetWindowSize().y });
		hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);

		My_Ptr<FontRenderer> font = hatchGoopy->AddComponent< FontRenderer>(RG_BACKGROUND);
		font->SetFont(L"Silkscreen");
		font->SetText(L"NIKO", 18.0f, Vector4::WHITE);
		font->SetPos({ 0.0f, 40.0f, 0.0f, 0.0f });

		//hatchGoopy->GetTransform()->LocalScaleMultiple(0.3f);
		hatchGoopy->AddComponent<CreditMove>();
	}

	//
	{
		My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");
		My_Ptr<SpriteRenderer> hatchGoopyRenderer = hatchGoopy->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
		hatchGoopyRenderer->SetSprite(L"itchy.png");
		//hatchGoopyRenderer->SetBlender(L"BLEND1TO1");
		My_Ptr<SpriteAnimation>  hatchGoopyAni = hatchGoopy->AddComponent<SpriteAnimation>();
		//hatchGoopyAni->CreateAnimation(L"egg1", L"egg.png", 0, 0, 0.1f, false);
		hatchGoopyAni->CreateAnimation(L"basic", L"itchy.png", 0, 9, 0.1f, true);
		hatchGoopy->GetTransform()->SetLocalPosition({ 1.0f, -24.0f + tempValue, __UI });
		hatchGoopy->GetTransform()->SetLocalScale({ 80.0f / GameWindow::Inst()->GetWindowSize().y , 80.0f / GameWindow::Inst()->GetWindowSize().y });
		hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);

		My_Ptr<FontRenderer> font = hatchGoopy->AddComponent< FontRenderer>(RG_BACKGROUND);
		font->SetFont(L"Silkscreen");
		font->SetText(L"ITCHY", 18.0f, Vector4::WHITE);
		font->SetPos({ 0.0f, 40.0f, 0.0f, 0.0f });

		//hatchGoopy->GetTransform()->LocalScaleMultiple(0.3f);
		hatchGoopy->AddComponent<CreditMove>();
	}

	{
		My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");
		My_Ptr<SpriteRenderer> hatchGoopyRenderer = hatchGoopy->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
		hatchGoopyRenderer->SetSprite(L"prego.png");
		//hatchGoopyRenderer->SetBlender(L"BLEND1TO1");
		My_Ptr<SpriteAnimation>  hatchGoopyAni = hatchGoopy->AddComponent<SpriteAnimation>();
		//hatchGoopyAni->CreateAnimation(L"egg1", L"egg.png", 0, 0, 0.1f, false);
		hatchGoopyAni->CreateAnimation(L"basic", L"prego.png", 0, 9, 0.1f, true);
		hatchGoopy->GetTransform()->SetLocalPosition({ -1.0f, -24.0f + tempValue, __UI });
		hatchGoopy->GetTransform()->SetLocalScale({ 80.0f / GameWindow::Inst()->GetWindowSize().y , 80.0f / GameWindow::Inst()->GetWindowSize().y });
		hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);

		My_Ptr<FontRenderer> font = hatchGoopy->AddComponent< FontRenderer>(RG_BACKGROUND);
		font->SetFont(L"Silkscreen");
		font->SetText(L"PREGO", 18.0f, Vector4::WHITE);
		font->SetPos({ 0.0f, 40.0f, 0.0f, 0.0f });

		//hatchGoopy->GetTransform()->LocalScaleMultiple(0.3f);
		hatchGoopy->AddComponent<CreditMove>();
	}
	//
	{
		My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");
		My_Ptr<SpriteRenderer> hatchGoopyRenderer = hatchGoopy->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
		hatchGoopyRenderer->SetSprite(L"zorf.png");
		//hatchGoopyRenderer->SetBlender(L"BLEND1TO1");
		My_Ptr<SpriteAnimation>  hatchGoopyAni = hatchGoopy->AddComponent<SpriteAnimation>();
		//hatchGoopyAni->CreateAnimation(L"egg1", L"egg.png", 0, 0, 0.1f, false);
		hatchGoopyAni->CreateAnimation(L"basic", L"zorf.png", 0, 9, 0.1f, true);
		hatchGoopy->GetTransform()->SetLocalPosition({ 1.0f, -26.0f + tempValue, __UI });
		hatchGoopy->GetTransform()->SetLocalScale({ 80.0f / GameWindow::Inst()->GetWindowSize().y , 80.0f / GameWindow::Inst()->GetWindowSize().y });
		hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);

		My_Ptr<FontRenderer> font = hatchGoopy->AddComponent< FontRenderer>(RG_BACKGROUND);
		font->SetFont(L"Silkscreen");
		font->SetText(L"ZORF", 18.0f, Vector4::WHITE);
		font->SetPos({ 0.0f, 40.0f, 0.0f, 0.0f });

		//hatchGoopy->GetTransform()->LocalScaleMultiple(0.3f);
		hatchGoopy->AddComponent<CreditMove>();
	}

	{
		My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");
		My_Ptr<SpriteRenderer> hatchGoopyRenderer = hatchGoopy->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
		hatchGoopyRenderer->SetSprite(L"clyde.png");
		//hatchGoopyRenderer->SetBlender(L"BLEND1TO1");
		My_Ptr<SpriteAnimation>  hatchGoopyAni = hatchGoopy->AddComponent<SpriteAnimation>();
		//hatchGoopyAni->CreateAnimation(L"egg1", L"egg.png", 0, 0, 0.1f, false);
		hatchGoopyAni->CreateAnimation(L"basic", L"clyde.png", 0, 9, 0.1f, true);
		hatchGoopy->GetTransform()->SetLocalPosition({ -1.0f, -26.0f + tempValue, __UI });
		hatchGoopy->GetTransform()->SetLocalScale({ 80.0f / GameWindow::Inst()->GetWindowSize().y , 80.0f / GameWindow::Inst()->GetWindowSize().y });
		hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);

		My_Ptr<FontRenderer> font = hatchGoopy->AddComponent< FontRenderer>(RG_BACKGROUND);
		font->SetFont(L"Silkscreen");
		font->SetText(L"CLYDE", 18.0f, Vector4::WHITE);
		font->SetPos({ 0.0f, 40.0f, 0.0f, 0.0f });

		//hatchGoopy->GetTransform()->LocalScaleMultiple(0.3f);
		hatchGoopy->AddComponent<CreditMove>();
	}


	//
	{
		My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");
		My_Ptr<SpriteRenderer> hatchGoopyRenderer = hatchGoopy->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
		hatchGoopyRenderer->SetSprite(L"vert.png");
		//hatchGoopyRenderer->SetBlender(L"BLEND1TO1");
		My_Ptr<SpriteAnimation>  hatchGoopyAni = hatchGoopy->AddComponent<SpriteAnimation>();
		//hatchGoopyAni->CreateAnimation(L"egg1", L"egg.png", 0, 0, 0.1f, false);
		hatchGoopyAni->CreateAnimation(L"basic", L"vert.png", 0, 9, 0.1f, true);
		hatchGoopy->GetTransform()->SetLocalPosition({ 1.0f, -28.0f + tempValue, __UI });
		hatchGoopy->GetTransform()->SetLocalScale({ 80.0f / GameWindow::Inst()->GetWindowSize().y , 80.0f / GameWindow::Inst()->GetWindowSize().y });
		hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);

		My_Ptr<FontRenderer> font = hatchGoopy->AddComponent< FontRenderer>(RG_BACKGROUND);
		font->SetFont(L"Silkscreen");
		font->SetText(L"VERT", 18.0f, Vector4::WHITE);
		font->SetPos({ 0.0f, 40.0f, 0.0f, 0.0f });

		//hatchGoopy->GetTransform()->LocalScaleMultiple(0.3f);
		hatchGoopy->AddComponent<CreditMove>();
	}

	{
		My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");
		My_Ptr<SpriteRenderer> hatchGoopyRenderer = hatchGoopy->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
		hatchGoopyRenderer->SetSprite(L"rufus.png");
		//hatchGoopyRenderer->SetBlender(L"BLEND1TO1");
		My_Ptr<SpriteAnimation>  hatchGoopyAni = hatchGoopy->AddComponent<SpriteAnimation>();
		//hatchGoopyAni->CreateAnimation(L"egg1", L"egg.png", 0, 0, 0.1f, false);
		hatchGoopyAni->CreateAnimation(L"basic", L"rufus.png", 0, 9, 0.1f, true);
		hatchGoopy->GetTransform()->SetLocalPosition({ -1.0f, -28.0f + tempValue, __UI });
		hatchGoopy->GetTransform()->SetLocalScale({ 80.0f / GameWindow::Inst()->GetWindowSize().y , 80.0f / GameWindow::Inst()->GetWindowSize().y });
		hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);

		My_Ptr<FontRenderer> font = hatchGoopy->AddComponent< FontRenderer>(RG_BACKGROUND);
		font->SetFont(L"Silkscreen");
		font->SetText(L"RUFUS", 18.0f, Vector4::WHITE);
		font->SetPos({ 0.0f, 40.0f, 0.0f, 0.0f });

		//hatchGoopy->GetTransform()->LocalScaleMultiple(0.3f);
		hatchGoopy->AddComponent<CreditMove>();
	}

	//
	{
		My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");
		My_Ptr<SpriteRenderer> hatchGoopyRenderer = hatchGoopy->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
		hatchGoopyRenderer->SetSprite(L"meryl.png");
		//hatchGoopyRenderer->SetBlender(L"BLEND1TO1");
		My_Ptr<SpriteAnimation>  hatchGoopyAni = hatchGoopy->AddComponent<SpriteAnimation>();
		//hatchGoopyAni->CreateAnimation(L"egg1", L"egg.png", 0, 0, 0.1f, false);
		hatchGoopyAni->CreateAnimation(L"basic", L"meryl.png", 0, 9, 0.1f, true);
		hatchGoopy->GetTransform()->SetLocalPosition({ 1.0f, -30.0f + tempValue, __UI });
		hatchGoopy->GetTransform()->SetLocalScale({ 80.0f / GameWindow::Inst()->GetWindowSize().y , 80.0f / GameWindow::Inst()->GetWindowSize().y });
		hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);

		My_Ptr<FontRenderer> font = hatchGoopy->AddComponent< FontRenderer>(RG_BACKGROUND);
		font->SetFont(L"Silkscreen");
		font->SetText(L"MERYL", 18.0f, Vector4::WHITE);
		font->SetPos({ 0.0f, 40.0f, 0.0f, 0.0f });

		//hatchGoopy->GetTransform()->LocalScaleMultiple(0.3f);
		hatchGoopy->AddComponent<CreditMove>();
	}

	{
		My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");
		My_Ptr<SpriteRenderer> hatchGoopyRenderer = hatchGoopy->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
		hatchGoopyRenderer->SetSprite(L"wadsworth.png");
		//hatchGoopyRenderer->SetBlender(L"BLEND1TO1");
		My_Ptr<SpriteAnimation>  hatchGoopyAni = hatchGoopy->AddComponent<SpriteAnimation>();
		//hatchGoopyAni->CreateAnimation(L"egg1", L"egg.png", 0, 0, 0.1f, false);
		hatchGoopyAni->CreateAnimation(L"basic", L"wadsworth.png", 0, 9, 0.1f, true);
		hatchGoopy->GetTransform()->SetLocalPosition({ -1.0f, -30.0f + tempValue, __UI });
		hatchGoopy->GetTransform()->SetLocalScale({ 80.0f / GameWindow::Inst()->GetWindowSize().y , 80.0f / GameWindow::Inst()->GetWindowSize().y });
		hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);

		My_Ptr<FontRenderer> font = hatchGoopy->AddComponent< FontRenderer>(RG_BACKGROUND);
		font->SetFont(L"Silkscreen");
		font->SetText(L"WADSWORTH", 18.0f, Vector4::WHITE);
		font->SetPos({ 0.0f, 40.0f, 0.0f, 0.0f });

		//hatchGoopy->GetTransform()->LocalScaleMultiple(0.3f);
		hatchGoopy->AddComponent<CreditMove>();
	}

	{
		My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");
		My_Ptr<SpriteRenderer> hatchGoopyRenderer = hatchGoopy->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
		hatchGoopyRenderer->SetSprite(L"seymour.png");
		//hatchGoopyRenderer->SetBlender(L"BLEND1TO1");
		My_Ptr<SpriteAnimation>  hatchGoopyAni = hatchGoopy->AddComponent<SpriteAnimation>();
		//hatchGoopyAni->CreateAnimation(L"egg1", L"egg.png", 0, 0, 0.1f, false);
		hatchGoopyAni->CreateAnimation(L"basic", L"seymour.png", 0, 9, 0.1f, true);
		hatchGoopy->GetTransform()->SetLocalPosition({ 1.0f, -32.0f + tempValue, __UI });
		hatchGoopy->GetTransform()->SetLocalScale({ 80.0f / GameWindow::Inst()->GetWindowSize().y , 80.0f / GameWindow::Inst()->GetWindowSize().y });
		hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);

		My_Ptr<FontRenderer> font = hatchGoopy->AddComponent< FontRenderer>(RG_BACKGROUND);
		font->SetFont(L"Silkscreen");
		font->SetText(L"SEYMOUR", 18.0f, Vector4::WHITE);
		font->SetPos({ 0.0f, 40.0f, 0.0f, 0.0f });

		//hatchGoopy->GetTransform()->LocalScaleMultiple(0.3f);
		hatchGoopy->AddComponent<CreditMove>();
	}

	{
		My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");
		My_Ptr<SpriteRenderer> hatchGoopyRenderer = hatchGoopy->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
		hatchGoopyRenderer->SetSprite(L"shrapnel.png");
		//hatchGoopyRenderer->SetBlender(L"BLEND1TO1");
		My_Ptr<SpriteAnimation>  hatchGoopyAni = hatchGoopy->AddComponent<SpriteAnimation>();
		//hatchGoopyAni->CreateAnimation(L"egg1", L"egg.png", 0, 0, 0.1f, false);
		hatchGoopyAni->CreateAnimation(L"basic", L"shrapnel.png", 0, 9, 0.1f, true);
		hatchGoopy->GetTransform()->SetLocalPosition({ -1.0f, -32.0f + tempValue, __UI });
		hatchGoopy->GetTransform()->SetLocalScale({ 80.0f / GameWindow::Inst()->GetWindowSize().y , 80.0f / GameWindow::Inst()->GetWindowSize().y });
		hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);

		My_Ptr<FontRenderer> font = hatchGoopy->AddComponent< FontRenderer>(RG_BACKGROUND);
		font->SetFont(L"Silkscreen");
		font->SetText(L"SHRAPNEL", 18.0f, Vector4::WHITE);
		font->SetPos({ 0.0f, 40.0f, 0.0f, 0.0f });

		//hatchGoopy->GetTransform()->LocalScaleMultiple(0.3f);
		hatchGoopy->AddComponent<CreditMove>();
	}

	{
		My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");
		My_Ptr<SpriteRenderer> hatchGoopyRenderer = hatchGoopy->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
		hatchGoopyRenderer->SetSprite(L"gumbo.png");
		//hatchGoopyRenderer->SetBlender(L"BLEND1TO1");
		My_Ptr<SpriteAnimation>  hatchGoopyAni = hatchGoopy->AddComponent<SpriteAnimation>();
		//hatchGoopyAni->CreateAnimation(L"egg1", L"egg.png", 0, 0, 0.1f, false);
		hatchGoopyAni->CreateAnimation(L"basic", L"gumbo.png", 0, 9, 0.1f, true);
		hatchGoopy->GetTransform()->SetLocalPosition({ 1.0f, -34.0f + tempValue, __UI });
		hatchGoopy->GetTransform()->SetLocalScale({ 80.0f / GameWindow::Inst()->GetWindowSize().y , 80.0f / GameWindow::Inst()->GetWindowSize().y });
		hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);

		My_Ptr<FontRenderer> font = hatchGoopy->AddComponent< FontRenderer>(RG_BACKGROUND);
		font->SetFont(L"Silkscreen");
		font->SetText(L"GUMBO", 18.0f, Vector4::WHITE);
		font->SetPos({ 0.0f, 40.0f, 0.0f, 0.0f });

		//hatchGoopy->GetTransform()->LocalScaleMultiple(0.3f);
		hatchGoopy->AddComponent<CreditMove>();
	}

	{
		My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");
		My_Ptr<SpriteRenderer> hatchGoopyRenderer = hatchGoopy->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
		hatchGoopyRenderer->SetSprite(L"blip.png");
		//hatchGoopyRenderer->SetBlender(L"BLEND1TO1");
		My_Ptr<SpriteAnimation>  hatchGoopyAni = hatchGoopy->AddComponent<SpriteAnimation>();
		//hatchGoopyAni->CreateAnimation(L"egg1", L"egg.png", 0, 0, 0.1f, false);
		hatchGoopyAni->CreateAnimation(L"basic", L"blip.png", 0, 9, 0.1f, true);
		hatchGoopy->GetTransform()->SetLocalPosition({ -1.0f, -34.0f + tempValue, __UI });
		hatchGoopy->GetTransform()->SetLocalScale({ 80.0f / GameWindow::Inst()->GetWindowSize().y , 80.0f / GameWindow::Inst()->GetWindowSize().y });
		hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);

		My_Ptr<FontRenderer> font = hatchGoopy->AddComponent< FontRenderer>(RG_BACKGROUND);
		font->SetFont(L"Silkscreen");
		font->SetText(L"BLIP", 18.0f, Vector4::WHITE);
		font->SetPos({ 0.0f, 40.0f, 0.0f, 0.0f });

		//hatchGoopy->GetTransform()->LocalScaleMultiple(0.3f);
		hatchGoopy->AddComponent<CreditMove>();
	}

	{
		My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");
		My_Ptr<SpriteRenderer> hatchGoopyRenderer = hatchGoopy->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
		hatchGoopyRenderer->SetSprite(L"rhubarb.png");
		//hatchGoopyRenderer->SetBlender(L"BLEND1TO1");
		My_Ptr<SpriteAnimation>  hatchGoopyAni = hatchGoopy->AddComponent<SpriteAnimation>();
		//hatchGoopyAni->CreateAnimation(L"egg1", L"egg.png", 0, 0, 0.1f, false);
		hatchGoopyAni->CreateAnimation(L"basic", L"rhubarb.png", 0, 9, 0.1f, true);
		hatchGoopy->GetTransform()->SetLocalPosition({ 1.0f, -36.0f + tempValue, __UI });
		hatchGoopy->GetTransform()->SetLocalScale({ 80.0f / GameWindow::Inst()->GetWindowSize().y , 80.0f / GameWindow::Inst()->GetWindowSize().y });
		hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);

		My_Ptr<FontRenderer> font = hatchGoopy->AddComponent< FontRenderer>(RG_BACKGROUND);
		font->SetFont(L"Silkscreen");
		font->SetText(L"RHUBARB", 18.0f, Vector4::WHITE);
		font->SetPos({ 0.0f, 40.0f, 0.0f, 0.0f });

		//hatchGoopy->GetTransform()->LocalScaleMultiple(0.3f);
		hatchGoopy->AddComponent<CreditMove>();
	}

	{
		My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");
		My_Ptr<SpriteRenderer> hatchGoopyRenderer = hatchGoopy->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
		hatchGoopyRenderer->SetSprite(L"nimbus.png");
		//hatchGoopyRenderer->SetBlender(L"BLEND1TO1");
		My_Ptr<SpriteAnimation>  hatchGoopyAni = hatchGoopy->AddComponent<SpriteAnimation>();
		//hatchGoopyAni->CreateAnimation(L"egg1", L"egg.png", 0, 0, 0.1f, false);
		hatchGoopyAni->CreateAnimation(L"basic", L"nimbus.png", 0, 9, 0.1f, true);
		hatchGoopy->GetTransform()->SetLocalPosition({ -1.0f, -36.0f + tempValue, __UI });
		hatchGoopy->GetTransform()->SetLocalScale({ 80.0f / GameWindow::Inst()->GetWindowSize().y , 80.0f / GameWindow::Inst()->GetWindowSize().y });
		hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);

		My_Ptr<FontRenderer> font = hatchGoopy->AddComponent< FontRenderer>(RG_BACKGROUND);
		font->SetFont(L"Silkscreen");
		font->SetText(L"NIMBUS", 18.0f, Vector4::WHITE);
		font->SetPos({ 0.0f, 40.0f, 0.0f, 0.0f });

		//hatchGoopy->GetTransform()->LocalScaleMultiple(0.3f);
		hatchGoopy->AddComponent<CreditMove>();
	}


	{
		My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");
		My_Ptr<SpriteRenderer> hatchGoopyRenderer = hatchGoopy->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
		hatchGoopyRenderer->SetSprite(L"amp.png");
		//hatchGoopyRenderer->SetBlender(L"BLEND1TO1");
		My_Ptr<SpriteAnimation>  hatchGoopyAni = hatchGoopy->AddComponent<SpriteAnimation>();
		//hatchGoopyAni->CreateAnimation(L"egg1", L"egg.png", 0, 0, 0.1f, false);
		hatchGoopyAni->CreateAnimation(L"basic", L"amp.png", 0, 9, 0.1f, true);
		hatchGoopy->GetTransform()->SetLocalPosition({ 1.0f, -38.0f + tempValue, __UI });
		hatchGoopy->GetTransform()->SetLocalScale({ 160.0f / GameWindow::Inst()->GetWindowSize().y , 120.0f / GameWindow::Inst()->GetWindowSize().y });
		hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);

		My_Ptr<FontRenderer> font = hatchGoopy->AddComponent< FontRenderer>(RG_BACKGROUND);
		font->SetFont(L"Silkscreen");
		font->SetText(L"AMP", 18.0f, Vector4::WHITE);
		font->SetPos({ 0.0f, 40.0f, 0.0f, 0.0f });

		//hatchGoopy->GetTransform()->LocalScaleMultiple(0.3f);
		hatchGoopy->AddComponent<CreditMove>();
	}

	{
		My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");
		My_Ptr<SpriteRenderer> hatchGoopyRenderer = hatchGoopy->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
		hatchGoopyRenderer->SetSprite(L"gash.png");
		//hatchGoopyRenderer->SetBlender(L"BLEND1TO1");
		My_Ptr<SpriteAnimation>  hatchGoopyAni = hatchGoopy->AddComponent<SpriteAnimation>();
		//hatchGoopyAni->CreateAnimation(L"egg1", L"egg.png", 0, 0, 0.1f, false);
		hatchGoopyAni->CreateAnimation(L"basic", L"gash.png", 0, 9, 0.1f, true);
		hatchGoopy->GetTransform()->SetLocalPosition({ -1.0f, -38.0f + tempValue, __UI });
		hatchGoopy->GetTransform()->SetLocalScale({ 80.0f / GameWindow::Inst()->GetWindowSize().y , 80.0f / GameWindow::Inst()->GetWindowSize().y });
		hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);

		My_Ptr<FontRenderer> font = hatchGoopy->AddComponent< FontRenderer>(RG_BACKGROUND);
		font->SetFont(L"Silkscreen");
		font->SetText(L"GASH", 18.0f, Vector4::WHITE);
		font->SetPos({ 0.0f, 40.0f, 0.0f, 0.0f });

		//hatchGoopy->GetTransform()->LocalScaleMultiple(0.3f);
		hatchGoopy->AddComponent<CreditMove>();
	}


	{
		My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");
		My_Ptr<SpriteRenderer> hatchGoopyRenderer = hatchGoopy->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
		hatchGoopyRenderer->SetSprite(L"angie.png");
		//hatchGoopyRenderer->SetBlender(L"BLEND1TO1");
		My_Ptr<SpriteAnimation>  hatchGoopyAni = hatchGoopy->AddComponent<SpriteAnimation>();
		//hatchGoopyAni->CreateAnimation(L"egg1", L"egg.png", 0, 0, 0.1f, false);
		hatchGoopyAni->CreateAnimation(L"basic", L"angie.png", 0, 9, 0.1f, true);
		hatchGoopy->GetTransform()->SetLocalPosition({ 1.0f, -40.0f + tempValue, __UI });
		hatchGoopy->GetTransform()->SetLocalScale({ 80.0f / GameWindow::Inst()->GetWindowSize().y , 80.0f / GameWindow::Inst()->GetWindowSize().y });
		hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);

		My_Ptr<FontRenderer> font = hatchGoopy->AddComponent< FontRenderer>(RG_BACKGROUND);
		font->SetFont(L"Silkscreen");
		font->SetText(L"ANGIE", 18.0f, Vector4::WHITE);
		font->SetPos({ 0.0f, 40.0f, 0.0f, 0.0f });

		//hatchGoopy->GetTransform()->LocalScaleMultiple(0.3f);
		hatchGoopy->AddComponent<CreditMove>();
	}

	{
		My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");
		My_Ptr<SpriteRenderer> hatchGoopyRenderer = hatchGoopy->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
		hatchGoopyRenderer->SetSprite(L"presto.png");
		//hatchGoopyRenderer->SetBlender(L"BLEND1TO1");
		My_Ptr<SpriteAnimation>  hatchGoopyAni = hatchGoopy->AddComponent<SpriteAnimation>();
		//hatchGoopyAni->CreateAnimation(L"egg1", L"egg.png", 0, 0, 0.1f, false);
		hatchGoopyAni->CreateAnimation(L"basic", L"presto.png", 0, 9, 0.1f, true);
		hatchGoopy->GetTransform()->SetLocalPosition({ -1.0f, -40.0f + tempValue, __UI });
		hatchGoopy->GetTransform()->SetLocalScale({ 80.0f / GameWindow::Inst()->GetWindowSize().y , 80.0f / GameWindow::Inst()->GetWindowSize().y });
		hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);

		My_Ptr<FontRenderer> font = hatchGoopy->AddComponent< FontRenderer>(RG_BACKGROUND);
		font->SetFont(L"Silkscreen");
		font->SetText(L"PRESTO", 18.0f, Vector4::WHITE);
		font->SetPos({ 0.0f, 40.0f, 0.0f, 0.0f });

		//hatchGoopy->GetTransform()->LocalScaleMultiple(0.3f);
		hatchGoopy->AddComponent<CreditMove>();
	}


	{
		My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");
		My_Ptr<SpriteRenderer> hatchGoopyRenderer = hatchGoopy->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
		hatchGoopyRenderer->SetSprite(L"brink.png");
		//hatchGoopyRenderer->SetBlender(L"BLEND1TO1");
		My_Ptr<SpriteAnimation>  hatchGoopyAni = hatchGoopy->AddComponent<SpriteAnimation>();
		//hatchGoopyAni->CreateAnimation(L"egg1", L"egg.png", 0, 0, 0.1f, false);
		hatchGoopyAni->CreateAnimation(L"basic", L"brink.png", 0, 9, 0.1f, true);
		hatchGoopy->GetTransform()->SetLocalPosition({ 1.0f, -42.0f + tempValue, __UI });
		hatchGoopy->GetTransform()->SetLocalScale({ 80.0f / GameWindow::Inst()->GetWindowSize().y , 80.0f / GameWindow::Inst()->GetWindowSize().y });
		hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);

		My_Ptr<FontRenderer> font = hatchGoopy->AddComponent< FontRenderer>(RG_BACKGROUND);
		font->SetFont(L"Silkscreen");
		font->SetText(L"BRINKLEY", 18.0f, Vector4::WHITE);
		font->SetPos({ 0.0f, 40.0f, 0.0f, 0.0f });

		//hatchGoopy->GetTransform()->LocalScaleMultiple(0.3f);
		hatchGoopy->AddComponent<CreditMove>();
	}

	{
		My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");
		My_Ptr<SpriteRenderer> hatchGoopyRenderer = hatchGoopy->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
		hatchGoopyRenderer->SetSprite(L"nostradamus.png");
		//hatchGoopyRenderer->SetBlender(L"BLEND1TO1");
		My_Ptr<SpriteAnimation>  hatchGoopyAni = hatchGoopy->AddComponent<SpriteAnimation>();
		//hatchGoopyAni->CreateAnimation(L"egg1", L"egg.png", 0, 0, 0.1f, false);
		hatchGoopyAni->CreateAnimation(L"basic", L"nostradamus.png", 0, 9, 0.1f, true);
		hatchGoopy->GetTransform()->SetLocalPosition({ -1.0f, -42.0f + tempValue, __UI });
		hatchGoopy->GetTransform()->SetLocalScale({ 80.0f / GameWindow::Inst()->GetWindowSize().y , 80.0f / GameWindow::Inst()->GetWindowSize().y });
		hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);

		My_Ptr<FontRenderer> font = hatchGoopy->AddComponent< FontRenderer>(RG_BACKGROUND);
		font->SetFont(L"Silkscreen");
		font->SetText(L"NOSTRADAMUS", 18.0f, Vector4::WHITE);
		font->SetPos({ 0.0f, 40.0f, 0.0f, 0.0f });

		//hatchGoopy->GetTransform()->LocalScaleMultiple(0.3f);
		hatchGoopy->AddComponent<CreditMove>();
	}


	{
		My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");
		My_Ptr<SpriteRenderer> hatchGoopyRenderer = hatchGoopy->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
		hatchGoopyRenderer->SetSprite(L"stanley.png");
		//hatchGoopyRenderer->SetBlender(L"BLEND1TO1");
		My_Ptr<SpriteAnimation>  hatchGoopyAni = hatchGoopy->AddComponent<SpriteAnimation>();
		//hatchGoopyAni->CreateAnimation(L"egg1", L"egg.png", 0, 0, 0.1f, false);
		hatchGoopyAni->CreateAnimation(L"basic", L"stanley.png", 0, 9, 0.1f, true);
		hatchGoopy->GetTransform()->SetLocalPosition({ 1.0f, -44.0f + tempValue, __UI });
		hatchGoopy->GetTransform()->SetLocalScale({ 80.0f / GameWindow::Inst()->GetWindowSize().y , 80.0f / GameWindow::Inst()->GetWindowSize().y });
		hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);

		My_Ptr<FontRenderer> font = hatchGoopy->AddComponent< FontRenderer>(RG_BACKGROUND);
		font->SetFont(L"Silkscreen");
		font->SetText(L"STANLEY", 18.0f, Vector4::WHITE);
		font->SetPos({ 0.0f, 40.0f, 0.0f, 0.0f });

		//hatchGoopy->GetTransform()->LocalScaleMultiple(0.3f);
		hatchGoopy->AddComponent<CreditMove>();
	}

	{
		My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");
		My_Ptr<SpriteRenderer> hatchGoopyRenderer = hatchGoopy->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
		hatchGoopyRenderer->SetSprite(L"walter.png");
		//hatchGoopyRenderer->SetBlender(L"BLEND1TO1");
		My_Ptr<SpriteAnimation>  hatchGoopyAni = hatchGoopy->AddComponent<SpriteAnimation>();
		//hatchGoopyAni->CreateAnimation(L"egg1", L"egg.png", 0, 0, 0.1f, false);
		hatchGoopyAni->CreateAnimation(L"basic", L"walter.png", 0, 9, 0.1f, true);
		hatchGoopy->GetTransform()->SetLocalPosition({ -1.0f, -44.0f + tempValue, __UI });
		hatchGoopy->GetTransform()->SetLocalScale({ 80.0f / GameWindow::Inst()->GetWindowSize().y , 80.0f / GameWindow::Inst()->GetWindowSize().y });
		hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);

		My_Ptr<FontRenderer> font = hatchGoopy->AddComponent< FontRenderer>(RG_BACKGROUND);
		font->SetFont(L"Silkscreen");
		font->SetText(L"WALTER", 18.0f, Vector4::WHITE);
		font->SetPos({ 0.0f, 40.0f, 0.0f, 0.0f });

		//hatchGoopy->GetTransform()->LocalScaleMultiple(0.3f);
		hatchGoopy->AddComponent<CreditMove>();
	}


	{
		My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");

		My_Ptr<FontRenderer> font = hatchGoopy->AddComponent< FontRenderer>(RG_BACKGROUND);
		font->SetFont(L"Silkscreen");
		std::wstring text;
		text += L"THANK YOU ALL FOR WATCHING";
			//Thank you all for watching";


		font->SetText(text, 28.0f, Vector4::WHITE);


		hatchGoopy->GetTransform()->SetLocalPosition({ 0.0f, -46.0f + tempValue, __UI });
		hatchGoopy->GetTransform()->SetLocalScale({ 80.0f / GameWindow::Inst()->GetWindowSize().y , 80.0f / GameWindow::Inst()->GetWindowSize().y });
		hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);
		hatchGoopy->GetTransform()->LocalScaleMultiple(0.3f);
		hatchGoopy->AddComponent<CreditMove>();
	}

}

void EndingUpdater::SceneUpdate()
{
	//GraphicDebug::DrawFontUI(L"CONGRATULATIONS! 1000", Vector4::WHITE);



#pragma region BUBBLE
	bubbleTime1 -= Time::DeltaTime();
	bubbleTime2 -= Time::DeltaTime();
	bubbleTime3 -= Time::DeltaTime();

	if (bubbleTime1 < 0.0f)
	{
		Sound::Play(L"bubbles.wav");
		for (int i = 0; i < 10; ++i)
		{
			My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");
			My_Ptr<SpriteRenderer> hatchGoopyRenderer = hatchGoopy->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
			hatchGoopyRenderer->SetSprite(L"bubbles.png");
			hatchGoopyRenderer->SetBlender(L"BLEND1TO1");

	/*		My_Ptr<FontRenderer> font = hatchGoopy->AddComponent< FontRenderer>(RG_UI);
			font->SetFont(L"Silkscreen");*/


			My_Ptr<SpriteAnimation>  hatchGoopyAni = hatchGoopy->AddComponent<SpriteAnimation>();
			//hatchGoopyAni->CreateAnimation(L"egg1", L"egg.png", 0, 0, 0.1f, false);
			hatchGoopyAni->CreateAnimation(L"bubbles", L"bubbles.png", 0, 4, 0.4f, false);
			hatchGoopy->GetTransform()->SetLocalPosition({ Well512Random::Instance().GetFloatValue(-2.7f, -2.0f), Well512Random::Instance().GetFloatValue(-2.8f, -10.0f), __UI });
			hatchGoopy->GetTransform()->SetLocalScale({ 80.0f / GameWindow::Inst()->GetWindowSize().y , 80.0f / GameWindow::Inst()->GetWindowSize().y });
			hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);
			hatchGoopy->GetTransform()->LocalScaleMultiple(0.3f);
			hatchGoopy->AddComponent<BubbleMove>();
		}
		bubbleTime1 = Well512Random::Instance().GetFloatValue(5.0f, 15.0f);
	}
	if (bubbleTime2 < 0.0f)
	{
		Sound::Play(L"bubbles.wav");
		for (int i = 0; i < 10; ++i)
		{
			My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");
			My_Ptr<SpriteRenderer> hatchGoopyRenderer = hatchGoopy->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
			hatchGoopyRenderer->SetSprite(L"bubbles.png");
			hatchGoopyRenderer->SetBlender(L"BLEND1TO1");
			My_Ptr<SpriteAnimation>  hatchGoopyAni = hatchGoopy->AddComponent<SpriteAnimation>();
			//hatchGoopyAni->CreateAnimation(L"egg1", L"egg.png", 0, 0, 0.1f, false);
			hatchGoopyAni->CreateAnimation(L"bubbles", L"bubbles.png", 0, 4, 0.4f, false);
			hatchGoopy->GetTransform()->SetLocalPosition({ Well512Random::Instance().GetFloatValue(2.7f, 2.0f), Well512Random::Instance().GetFloatValue(-2.8f, -10.0f), __UI });
			hatchGoopy->GetTransform()->SetLocalScale({ 80.0f / GameWindow::Inst()->GetWindowSize().y , 80.0f / GameWindow::Inst()->GetWindowSize().y });
			hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);
			hatchGoopy->GetTransform()->LocalScaleMultiple(0.3f);
			hatchGoopy->AddComponent<BubbleMove>();
		}
		bubbleTime2 = Well512Random::Instance().GetFloatValue(5.0f, 15.0f);
	}
	if (bubbleTime3 < 0.0f)
	{
		Sound::Play(L"bubbles.wav");
		for (int i = 0; i < 10; ++i)
		{
			My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");
			My_Ptr<SpriteRenderer> hatchGoopyRenderer = hatchGoopy->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
			hatchGoopyRenderer->SetSprite(L"bubbles.png");
			hatchGoopyRenderer->SetBlender(L"BLEND1TO1");
			My_Ptr<SpriteAnimation>  hatchGoopyAni = hatchGoopy->AddComponent<SpriteAnimation>();
			//hatchGoopyAni->CreateAnimation(L"egg1", L"egg.png", 0, 0, 0.1f, false);
			hatchGoopyAni->CreateAnimation(L"bubbles", L"bubbles.png", 0, 4, 0.4f, false);
			hatchGoopy->GetTransform()->SetLocalPosition({ Well512Random::Instance().GetFloatValue(1.0f, -1.0f), Well512Random::Instance().GetFloatValue(-2.8f, -10.0f), __UI });
			hatchGoopy->GetTransform()->SetLocalScale({ 80.0f / GameWindow::Inst()->GetWindowSize().y , 80.0f / GameWindow::Inst()->GetWindowSize().y });
			hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);
			hatchGoopy->GetTransform()->LocalScaleMultiple(0.3f);
			hatchGoopy->AddComponent<BubbleMove>();
		}
		bubbleTime3 = Well512Random::Instance().GetFloatValue(5.0f, 15.0f);
	}
#pragma endregion
}