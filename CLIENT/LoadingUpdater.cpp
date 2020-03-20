#include "LoadingUpdater.h"
#include <Input.h>

#include <Camera.h>
#include <SpriteRenderer.h>
#include <Texture.h>
#include <Sprite.h>
#include <SpriteAnimation.h>
#include <RectRenderer.h>

#include <GameWindow.h>

#include "ENUM.h"
#include "Object.h"
#include "BackGround.h"

#include "Mouse.h"
#include <GraphicDebug.h>

#include <LoadingStinkyMove.h>
#include <Scene.h>
#include <Sound.h>

LoadingUpdater::LoadingUpdater()
{
}


LoadingUpdater::~LoadingUpdater()
{
}

void LoadingUpdater::Loading()
{
	//GraphicDebug::DebugON();
	Path::CreatePath(L"AdventureScene", L"Texture\\AdventureScene");
	Mouse::Inst().SetScene(GetScene());


	//LOAD
	Resources::Load<Texture>(Path::JoinPath(L"AdventureScene", L"food.png"));
	Resources::Create<Sprite>(L"food.png", L"food.png", 10, 5);

	Resources::Load<Texture>(Path::JoinPath(L"AdventureScene", L"UltraFish.png"));
	Resources::Create<Sprite>(L"UltraFish.png", L"UltraFish.png", 10, 4);


	Resources::Load<Texture>(Path::JoinPath(L"AdventureScene", L"lazergunz.png"));
	Resources::Create<Sprite>(L"lazergunz.png", L"lazergunz.png", 10, 1);

	Resources::Load<Texture>(Path::JoinPath(L"AdventureScene", L"egg.png"));
	Resources::Create<Sprite>(L"egg.png", L"egg.png", 13, 3);

	Resources::Load<Texture>(Path::JoinPath(L"AdventureScene", L"bubbles.png"));
	Resources::Create<Sprite>(L"bubbles.png", L"bubbles.png", 5, 1);

	Resources::Load<Texture>(Path::JoinPath(L"AdventureScene", L"chomp.png"));
	Resources::Create<Sprite>(L"chomp.png", L"chomp.png", 6, 1);

	Resources::Load<Texture>(Path::JoinPath(L"AdventureScene", L"HatchBubble.gif"));
	Resources::Create<Sprite>(L"HatchBubble.gif", L"HatchBubble.gif", 1, 1);


	Resources::Load<Texture>(Path::JoinPath(L"AdventureScene", L"money.png"));
	Resources::Create<Sprite>(L"money.png", L"money.png", 10, 6);

	Resources::Load<Texture>(Path::JoinPath(L"AdventureScene", L"warphole.png"));
	Resources::Create<Sprite>(L"warphole.png", L"warphole.png", 17, 1);

	Resources::Load<Texture>(Path::JoinPath(L"AdventureScene", L"halo.png"));
	Resources::Create<Sprite>(L"halo.png", L"halo.png", 10, 2);

	Resources::Load<Texture>(Path::JoinPath(L"AdventureScene", L"ampcharge.png"));
	Resources::Create<Sprite>(L"ampcharge.png", L"ampcharge.png", 10, 2);

	Resources::Load<Texture>(Path::JoinPath(L"AdventureScene", L"punch.png"));
	Resources::Create<Sprite>(L"punch.png", L"punch.png", 4, 2);

	Resources::Load<Texture>(Path::JoinPath(L"AdventureScene", L"balls.png"));
	Resources::Create<Sprite>(L"balls.png", L"balls.png", 10, 4);

	Resources::Load<Texture>(Path::JoinPath(L"AdventureScene", L"items.png"));
	Resources::Create<Sprite>(L"items.png", L"items.png", 3, 1);

	Resources::Load<Texture>(Path::JoinPath(L"AdventureScene", L"GunShoot.png"));
	Resources::Create<Sprite>(L"GunShoot.png", L"GunShoot.png", 4, 4);
	Resources::Load<Texture>(Path::JoinPath(L"AdventureScene", L"GunShoot1.png"));
	Resources::Create<Sprite>(L"GunShoot1.png", L"GunShoot1.png", 4, 4);
	Resources::Load<Texture>(Path::JoinPath(L"AdventureScene", L"GunShoot2.png"));
	Resources::Create<Sprite>(L"GunShoot2.png", L"GunShoot2.png", 4, 4);
	Resources::Load<Texture>(Path::JoinPath(L"AdventureScene", L"GunShoot3.png"));
	Resources::Create<Sprite>(L"GunShoot3.png", L"GunShoot3.png", 4, 4);
	Resources::Load<Texture>(Path::JoinPath(L"AdventureScene", L"GunShoot4.png"));
	Resources::Create<Sprite>(L"GunShoot4.png", L"GunShoot4.png", 4, 4);
	Resources::Load<Texture>(Path::JoinPath(L"AdventureScene", L"GunShoot5.png"));
	Resources::Create<Sprite>(L"GunShoot5.png", L"GunShoot5.png", 4, 4);
	Resources::Load<Texture>(Path::JoinPath(L"AdventureScene", L"GunShoot6.png"));
	Resources::Create<Sprite>(L"GunShoot6.png", L"GunShoot6.png", 4, 4);
	Resources::Load<Texture>(Path::JoinPath(L"AdventureScene", L"GunShoot7.png"));
	Resources::Create<Sprite>(L"GunShoot7.png", L"GunShoot7.png", 4, 4);
	Resources::Load<Texture>(Path::JoinPath(L"AdventureScene", L"GunShoot8.png"));
	Resources::Create<Sprite>(L"GunShoot8.png", L"GunShoot8.png", 4, 4);


	Resources::Load<Texture>(Path::JoinPath(L"AdventureScene", L"smoke.png"));
	Resources::Create<Sprite>(L"smoke.png", L"smoke.png", 21, 1);

	Resources::Load<Texture>(Path::JoinPath(L"AdventureScene", L"healthbar.png"));
	Resources::Create<Sprite>(L"healthbar.png", L"healthbar.png", 1, 1);

	Resources::Load<Texture>(Path::JoinPath(L"AdventureScene", L"healthbartube_.png"));
	Resources::Create<Sprite>(L"healthbartube_.png", L"healthbartube_.png", 1, 1);

	//MONSTER
	//1
	Resources::Load<Texture>(Path::JoinPath(L"AdventureScene", L"balrog.png"));
	Resources::Create<Sprite>(L"balrog.png", L"balrog.png", 10, 2);


	//2
	Resources::Load<Texture>(Path::JoinPath(L"AdventureScene", L"gus.png"));
	Resources::Create<Sprite>(L"gus.png", L"gus.png", 10, 3);

	//3
	Resources::Load<Texture>(Path::JoinPath(L"AdventureScene", L"psychosquid.png"));
	Resources::Create<Sprite>(L"psychosquid.png", L"psychosquid.png", 10, 6);


	//4
	Resources::Load<Texture>(Path::JoinPath(L"AdventureScene", L"ulysses.png"));
	Resources::Create<Sprite>(L"ulysses.png", L"ulysses.png", 10, 3);

	//5
	Resources::Load<Texture>(Path::JoinPath(L"AdventureScene", L"boss.png"));
	Resources::Create<Sprite>(L"boss.png", L"boss.png", 10, 2);
	Resources::Load<Texture>(Path::JoinPath(L"AdventureScene", L"smallsylv.png"));
	Resources::Create<Sprite>(L"smallsylv.png", L"smallsylv.png", 10, 2);


	//PET
	Resources::Load<Texture>(Path::JoinPath(L"AdventureScene", L"pearl.png"));
	Resources::Create<Sprite>(L"pearl.png", L"pearl.png", 1, 1);

	Mouse::Inst().SetScene(GetScene());
	Mouse::Inst().Init();

	Path::CreatePath(L"Texture");
	Path::CreatePath(L"LoadingScene", L"Texture\\LoadingScene");

	Resources::Load<Texture>(Path::JoinPath(L"LoadingScene", L"loadingscreen.jpg"));
	Resources::Create<Sprite>(L"loadingscreen.jpg", L"loadingscreen.jpg", 1, 1);

	Resources::Load<Texture>(Path::JoinPath(L"LoadingScene", L"loaderbarover.png"));
	Resources::Create<Sprite>(L"loaderbarover.png", L"loaderbarover.png", 1, 1);
	Resources::Load<Texture>(Path::JoinPath(L"LoadingScene", L"Loadingstinky.png"));
	Resources::Create<Sprite>(L"Loadingstinky.png", L"Loadingstinky.png", 10, 3);


	//SOUND
	//Path::CreatePath(L"Sound", L"Texture\\Sound");
	Path::CreatePath(L"Sound");

	std::vector<File> AllFileList;

	Directory dic;
	dic.ReplaceToParentPath();
	dic.MoveDirectory(L"_BIN");
	dic.MoveDirectory(L"Sound");

	dic.GetAllFileName(AllFileList, L"*.*");

	std::wstring Name;
	for (size_t i = 0; i < AllFileList.size(); i++)
	{
		Name = AllFileList[i].GetFileName();

		Resources::Load<Sound>(Path::JoinPath(L"Sound", Name.c_str()));

		//HRES::Load<HTEX>(HPATH::PlusPath(L"TEX", Name.c_str()));
	}

	//CAMERA
	My_Ptr<Actor> mainCam = GetScene()->CreateActor(L"LOADINGCAM");
	mainCam->GetTransform()->SetPosition({ 0.0f, 0.0f, -100.0f });
	My_Ptr<Camera> camera = mainCam->AddComponent<Camera>(RENDERGROUP::RG_PLAYER);
	camera->SetProjMode(PROJMODE::ORTHOGONAL);	
	camera->SetArea(GameWindow::Inst()->GetWindowSize().x / 100.0f, GameWindow::Inst()->GetWindowSize().y / 100.0f);

	My_Ptr<Actor> monster = GetScene()->CreateActor();
	monster->GetTransform()->SetLocalPosition({0.0f,0.0f,0.0f});
	monster->GetTransform()->SetLocalScale({ 640.0f / GameWindow::Inst()->GetWindowSize().y , 480.0f / GameWindow::Inst()->GetWindowSize().y });
	monster->GetTransform()->LocalScaleMultiple(GameWindow::Inst()->GetWindowSize().y / 100.0f);
	My_Ptr<SpriteRenderer> monsterRender = monster->AddComponent<SpriteRenderer>(RENDERGROUP::RG_PLAYER);
	//Render->SetBlendOption();
	monsterRender->SetSprite(L"loadingscreen.jpg");
	
	
	{
		My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");

		hatchGoopy->GetTransform()->SetLocalPosition({ -0.14f, -1.93f, -10.0f });
		hatchGoopy->GetTransform()->SetLocalScale({ 250.0f / GameWindow::Inst()->GetWindowSize().y  , 31.0f / GameWindow::Inst()->GetWindowSize().x * 1.2f });
		//hatchGoopy->GetTransform()->SetLocalScale({ 1.0f , 3.0f});
		hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);
		//hatchGoopy->GetTransform()->SetLocalScale(1.2f);
		//hatchGoopy->GetTransform()->SetLocalScale({1.0f, 1.0f, 1.0f});
		

		loadingRender = hatchGoopy->AddComponent<SpriteRenderer>(RG_PLAYER);
		loadingRender->SetSprite(L"loaderbarover.png");
		loadingRender->SetBlender(L"BLEND1TO1");
		loadingRender->SetRateHp(0.0f);


		//My_Ptr<SpriteAnimation> Anirender = hatchGoopy->AddComponent<SpriteAnimation>();
		//Anirender->CreateAnimation(L"Base", L"loaderbarover.png", 0, 0, false);
		//Anirender->CreateAnimation(L"On", L"loaderbarover.png", 1, 1, false);
		//Anirender->CreateAnimation(L"Click", L"loaderbarover.png", 2, 2, false);
		///////////////COLLIDER
	}

	{
		My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");

		hatchGoopy->GetTransform()->SetLocalPosition({ -1.24f, -1.93f, -50.0f });
		hatchGoopy->GetTransform()->SetLocalScale({ 80.0f / GameWindow::Inst()->GetWindowSize().y  , 80.0f / GameWindow::Inst()->GetWindowSize().x  });
		//hatchGoopy->GetTransform()->SetLocalScale({ 1.0f , 3.0f});
		hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);
		//hatchGoopy->GetTransform()->SetLocalScale(1.2f);
		//hatchGoopy->GetTransform()->SetLocalScale({1.0f, 1.0f, 1.0f});


		My_Ptr<SpriteRenderer> stinkyRender = hatchGoopy->AddComponent<SpriteRenderer>(RG_PLAYER);
		stinkyRender->SetSprite(L"Loadingstinky.png");
		stinkyRender->TurnRight();
		//loadingRender->SetBlender(L"BLEND1TO1");
		//loadingRender->SetRateHp(0.0f);


		My_Ptr<SpriteAnimation> Anirender = hatchGoopy->AddComponent<SpriteAnimation>();
		Anirender->CreateAnimation(L"Base", L"Loadingstinky.png", 0, 9, 0.1f,true);

		hatchGoopy->AddComponent<LoadingStinkyMove>();
		///////////////COLLIDER
	}


	//My_Ptr<SpriteAnimation> monsterAni = monster->AddComponent<SpriteAnimation>();
	//monsterAni->CreateAnimation(L"Swim", L"smallsylv.png", 0, 9, 0.1f, true);
	//monsterAni->CreateAnimation(L"Turn", L"smallsylv.png", 10, 19, 0.1f, false);
	//monsterAni->CreateAnimation(L"Swimfast", L"smallsylv.png", 0, 9, 0.06f, true);
	//monsterAni->CreateAnimation(L"Turnfast", L"smallsylv.png", 10, 19, 0.06f, false);

	//BackGround backGround = BackGround(GetScene(), L"loadingscreen.jpg", {1,1,0,0});
	

	Input::CreateKey(L"TitleScene",	'2');


	Input::CreateKey(L"MOUSELEFT", VK_LBUTTON);
	//GetScene()->ChangeScene(L"SelectScene");


	//SOUND

	Sound::Play(L"LoadingBgm", L"BG Tank 4.wav", 100);
	//Sound::Play(L"LoadingBgm", L"BG Tank 4.wav", 100);
	//Sound::Play(L"BG Tank 4.wav");
	//Sound::Stop(L"LoadingBgm");
}

void LoadingUpdater::SceneUpdate()
{
	if (Input::Up(L"TitleScene") == true)
	{
		Sound::Play(L"ButtonClick", L"buttonclick.wav");

		int a = 0;
		GameWindow::Inst()->ChangeScene(L"TitleScene");
		//GetScene()->ChangeScene(L"TitleScene");
	}
	loadingRender->SetRateHp(LoadingStinkyMove::loadingRate);

}