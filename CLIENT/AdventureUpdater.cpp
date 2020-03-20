#define _CRT_SECURE_NO_WARNINGS
#include "AdventureUpdater.h"


//STANDARD
#include <stdlib.h>
#include <string.h>
#include <stdio.h>     

//ENGINE
#include <GameWindow.h>
#include <GraphicDebug.h>
#include <Camera.h>
#include <SpriteRenderer.h>
#include <Texture.h>
#include <Sprite.h>
#include <SpriteAnimation.h>
#include <RectRenderer.h>

//LOGIC
#include <FishMove.h>
#include <FoodMove.h>
#include <GoopyList.h>

//CLIENT
#include <ENUM.h>
#include "Mouse.h"
#include "BackGround.h"



#include "Goopy.h"	
#include "Food.h"
#include <FoodMove.h>
#include <BubbleMove.h>
#include <CoinBox.h>
#include <MonsterList.h>
#include <PetFishMove.h>

#include <PregoMove.h>
//#include "Zorf.h"
#include <ZorfMove.h>

#include <MonsterMove.h>
#include <FontRenderer.h>

#include <PetList.h>
#include <DentacleMove.h>
#include <ShellPetMove.h>

#include <BossMove.h>
#include <GusMove.h>
#include <Sound.h>

std::list<Hatch*> AdventureUpdater::hatchList;
int	 AdventureUpdater::monsterHp = 100;

//SpriteRenderer* AdventureUpdater::hpRender;

AdventureUpdater::AdventureUpdater() : bubbleTime1(5.0f), rebubbleTime(0.7f), bubbleTime2(7.0f), bubbleTime3(9.0f)
, createMonsterTime(CREATETIME), kindsOfMonster(MONSTER::BALROG)
{
}


AdventureUpdater::~AdventureUpdater()
{
}


void AdventureUpdater::Loading()
{

	GetScene()->colliderMgr.Link(COLGROUP::CG_LITTLEGOOPY, COLGROUP::CG_FOOD);
	GetScene()->colliderMgr.Link(COLGROUP::CG_LITTLEGOOPY, COLGROUP::CG_WADSWORTH);
	GetScene()->colliderMgr.Link(COLGROUP::CG_MIDDLEGOOPY, COLGROUP::CG_WADSWORTH);


	GetScene()->colliderMgr.Link(COLGROUP::CG_LITTLEGOOPY,	COLGROUP::CG_COIN);
	GetScene()->colliderMgr.Link(COLGROUP::CG_MIDDLEGOOPY,	COLGROUP::CG_COIN);
	GetScene()->colliderMgr.Link(COLGROUP::CG_BIGGOOPY,		COLGROUP::CG_COIN);
	GetScene()->colliderMgr.Link(COLGROUP::CG_CROWNGOOPY,	COLGROUP::CG_COIN);
	GetScene()->colliderMgr.Link(COLGROUP::CG_PIRANA,		COLGROUP::CG_COIN);
	GetScene()->colliderMgr.Link(COLGROUP::CG_ULTRAGOOPY,	COLGROUP::CG_COIN);

	GetScene()->colliderMgr.Link(COLGROUP::CG_LITTLEGOOPY,	COLGROUP::CG_RHUBARB);
	GetScene()->colliderMgr.Link(COLGROUP::CG_MIDDLEGOOPY,	COLGROUP::CG_RHUBARB);
	GetScene()->colliderMgr.Link(COLGROUP::CG_BIGGOOPY,		COLGROUP::CG_RHUBARB);
	GetScene()->colliderMgr.Link(COLGROUP::CG_CROWNGOOPY,	COLGROUP::CG_RHUBARB);
	GetScene()->colliderMgr.Link(COLGROUP::CG_PIRANA,		COLGROUP::CG_RHUBARB);
	GetScene()->colliderMgr.Link(COLGROUP::CG_ULTRAGOOPY,	COLGROUP::CG_RHUBARB);

	GetScene()->colliderMgr.Link(COLGROUP::CG_LITTLEGOOPY,	COLGROUP::CG_ANGIE);
	GetScene()->colliderMgr.Link(COLGROUP::CG_MIDDLEGOOPY,	COLGROUP::CG_ANGIE);
	GetScene()->colliderMgr.Link(COLGROUP::CG_BIGGOOPY,		COLGROUP::CG_ANGIE);
	GetScene()->colliderMgr.Link(COLGROUP::CG_CROWNGOOPY,	COLGROUP::CG_ANGIE);
	GetScene()->colliderMgr.Link(COLGROUP::CG_PIRANA,		COLGROUP::CG_ANGIE);
	GetScene()->colliderMgr.Link(COLGROUP::CG_ULTRAGOOPY,	COLGROUP::CG_ANGIE);

	GetScene()->colliderMgr.Link(COLGROUP::CG_LITTLEGOOPY,	COLGROUP::CG_PUNCH);
	GetScene()->colliderMgr.Link(COLGROUP::CG_MIDDLEGOOPY,	COLGROUP::CG_PUNCH);
	GetScene()->colliderMgr.Link(COLGROUP::CG_BIGGOOPY,		COLGROUP::CG_PUNCH);
	GetScene()->colliderMgr.Link(COLGROUP::CG_CROWNGOOPY,	COLGROUP::CG_PUNCH);
	GetScene()->colliderMgr.Link(COLGROUP::CG_PIRANA,		COLGROUP::CG_PUNCH);
	GetScene()->colliderMgr.Link(COLGROUP::CG_ULTRAGOOPY,	COLGROUP::CG_PUNCH);

	GetScene()->colliderMgr.Link(COLGROUP::CG_RHUBARB, COLGROUP::CG_LITTLEGOOPY );
	GetScene()->colliderMgr.Link(COLGROUP::CG_RHUBARB, COLGROUP::CG_MIDDLEGOOPY );
	GetScene()->colliderMgr.Link(COLGROUP::CG_RHUBARB, COLGROUP::CG_BIGGOOPY );
	GetScene()->colliderMgr.Link(COLGROUP::CG_RHUBARB, COLGROUP::CG_CROWNGOOPY );
	GetScene()->colliderMgr.Link(COLGROUP::CG_RHUBARB, COLGROUP::CG_PIRANA );
	GetScene()->colliderMgr.Link(COLGROUP::CG_RHUBARB, COLGROUP::CG_ULTRAGOOPY);



	//GetScene()->colliderMgr.Link(COLGROUP::CG_NIMBUS,	COLGROUP::CG_COIN);
	//GetScene()->colliderMgr.Link(COLGROUP::CG_NIMBUS,	COLGROUP::CG_FOOD);
	GetScene()->colliderMgr.Link(COLGROUP::CG_COIN,		COLGROUP::CG_NIMBUS);
	GetScene()->colliderMgr.Link(COLGROUP::CG_FOOD,		COLGROUP::CG_NIMBUS );

	GetScene()->colliderMgr.Link(COLGROUP::CG_PIRANA, COLGROUP::CG_LITTLEGOOPY);
	GetScene()->colliderMgr.Link(COLGROUP::CG_ULTRAGOOPY, COLGROUP::CG_PIRANA);

	GetScene()->colliderMgr.Link(COLGROUP::CG_MONSTER, COLGROUP::CG_LITTLEGOOPY);
	GetScene()->colliderMgr.Link(COLGROUP::CG_MONSTER, COLGROUP::CG_MIDDLEGOOPY);
	GetScene()->colliderMgr.Link(COLGROUP::CG_MONSTER, COLGROUP::CG_BIGGOOPY);
	GetScene()->colliderMgr.Link(COLGROUP::CG_MONSTER, COLGROUP::CG_CROWNGOOPY);
	GetScene()->colliderMgr.Link(COLGROUP::CG_MONSTER, COLGROUP::CG_PIRANA);
	GetScene()->colliderMgr.Link(COLGROUP::CG_MONSTER, COLGROUP::CG_ULTRAGOOPY);
	GetScene()->colliderMgr.Link(COLGROUP::CG_MONSTER, COLGROUP::CG_MOUSE);

	GetScene()->colliderMgr.Link(COLGROUP::CG_DENTACLE, COLGROUP::CG_LITTLEGOOPY);
	GetScene()->colliderMgr.Link(COLGROUP::CG_DENTACLE, COLGROUP::CG_MIDDLEGOOPY);
	GetScene()->colliderMgr.Link(COLGROUP::CG_DENTACLE, COLGROUP::CG_BIGGOOPY);
	GetScene()->colliderMgr.Link(COLGROUP::CG_DENTACLE, COLGROUP::CG_CROWNGOOPY);
	GetScene()->colliderMgr.Link(COLGROUP::CG_DENTACLE, COLGROUP::CG_PIRANA);
	GetScene()->colliderMgr.Link(COLGROUP::CG_DENTACLE, COLGROUP::CG_ULTRAGOOPY);
	GetScene()->colliderMgr.Link(COLGROUP::CG_DENTACLE, COLGROUP::CG_MOUSE);

	GetScene()->colliderMgr.Link(COLGROUP::CG_BOSS, COLGROUP::CG_LITTLEGOOPY);
	GetScene()->colliderMgr.Link(COLGROUP::CG_BOSS, COLGROUP::CG_MIDDLEGOOPY);
	GetScene()->colliderMgr.Link(COLGROUP::CG_BOSS, COLGROUP::CG_BIGGOOPY);
	GetScene()->colliderMgr.Link(COLGROUP::CG_BOSS, COLGROUP::CG_CROWNGOOPY);
	GetScene()->colliderMgr.Link(COLGROUP::CG_BOSS, COLGROUP::CG_PIRANA);
	GetScene()->colliderMgr.Link(COLGROUP::CG_BOSS, COLGROUP::CG_ULTRAGOOPY);
	GetScene()->colliderMgr.Link(COLGROUP::CG_BOSS, COLGROUP::CG_MOUSE);



	GetScene()->colliderMgr.Link(COLGROUP::CG_DENTACLE, COLGROUP::CG_MOUSE);
	GetScene()->colliderMgr.Link(COLGROUP::CG_BOSS, COLGROUP::CG_MOUSE);
	GetScene()->colliderMgr.Link(COLGROUP::CG_GUS, COLGROUP::CG_FOOD);
	GetScene()->colliderMgr.Link(COLGROUP::CG_GUS, COLGROUP::CG_LITTLEGOOPY);
	GetScene()->colliderMgr.Link(COLGROUP::CG_GUS, COLGROUP::CG_MIDDLEGOOPY);
	GetScene()->colliderMgr.Link(COLGROUP::CG_GUS, COLGROUP::CG_BIGGOOPY);
	GetScene()->colliderMgr.Link(COLGROUP::CG_GUS, COLGROUP::CG_CROWNGOOPY);
	GetScene()->colliderMgr.Link(COLGROUP::CG_GUS, COLGROUP::CG_PIRANA);
	GetScene()->colliderMgr.Link(COLGROUP::CG_GUS, COLGROUP::CG_ULTRAGOOPY);



	GetScene()->colliderMgr.Link(COLGROUP::CG_COINBOX, COLGROUP::CG_COIN);

	GetScene()->colliderMgr.Link(COLGROUP::CG_COIN, COLGROUP::CG_MOUSE);
	GetScene()->colliderMgr.Link(COLGROUP::CG_COIN, COLGROUP::CG_COINBOX);
	GetScene()->colliderMgr.Link(COLGROUP::CG_COIN, COLGROUP::CG_STINKY);
	GetScene()->colliderMgr.Link(COLGROUP::CG_COIN, COLGROUP::CG_CLYDE);
		
	GetScene()->colliderMgr.Link(COLGROUP::CG_MOUSE, COLGROUP::CG_MONSTER);
	GetScene()->colliderMgr.Link(COLGROUP::CG_MOUSE, COLGROUP::CG_DENTACLE);
	GetScene()->colliderMgr.Link(COLGROUP::CG_MOUSE, COLGROUP::CG_BOSS);

	GetScene()->colliderMgr.Link(COLGROUP::CG_MONSTER, COLGROUP::CG_BALL);
	GetScene()->colliderMgr.Link(COLGROUP::CG_DENTACLE, COLGROUP::CG_BALL);
	GetScene()->colliderMgr.Link(COLGROUP::CG_GUS, COLGROUP::CG_BALL);
	GetScene()->colliderMgr.Link(COLGROUP::CG_BOSS, COLGROUP::CG_BALL);

	GetScene()->colliderMgr.Link(COLGROUP::CG_AMP,	 COLGROUP::CG_MOUSE);
	GetScene()->colliderMgr.Link(COLGROUP::CG_WALTER, COLGROUP::CG_MOUSE);
	


#pragma region CAMERA
	My_Ptr<Actor> mainCam = GetScene()->CreateActor(L"PLAYERCAMERA");
	mainCam->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, -100.0f });
	My_Ptr<Camera> playerCamera = mainCam->AddComponent<Camera>(RENDERGROUP::RG_BACKGROUND, RENDERGROUP::RG_FOOD, RENDERGROUP::RG_PLAYER,
																RENDERGROUP::RG_PET, RENDERGROUP::RG_MONSTER, RENDERGROUP::RG_UI, RENDERGROUP::RG_COIN);
	playerCamera->SetProjMode(PROJMODE::ORTHOGONAL);
	playerCamera->SetArea(GameWindow::Inst()->GetWindowSize().x / 100.0f, GameWindow::Inst()->GetWindowSize().y / 100.0f);

	std::wstring backGroundName = L"aquarium1.jpg";
	BackGround backGround = BackGround(GetScene(), L"aquarium1.jpg", { 1,1,0,0 });
#pragma endregion
	   	 	
		
	for (int i = 0; i < 2; i++)
	{
		Goopy goopy = Goopy(GetScene(), L"Goopy.png", { 10, 35, 0, 349 });
		if (goopy.GetLogic()->GetPoint() < 20)
		{
			BoundingSphere* collider = goopy.GetCollider();			
			GoopyList::PushGoopy(goopy.GetActor());
		}
	}

	
	Input::CreateKey(L"F1", VK_F1);
	Input::CreateKey(L"F7", VK_F7);


#pragma region UI
	BackGround menuBar = BackGround(GetScene(), L"menubar.gif", { 1,1,0,0 });
	menuBar.GetActor()->GetTransform()->SetLocalPosition({ 0.0f, 2.05f, -1.0f });


#pragma region 이거 나중에 하나로 합쳐야한다

	{
		HatchButtonLine = new Hatch(GetScene(), L"hatchanimation2.png", { 6,1,0,5 }, COLGROUP::CG_UI_FISH);
		HatchButtonLine->GetActor()->GetTransform()->SetLocalPosition({ -2.73f, 2.06f, -3.0f });
		hatchList.push_back(HatchButtonLine);
	}
	
	//My_Ptr<BoundingSphere> hatchBubbleSphere = hatchBubble->AddComponent<BoundingSphere>(COLGROUP::CG_UI_FISH);

	
	/////////////////////////////먹이 종류
	{
		foodUIHatch = new Hatch(GetScene(), L"hatchanimation2.png", { 6,1,0,5 }, COLGROUP::CG_UI_FOOD);

		foodUIHatch->GetActor()->GetTransform()->SetLocalPosition({ -2.04f, 2.06f, -3.0f });
		hatchList.push_back(foodUIHatch);

		
		//My_Ptr<BoundingSphere> hatchBubbleSphere = hatchBubble->AddComponent<BoundingSphere>(COLGROUP::CG_UI_FOOD);
	}

	/////////////////////////////먹이 갯수
	{
		uiFoodAmount = new Hatch(GetScene(), L"hatchanimation2.png", { 6,1,0,5 }, COLGROUP::CG_UI_FOODCNT);

		uiFoodAmount->GetActor()->GetTransform()->SetLocalPosition({ -1.47f, 2.06f, -3.0f });
		hatchList.push_back(uiFoodAmount);

		
	}

	//////피라냐
	{
		float uiXPos = -0.74f;
		uiPirana = new Hatch(GetScene(), L"hatchanimation2.png", { 6,1,0,5 }, COLGROUP::CG_UI_PIRANA);

		uiPirana->GetActor()->GetTransform()->SetLocalPosition({ uiXPos, 2.06f, -3.0f });
		hatchList.push_back(uiPirana);

		
	}

	//////울트라피쉬
	{
		float uiXPos = -0.005f;
		uiBIGFish = new Hatch(GetScene(), L"hatchanimation2.png", { 6,1,0,5 }, COLGROUP::CG_UI_KINGFISH);

		uiBIGFish->GetActor()->GetTransform()->SetLocalPosition({ uiXPos, 2.06f, -3.0f });
		hatchList.push_back(uiBIGFish);

		
	}

	//////총
	{
		float uiXPos = 0.71f;
		uiGun = new Hatch(GetScene(), L"hatchanimation2.png", { 6,1,0,5 }, COLGROUP::CG_UI_GUN);

		uiGun->GetActor()->GetTransform()->SetLocalPosition({ uiXPos, 2.06f, -3.0f });
		hatchList.push_back(uiGun);
		
		
	}

	//////펫 에그
	{
		float uiXPos = 1.45f;
		uiPetEgg = new Hatch(GetScene(), L"hatchanimation2.png", { 6,1,0,5 }, COLGROUP::CG_UI_PETAGG);

		uiPetEgg->GetActor()->GetTransform()->SetLocalPosition({ uiXPos, 2.06f, -3.0f });
		hatchList.push_back(uiPetEgg);	
	}

	coinScore = GetScene()->CreateActor(L"COINSCROE");
	
	coinScore->GetTransform()->SetLocalScale({ 0.75f,0.22f, 1.0f });
	coinScore->GetTransform()->SetLocalPosition({ 2.65f, 1.88f, __UI });
	coinScore->AddComponent<BoundingBox>(CG_COINBOX);
	coinScore->AddComponent<CoinBox>();


#pragma endregion
			
#pragma region WAVE
	//WAVE
	Resources::Load<Texture>(Path::JoinPath(L"AdventureScene", L"wave.png"));
	Resources::Create<Sprite>(L"wave.png", L"wave.png", 1, 22, 0, 21);
	My_Ptr<Actor> WAVE = GetScene()->CreateActor();
	WAVE->GetTransform()->SetLocalPosition({ 0.0f, 1.4f, -50.0f });
	WAVE->GetTransform()->SetLocalScale({ 640.0f / GameWindow::Inst()->GetWindowSize().y , 27.0f / GameWindow::Inst()->GetWindowSize().y });
	WAVE->GetTransform()->LocalScaleMultiple(GameWindow::Inst()->GetWindowSize().y / 100.0f);
	My_Ptr<SpriteRenderer> WaveRender = WAVE->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
	//Render->SetBlendOption();
	WaveRender->SetSprite(L"wave.png");
	WaveRender->SetBlender(L"BLEND1TO1");	//블랜더 변경
	My_Ptr<SpriteAnimation> WaveAni = WAVE->AddComponent<SpriteAnimation>();
	WaveAni->CreateAnimation(L"Wave", L"wave.png", 0, 21, 0.05f, true);
#pragma endregion




	Mouse::Inst().Init();



	{
		My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");

		My_Ptr<FontRenderer> font = hatchGoopy->AddComponent< FontRenderer>(RG_UI);
		font->SetFont(L"Silkscreen");
		//std::wstring text = 100;


		//std::to_wstring();
		//Thank you all for watching";


		font->SetText(L"&100", 11.0f, { 110.0f / 255.0f, 250.0f / 255.0f, 110.0f / 255.0f });

		My_Ptr<FontRenderer> font2 = hatchGoopy->AddComponent< FontRenderer>(RG_UI);
		font2->SetFont(L"Silkscreen");
		font2->SetText(L"$200", 11.0f, { 110.0f / 255.0f, 250.0f / 255.0f, 110.0f / 255.0f });
		font2->SetLocalPosition({ 3.0f, 0.0f, 0.0f });

		My_Ptr<FontRenderer> font3 = hatchGoopy->AddComponent< FontRenderer>(RG_UI);
		font3->SetFont(L"Silkscreen");
		font3->SetText(L"$200", 11.0f, { 110.0f / 255.0f, 250.0f / 255.0f, 110.0f / 255.0f });
		font3->SetLocalPosition({ 5.3f, 0.0f, 0.0f });

		My_Ptr<FontRenderer> font4 = hatchGoopy->AddComponent< FontRenderer>(RG_UI);
		font4->SetFont(L"Silkscreen");
		font4->SetText(L"$1000", 11.0f, { 110.0f / 255.0f, 250.0f / 255.0f, 110.0f / 255.0f });
		font4->SetLocalPosition({ 8.3f, 0.0f, 0.0f });

		My_Ptr<FontRenderer> font5 = hatchGoopy->AddComponent< FontRenderer>(RG_UI);
		font5->SetFont(L"Silkscreen");
		font5->SetText(L"$5000", 11.0f, { 110.0f / 255.0f, 250.0f / 255.0f, 110.0f / 255.0f });
		font5->SetLocalPosition({ 11.3f, 0.0f, 0.0f });


		My_Ptr<FontRenderer> font6 = hatchGoopy->AddComponent< FontRenderer>(RG_UI);
		font6->SetFont(L"Silkscreen");
		font6->SetText(L"$1000", 11.0f, { 110.0f / 255.0f, 250.0f / 255.0f, 110.0f / 255.0f });
		font6->SetLocalPosition({ 14.3f, 0.0f, 0.0f });

		My_Ptr<FontRenderer> font7 = hatchGoopy->AddComponent< FontRenderer>(RG_UI);
		font7->SetFont(L"Silkscreen");
		font7->SetText(L"$3000", 11.0f, { 110.0f / 255.0f, 250.0f / 255.0f, 110.0f / 255.0f });
		font7->SetLocalPosition({ 17.5f, 0.0f, 0.0f });

		hatchGoopy->GetTransform()->SetLocalPosition({ -2.75f, 1.93f, - 90.0f });
		hatchGoopy->GetTransform()->SetLocalScale({ 80.0f / GameWindow::Inst()->GetWindowSize().y , 80.0f / GameWindow::Inst()->GetWindowSize().y });
		hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);
		hatchGoopy->GetTransform()->LocalScaleMultiple(0.3f);
		//hatchGoopy->AddComponent<CreditMove>();
	}
	{
		My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");

		piiCnt = hatchGoopy->AddComponent< FontRenderer>(RG_UI);
		piiCnt->SetFont(L"Silkscreen");
		//std::wstring text = 100;


		//std::to_wstring();
		//Thank you all for watching";


		piiCnt->SetText(L"1", 32.0f, { 110.0f / 255.0f, 250.0f / 255.0f, 110.0f / 255.0f });
		

		hatchGoopy->GetTransform()->SetLocalPosition({ -1.47f, 2.33f, -90.0f });
		hatchGoopy->GetTransform()->SetLocalScale({ 80.0f / GameWindow::Inst()->GetWindowSize().y , 80.0f / GameWindow::Inst()->GetWindowSize().y });
		hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);
		hatchGoopy->GetTransform()->LocalScaleMultiple(0.3f);
		//hatchGoopy->AddComponent<CreditMove>();
	}
}

void AdventureUpdater::SceneUpdate()
{
	//GraphicDebug::DrawFontUI(L"100 Hello", Vector4::WHITE);
	
	
	//Food::SetFoodCount(FoodMove::GetFoodListSize());
	
	
	piiCnt->SetText(std::to_wstring(Food::GetMaxFoodCount()) , 32.0f, { 110.0f / 255.0f, 250.0f / 255.0f, 110.0f / 255.0f });

	Mouse::Inst().Update();

	//구피생성
	if (PregoMove::birthCnt > 0)
	{
		Goopy goopy = Goopy(GetScene(), L"Goopy.png", { 10, 35, 0, 349 });
		goopy.PregoOn();

		
		
		if (goopy.GetLogic()->GetPoint() < 20)
		{
			GoopyList::PushGoopy(goopy.GetActor());
		}

		PregoMove::birthCnt = 0;
	}


	//몬스터 생성 로직
	createMonsterTime -= Time::DeltaTime();
	if (Input::Up(L"F1") == true)//if (createMonsterTime < 0.0f)
	{
#pragma region WARP
		//뒷이미지


		if (createWarp == false)
		{
			Sound::Play(L"AWOOGA.wav");
			Sound::Stop(L"AdventureBgm");

			createPos = { Well512Random::Instance().GetFloatValue(-3.0f, 3.0f), Well512Random::Instance().GetFloatValue(-1.8f,1.0f), -40.0f };
			warpHole = GetScene()->CreateActor();
			warpHole->GetTransform()->SetLocalPosition(createPos);
			warpHole->GetTransform()->SetLocalScale({ 100.0f / GameWindow::Inst()->GetWindowSize().y , 220.0f / GameWindow::Inst()->GetWindowSize().y });
			warpHole->GetTransform()->LocalScaleMultiple(GameWindow::Inst()->GetWindowSize().y / 100.0f);
			My_Ptr<SpriteRenderer> WaveRender = warpHole->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
			//Render->SetBlendOption();
			WaveRender->SetSprite(L"warphole.png");
			//WaveRender->SetBlender(L"BLEND1TO1");	//블랜더 변경
			warpHoleAni = warpHole->AddComponent<SpriteAnimation>();
			warpHoleAni->CreateAnimation(L"Wave", L"warphole.png", 0, 16, 0.1f, false);

			createWarp = true;
		}
#pragma endregion

	}
	if(createWarp == true)
	{
		createPos.z = __PET;
		UINT idx = warpHoleAni->GetCurAni()->GetFrameIndex();
		if (12 == warpHoleAni->GetCurAni()->GetFrameIndex())
		{
			Sound::Play(L"MonsterBgm",L"BG Alien.wav");
			switch (kindsOfMonster)
			{
			case AdventureUpdater::BALROG:
				{
					monster = GetScene()->CreateActor();
					monster->GetTransform()->SetLocalPosition( createPos );
					monster->GetTransform()->SetLocalScale({ 160.0f / GameWindow::Inst()->GetWindowSize().y , 160.0f / GameWindow::Inst()->GetWindowSize().y });
					monster->GetTransform()->LocalScaleMultiple(GameWindow::Inst()->GetWindowSize().y / 100.0f);
					My_Ptr<SpriteRenderer> monsterRender = monster->AddComponent<SpriteRenderer>(RENDERGROUP::RG_MONSTER);
					//Render->SetBlendOption();
					monsterRender->SetSprite(L"balrog.png");
					

					My_Ptr<SpriteAnimation> monsterAni = monster->AddComponent<SpriteAnimation>();
					monsterAni->CreateAnimation(L"Swim",		L"balrog.png", 0, 9, 0.1f, true);
					monsterAni->CreateAnimation(L"Turn",		L"balrog.png", 10, 19, 0.1f, false);
					monsterAni->CreateAnimation(L"Swimfast",	L"balrog.png", 0, 9, 0.06f, true);
					monsterAni->CreateAnimation(L"Turnfast",	L"balrog.png", 10, 19, 0.06f, false);




					My_Ptr<BoundingSphere> monsterCollider = monster->AddComponent<BoundingSphere>(CG_MONSTER);
					monsterCollider->MultipleRadius(0.7f);
					monsterLogic = monster->AddComponent<MonsterMove>();
					monsterLogic->isBalog = true;

					hpRender = monster->AddComponent<SpriteRenderer>(RENDERGROUP::RG_MONSTER);
					hpRender->SetSprite(L"healthbar.png");
					hpRender->SetLocalPosition({ 0.0f, -0.5f, 0.0f });
					hpRender->UpdateOff();


					

					int num = (int)kindsOfMonster + 1;
					kindsOfMonster = (MONSTER)num;

					createMonsterTime = CREATETIME;
					createWarp = false;
					createMonster = true;

					MonsterList::PushMonster(monster);
				}
			break;
			case AdventureUpdater::GUS:
			{
				monster = GetScene()->CreateActor();
				monster->GetTransform()->SetLocalPosition(createPos);
				monster->GetTransform()->SetLocalScale({ 160.0f / GameWindow::Inst()->GetWindowSize().y , 160.0f / GameWindow::Inst()->GetWindowSize().y });
				monster->GetTransform()->LocalScaleMultiple(GameWindow::Inst()->GetWindowSize().y / 100.0f);
				My_Ptr<SpriteRenderer> monsterRender = monster->AddComponent<SpriteRenderer>(RENDERGROUP::RG_MONSTER);
				//Render->SetBlendOption();
				monsterRender->SetSprite(L"gus.png");
				My_Ptr<SpriteAnimation> monsterAni = monster->AddComponent<SpriteAnimation>();
				monsterAni->CreateAnimation(L"Swim", L"gus.png", 0, 9, 0.1f, true);
				monsterAni->CreateAnimation(L"Turn", L"gus.png", 10, 19, 0.1f, false);
				monsterAni->CreateAnimation(L"Swimfast", L"gus.png", 0, 9, 0.06f, true);
				monsterAni->CreateAnimation(L"Turnfast", L"gus.png", 10, 19, 0.06f, false);
				monsterAni->CreateAnimation(L"Eat", L"gus.png", 20, 29, 0.06f, false);


				My_Ptr<BoundingSphere> monsterCollider = monster->AddComponent<BoundingSphere>(CG_GUS);
				monsterCollider->MultipleRadius(0.7f);
				gusLogic = monster->AddComponent<GusMove>();


				hpRender = monster->AddComponent<SpriteRenderer>(RENDERGROUP::RG_MONSTER);
				hpRender->SetSprite(L"healthbar.png");
				hpRender->SetLocalPosition({ 0.0f, -0.5f, 0.0f });
				hpRender->UpdateOff();

				int num = (int)kindsOfMonster + 1;
				kindsOfMonster = (MONSTER)num;

				createMonsterTime = CREATETIME;
				createWarp = false;
				createMonster = true;

				existGus = true;
				PetList::existGus = true;


				MonsterList::PushMonster(monster);
			}
			break;
			case AdventureUpdater::PSYCHOSQUID:
			{
				monster = GetScene()->CreateActor();
				monster->GetTransform()->SetLocalPosition(createPos);
				monster->GetTransform()->SetLocalScale({ 160.0f / GameWindow::Inst()->GetWindowSize().y , 160.0f / GameWindow::Inst()->GetWindowSize().y });
				monster->GetTransform()->LocalScaleMultiple(GameWindow::Inst()->GetWindowSize().y / 100.0f);
				My_Ptr<SpriteRenderer> monsterRender = monster->AddComponent<SpriteRenderer>(RENDERGROUP::RG_MONSTER);
				//Render->SetBlendOption();
				monsterRender->SetSprite(L"psychosquid.png");
				My_Ptr<SpriteAnimation> monsterAni = monster->AddComponent<SpriteAnimation>();
				monsterAni->CreateAnimation(L"Swim", L"psychosquid.png", 0, 9, 0.1f, true);
				monsterAni->CreateAnimation(L"Turn", L"psychosquid.png", 10, 19, 0.1f, false);
				monsterAni->CreateAnimation(L"Swimfast", L"psychosquid.png", 0, 9, 0.06f, true);
				monsterAni->CreateAnimation(L"Turnfast", L"psychosquid.png", 10, 19, 0.06f, false);
				

				
				monsterAni->CreateAnimation(L"ChangeSwim", L"psychosquid.png", 20, 29, 0.1f, true);
				monsterAni->CreateAnimation(L"ChangeTurn", L"psychosquid.png", 30, 39, 0.1f, false);
				monsterAni->CreateAnimation(L"ChangeSwimfast", L"psychosquid.png", 20, 29, 0.06f, true);
				monsterAni->CreateAnimation(L"ChangeTurnfast", L"psychosquid.png", 30, 39, 0.06f, false);
				monsterAni->CreateAnimation(L"Change", L"psychosquid.png", 40, 49, 0.1f, false);
				monsterAni->CreateAnimation(L"Change2", L"psychosquid.png", 50, 59, 0.1f, false);

				My_Ptr<BoundingSphere> monsterCollider = monster->AddComponent<BoundingSphere>(CG_DENTACLE);
				monsterCollider->MultipleRadius(0.7f);

				monster->AddComponent<DentacleMove>();
				dentacleLogic = monster->AddComponent<DentacleMove>();

				hpRender = monster->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
				hpRender->SetSprite(L"healthbar.png");
				hpRender->SetLocalPosition({ 0.0f, -0.5f, 0.0f });

	
				int num = (int)kindsOfMonster + 1;
				kindsOfMonster = (MONSTER)num;

				createMonsterTime = CREATETIME;
				createWarp = false;
				createMonster = true;

				MonsterList::PushMonster(monster);
			}
			break;

			case AdventureUpdater::BOSS:
			{
				monster = GetScene()->CreateActor();
				monster->GetTransform()->SetLocalPosition(createPos);
				monster->GetTransform()->SetLocalScale({ 160.0f / GameWindow::Inst()->GetWindowSize().y , 160.0f / GameWindow::Inst()->GetWindowSize().y });
				monster->GetTransform()->LocalScaleMultiple(GameWindow::Inst()->GetWindowSize().y / 100.0f);
				My_Ptr<SpriteRenderer> monsterRender = monster->AddComponent<SpriteRenderer>(RENDERGROUP::RG_MONSTER);
				//Render->SetBlendOption();
				monsterRender->SetSprite(L"boss.png");
				My_Ptr<SpriteAnimation> monsterAni = monster->AddComponent<SpriteAnimation>();
				monsterAni->CreateAnimation(L"Swim", L"boss.png", 0, 9, 0.1f, true);
				monsterAni->CreateAnimation(L"Turn", L"boss.png", 10, 19, 0.1f, false);
				monsterAni->CreateAnimation(L"Swimfast", L"boss.png", 0, 9, 0.06f, true);
				monsterAni->CreateAnimation(L"Turnfast", L"boss.png", 10, 19, 0.06f, false);
		
				hpRender = monster->AddComponent<SpriteRenderer>(RENDERGROUP::RG_MONSTER);
				hpRender->SetSprite(L"healthbar.png");
				hpRender->SetLocalPosition({ 0.0f, -0.5f, 0.0f });
				

				My_Ptr<BoundingSphere> monsterCollider = monster->AddComponent<BoundingSphere>(CG_BOSS);
				monsterCollider->MultipleRadius(0.7f);

				bossLogic = monster->AddComponent<BossMove>();

				int num = (int)kindsOfMonster + 1;
				kindsOfMonster = (MONSTER)num;

				createMonsterTime = CREATETIME;
				createWarp = false;
				createMonster = true;

				MonsterList::PushMonster(monster);
			}
			break;


			}
		}
	}

	if (createMonster == true && warpHoleAni->GetCurAni()->aniEnd == true)
	{
		warpHole->Die();
		createWarp = false;
		createMonster = false;
		//existMonster = true;
	}


	if (Input::Down(L"MOUSELEFT") == true && Mouse::Inst().GetPos().y < 1.8f && Mouse::Inst().GetPos().y > -1.8
		&& Mouse::Inst().GetPos().x < 3.2f && Mouse::Inst().GetPos().x > -3.2f)	//먹이 생성
	{	
		if (MonsterList::GetMonsterList().size() == 0)
		{
			
			Vector4 createPos = { Mouse::Inst().GetPos().x, Mouse::Inst().GetPos().y, 90.0f };
			Food food = Food(GetScene(), createPos);
			Food::SetFoodCount(FoodMove::GetFoodListSize());
			
		}
		else
		{
			if (PetList::existGus == true)
			{
				
				Vector4 createPos = { Mouse::Inst().GetPos().x, Mouse::Inst().GetPos().y, 90.0f };
				Food food = Food(GetScene(), createPos);

				Food::SetFoodCount(FoodMove::GetFoodListSize());
			}
			//총이 나간다
		}		
	}


#pragma region BUBBLE
	bubbleTime1 -= Time::DeltaTime();
	bubbleTime2 -= Time::DeltaTime();
	bubbleTime3 -= Time::DeltaTime();

	if (bubbleTime1 < 0.0f)
	{
		Sound::Play(L"bubbles.wav");
		for (int i = 0; i < 5; ++i)
		{
			My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");
			My_Ptr<SpriteRenderer> hatchGoopyRenderer = hatchGoopy->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
			hatchGoopyRenderer->SetSprite(L"bubbles.png");
			hatchGoopyRenderer->SetBlender(L"BLEND1TO1");
			My_Ptr<SpriteAnimation>  hatchGoopyAni = hatchGoopy->AddComponent<SpriteAnimation>();
			//hatchGoopyAni->CreateAnimation(L"egg1", L"egg.png", 0, 0, 0.1f, false);
			hatchGoopyAni->CreateAnimation(L"bubbles", L"bubbles.png", 0, 4, 0.4f, false);
			hatchGoopy->GetTransform()->SetLocalPosition({ Well512Random::Instance().GetFloatValue(-2.7f, -2.5f), Well512Random::Instance().GetFloatValue(-1.8f, -1.0f), __UI });
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
		for (int i = 0; i < 5; ++i)
		{
			My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");
			My_Ptr<SpriteRenderer> hatchGoopyRenderer = hatchGoopy->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
			hatchGoopyRenderer->SetSprite(L"bubbles.png");
			hatchGoopyRenderer->SetBlender(L"BLEND1TO1");
			My_Ptr<SpriteAnimation>  hatchGoopyAni = hatchGoopy->AddComponent<SpriteAnimation>();
			//hatchGoopyAni->CreateAnimation(L"egg1", L"egg.png", 0, 0, 0.1f, false);
			hatchGoopyAni->CreateAnimation(L"bubbles", L"bubbles.png", 0, 4, 0.4f, false);
			hatchGoopy->GetTransform()->SetLocalPosition({ Well512Random::Instance().GetFloatValue(2.7f, 2.5f), Well512Random::Instance().GetFloatValue(-1.8f, -1.0f), __UI });
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
		for (int i = 0; i < 5; ++i)
		{
			My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");
			My_Ptr<SpriteRenderer> hatchGoopyRenderer = hatchGoopy->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
			hatchGoopyRenderer->SetSprite(L"bubbles.png");
			hatchGoopyRenderer->SetBlender(L"BLEND1TO1");
			My_Ptr<SpriteAnimation>  hatchGoopyAni = hatchGoopy->AddComponent<SpriteAnimation>();
			//hatchGoopyAni->CreateAnimation(L"egg1", L"egg.png", 0, 0, 0.1f, false);
			hatchGoopyAni->CreateAnimation(L"bubbles", L"bubbles.png", 0, 4, 0.4f, false);
			hatchGoopy->GetTransform()->SetLocalPosition({ Well512Random::Instance().GetFloatValue(1.0f, -1.0f), Well512Random::Instance().GetFloatValue(-1.8f, -1.0f), __UI });
			hatchGoopy->GetTransform()->SetLocalScale({ 80.0f / GameWindow::Inst()->GetWindowSize().y , 80.0f / GameWindow::Inst()->GetWindowSize().y });
			hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);
			hatchGoopy->GetTransform()->LocalScaleMultiple(0.3f);
			hatchGoopy->AddComponent<BubbleMove>();
		}
		bubbleTime3 = Well512Random::Instance().GetFloatValue(5.0f, 15.0f);
	}
#pragma endregion

	if (MonsterList::GetMonsterList().size() != 0 )
	{
		

		switch ((kindsOfMonster-1))
		{
		case AdventureUpdater::BALROG:
		{
			float HP = monsterLogic->GetHp();
			hpRender->SetRateHp(HP);
		}

			break;
		case AdventureUpdater::GUS:
		{
			float HP = monsterLogic->GetHp();

			HP /= 2.0f;
			hpRender->SetRateHp(HP);
		}
			break;
		case AdventureUpdater::PSYCHOSQUID:
		{
			float HP = dentacleLogic->GetHp();
			
			//HP /= 3.0f;
			
			hpRender->SetRateHp(HP);

		}
			break;
		case AdventureUpdater::BOSS:
		{
			float HP = bossLogic->GetHp();

			//HP /= 5.0f;

			hpRender->SetRateHp(HP);
		}
			break;
		default:
			break;
		}

	}
	GoopyList::GoopyList_Update();


}

void AdventureUpdater::ChangeEnd()
{
	int a = 0;
}