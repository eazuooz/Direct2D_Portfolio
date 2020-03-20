#include "TitleUpdater.h"
#include <Input.h>


#include <Camera.h>
#include <SpriteRenderer.h>
#include <Texture.h>
#include <Sprite.h>
#include <SpriteAnimation.h>
#include <RectRenderer.h>

#include <GameWindow.h>

#include <MeryEyeLogic.h>
#include <MeryTailLogic.h>

#include "ENUM.h"
#include "BackGround.h"
#include "Mery.h"

#include <GraphicDebug.h>
#include <FontRenderer.h>

#include <BoundingBox.h>
#include <ENUM.h>

#include "Mouse.h"
#include <Sound.h>
//#include <Font.h>



TitleUpdater::TitleUpdater() 
{
	
}


TitleUpdater::~TitleUpdater()
{
}

void TitleUpdater::Loading()
{



	GetScene()->colliderMgr.Link(COLGROUP::CG_ADVENTURE, COLGROUP::CG_MOUSE);


	Path::CreatePath(L"TitleScene" ,L"Texture\\TitleScene");

	

	
	
		
	//CAMERA
	My_Ptr<Actor> mainCam = GetScene()->CreateActor(L"TITLECAM");
	mainCam->GetTransform()->SetPosition({ 0.0f, 0.0f, -100.0f });	
	My_Ptr<Camera> camera = mainCam->AddComponent<Camera>(RENDERGROUP::RG_PLAYER);
	camera->SetProjMode(PROJMODE::ORTHOGONAL);
	//camera->SetArea( (8.0f * 10.0f / 6.0f) ,  10.0f );
	camera->SetArea(GameWindow::Inst()->GetWindowSize().x/ 100.0f, GameWindow::Inst()->GetWindowSize().y / 100.0f);
	

	Resources::Load<Texture>(Path::JoinPath(L"TitleScene", L"selectorback.jpg"));
	Resources::Create<Sprite>(L"selectorback.jpg", L"selectorback.jpg", 1, 1, 0, 0);
	My_Ptr<Actor> selectBack = GetScene()->CreateActor();
	selectBack->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, 1.0f });
	selectBack->GetTransform()->SetLocalScale({ 640.0f / 480.0f , 480.0f / 480.0f });
	selectBack->GetTransform()->LocalScaleMultiple(4.8f);
	My_Ptr<SpriteRenderer> selectBackRender = selectBack->AddComponent<SpriteRenderer>(RENDERGROUP::RG_PLAYER);
	selectBackRender->SetSprite(L"selectorback.jpg");
	
#pragma region MERYEYE
	//Resources::Load<Texture>(Path::JoinPath(L"TitleScene", L"merylblink.gif"));
	//Resources::Create<Sprite>(L"merylblink.gif", L"merylblink.gif", 8, 1, 0, 8); 
	//My_Ptr<Actor> meryEye = GetScene()->CreateActor();
	//meryEye->GetTransform()->SetPos({ -1.535f, 0.325f, 0.9f });
	//meryEye->GetTransform()->SetScale({ 55.0f / 25.0f , 25.0f / 25.0f });
	//meryEye->GetTransform()->ScaleMul(0.25f);
	//My_Ptr<SpriteRenderer> meryEyeRender = meryEye->AddComponent<SpriteRenderer>(RG_PLAYER);
	//meryEyeRender->SetSprite(L"merylblink.gif");
	//My_Ptr<SpriteAnimation> meryEyeAni = meryEye->AddComponent< SpriteAnimation>();
	//meryEyeAni->CreateAnimation(L"MeryEyeBase", L"merylblink.gif", 0, 1, 0.1f, true);
	//meryEyeAni->CreateAnimation(L"MeryEyeBlink", L"merylblink.gif", 2, 8, 0.1f, false);
	//meryEye->AddComponent<MeryLogic>();
#pragma endregion

	   	 
		
	MeryEye mery = MeryEye(GetScene(), L"merylblink.gif", {8,1,0,7});	//ÀÎ¾î ´«±ôºýÀÓ	
	mery.GetActor()->AddComponent<MeryEyeLogic>();

	MeryTail meryTail = MeryTail(GetScene(), L"merytail.png", {10,1,0,9});
	meryTail.GetActor()->AddComponent<MeryTailLogic>();


	//const wchar_t* _Name, float _FontSize, Vector4 _Position, Vector4 _Color, FW1_TEXT_FLAG _Flag
	/*Font font = Font();
	font.DrawUI(L"adsfasdf", 1.0f, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f });*/

	//GraphicDebug::DrawFontUI(L"100 Hello", Vector4::WHITE);
	Resources::Load<Texture>(Path::JoinPath(L"TitleScene", L"battletankbutton.png"));
	Resources::Create<Sprite>(L"battletankbutton.png", L"battletankbutton.png", 3, 1);



	Resources::Load<Texture>(Path::JoinPath(L"TitleScene", L"middlebutton.png"));
	Resources::Create<Sprite>(L"middlebutton.png", L"middlebutton.png", 3, 1);

	Resources::Load<Texture>(Path::JoinPath(L"TitleScene", L"speechbubble.png"));
	Resources::Create<Sprite>(L"speechbubble.png", L"speechbubble.png", 1, 1);


	{
		My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");

		hatchGoopy->GetTransform()->SetLocalPosition({ 1.45f, 1.6f, -10.0f });
		hatchGoopy->GetTransform()->SetLocalScale({ 217.0f / GameWindow::Inst()->GetWindowSize().y , 66.0f / GameWindow::Inst()->GetWindowSize().x * 1.35f });
		//hatchGoopy->GetTransform()->SetLocalScale({ 1.0f , 3.0f});
		hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);
		//hatchGoopy->GetTransform()->SetLocalScale(1.2f);
		//hatchGoopy->GetTransform()->SetLocalScale({1.0f, 1.0f, 1.0f});

		My_Ptr<BoundingBox> collider =  hatchGoopy->AddComponent<BoundingBox>(CG_ADVENTURE);

		collider->RegisterEnterFunction(&TitleUpdater::Enter, this);
		collider->RegisterStayFunction(&TitleUpdater::Stay, this);
		collider->RegisterExitFunction(&TitleUpdater::Exit, this);

		My_Ptr<SpriteRenderer> render = hatchGoopy->AddComponent<SpriteRenderer>(RG_PLAYER);
		render->SetSprite(L"middlebutton.png");
		My_Ptr<SpriteAnimation> Anirender = hatchGoopy->AddComponent<SpriteAnimation>();
		Anirender->CreateAnimation(L"Base", L"middlebutton.png", 0, 0, false);
		Anirender->CreateAnimation(L"On", L"middlebutton.png", 1, 1, false);
		Anirender->CreateAnimation(L"Click", L"middlebutton.png", 2, 2, false);

		//Anirender->ChangeAnimation(L"On");

		My_Ptr<FontRenderer> font = hatchGoopy->AddComponent<FontRenderer>(RG_PLAYER);
		font->SetLocalPosition({ 0.0f, 0.2f,0.0f });
		font->SetFont(L"Silkscreen");
		std::wstring text;
		text += L"BONUS ADVENTURE";

		font->SetText(text, 20.0f, { 253.0f / 255.0f, 238.0f / 255.0f , 0.0f });
	}

	{
		My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");

		hatchGoopy->GetTransform()->SetLocalPosition({ 1.45f, 0.75f, -10.0f });
		hatchGoopy->GetTransform()->SetLocalScale({ 217.0f / GameWindow::Inst()->GetWindowSize().y , 66.0f  / GameWindow::Inst()->GetWindowSize().x * 1.1f });
		//hatchGoopy->GetTransform()->SetLocalScale({ 1.0f , 3.0f});
		hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);
		//hatchGoopy->GetTransform()->SetLocalScale(1.2f);
		//hatchGoopy->GetTransform()->SetLocalScale({1.0f, 1.0f, 1.0f});

		My_Ptr<BoundingBox> collider = hatchGoopy->AddComponent<BoundingBox>(CG_ADVENTURE);

		collider->RegisterEnterFunction(&TitleUpdater::Enter, this);
		collider->RegisterStayFunction(&TitleUpdater::Stay, this);
		collider->RegisterExitFunction(&TitleUpdater::Exit, this);

		My_Ptr<SpriteRenderer> render = hatchGoopy->AddComponent<SpriteRenderer>(RG_PLAYER);
		render->SetSprite(L"battletankbutton.png");
		Anirender1 = hatchGoopy->AddComponent<SpriteAnimation>();
		Anirender1->CreateAnimation(L"Base", L"battletankbutton.png", 0, 0, false);
		Anirender1->CreateAnimation(L"On", L"battletankbutton.png", 1, 1, false);
		Anirender1->CreateAnimation(L"Click", L"battletankbutton.png", 2, 2, false);

		//Anirender->ChangeAnimation(L"On");

		My_Ptr<FontRenderer> font = hatchGoopy->AddComponent<FontRenderer>(RG_PLAYER);
		font->SetLocalPosition({ 0.0f, 0.2f,0.0f });
		font->SetFont(L"Silkscreen");
		std::wstring text;
		text += L"TIME TRIAL";

		font->SetText(text, 20.0f, { 253.0f / 255.0f, 238.0f / 255.0f , 0.0f });
	}

	{
		My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");

		hatchGoopy->GetTransform()->SetLocalPosition({ 1.45f, 0.06f, -10.0f });
		hatchGoopy->GetTransform()->SetLocalScale({ 217.0f / GameWindow::Inst()->GetWindowSize().y , 66.0f / GameWindow::Inst()->GetWindowSize().x * 1.1f });
		//hatchGoopy->GetTransform()->SetLocalScale({ 1.0f , 3.0f});
		hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);
		//hatchGoopy->GetTransform()->SetLocalScale(1.2f);
		//hatchGoopy->GetTransform()->SetLocalScale({1.0f, 1.0f, 1.0f});

		My_Ptr<BoundingBox> collider = hatchGoopy->AddComponent<BoundingBox>(CG_ADVENTURE);

		collider->RegisterEnterFunction(&TitleUpdater::Enter, this);
		collider->RegisterStayFunction(&TitleUpdater::Stay, this);
		collider->RegisterExitFunction(&TitleUpdater::Exit, this);

		My_Ptr<SpriteRenderer> render = hatchGoopy->AddComponent<SpriteRenderer>(RG_PLAYER);
		render->SetSprite(L"battletankbutton.png");
		My_Ptr<SpriteAnimation> Anirender = hatchGoopy->AddComponent<SpriteAnimation>();
		Anirender->CreateAnimation(L"Base", L"battletankbutton.png", 0, 0, false);
		Anirender->CreateAnimation(L"On", L"battletankbutton.png", 1, 1, false);
		Anirender->CreateAnimation(L"Click", L"battletankbutton.png", 2, 2, false);

		//Anirender->ChangeAnimation(L"On");

		My_Ptr<FontRenderer> font = hatchGoopy->AddComponent<FontRenderer>(RG_PLAYER);
		font->SetLocalPosition({ 0.0f, 0.2f,0.0f });
		font->SetFont(L"Silkscreen");
		std::wstring text;
		text += L"CHALLENGE";

		font->SetText(text, 20.0f, { 253.0f / 255.0f, 238.0f / 255.0f , 0.0f });
	}

	{
		My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");

		hatchGoopy->GetTransform()->SetLocalPosition({ 1.45f, -0.8f, -10.0f });
		hatchGoopy->GetTransform()->SetLocalScale({ 217.0f / GameWindow::Inst()->GetWindowSize().y , 66.0f / GameWindow::Inst()->GetWindowSize().x * 1.35f });
		//hatchGoopy->GetTransform()->SetLocalScale({ 1.0f , 3.0f});
		hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);
		//hatchGoopy->GetTransform()->SetLocalScale(1.2f);
		//hatchGoopy->GetTransform()->SetLocalScale({1.0f, 1.0f, 1.0f});

		My_Ptr<BoundingBox> collider = hatchGoopy->AddComponent<BoundingBox>(CG_ADVENTURE);

		collider->RegisterEnterFunction(&TitleUpdater::Enter, this);
		collider->RegisterStayFunction(&TitleUpdater::Stay, this);
		collider->RegisterExitFunction(&TitleUpdater::Exit, this);

		My_Ptr<SpriteRenderer> render = hatchGoopy->AddComponent<SpriteRenderer>(RG_PLAYER);
		render->SetSprite(L"middlebutton.png");
		My_Ptr<SpriteAnimation> Anirender = hatchGoopy->AddComponent<SpriteAnimation>();
		Anirender->CreateAnimation(L"Base", L"middlebutton.png", 0, 0, false);
		Anirender->CreateAnimation(L"On", L"middlebutton.png", 1, 1, false);
		Anirender->CreateAnimation(L"Click", L"middlebutton.png", 2, 2, false);

		//Anirender->ChangeAnimation(L"On");

		My_Ptr<FontRenderer> font = hatchGoopy->AddComponent<FontRenderer>(RG_PLAYER);
		font->SetLocalPosition({ 0.0f, 0.2f,0.0f });
		font->SetFont(L"Silkscreen");
		std::wstring text;
		text += L"VIRTUAL TANK";

		font->SetText(text, 22.0f, { 253.0f / 255.0f, 238.0f / 255.0f , 0.0f });
	}

	{
		My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");

		hatchGoopy->GetTransform()->SetLocalPosition({-2.0f, 1.5f, -10.0f });
		hatchGoopy->GetTransform()->SetLocalScale({ 207.0f / GameWindow::Inst()->GetWindowSize().y , 114.0f / GameWindow::Inst()->GetWindowSize().x * 1.2f  });
		//hatchGoopy->GetTransform()->SetLocalScale({ 1.0f , 3.0f});
		hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y/ 100.0f);
		//hatchGoopy->GetTransform()->SetLocalScale(1.2f);
		//hatchGoopy->GetTransform()->SetLocalScale({1.0f, 1.0f, 1.0f});


		My_Ptr<SpriteRenderer> render = hatchGoopy->AddComponent<SpriteRenderer>(RG_PLAYER);
		render->SetSprite(L"speechbubble.png");
		//My_Ptr<SpriteAnimation> Anirender = hatchGoopy->AddComponent<SpriteAnimation>();
		//Anirender->CreateAnimation(L"Base", L"middlebutton.png", 0, 0, false);
		//Anirender->CreateAnimation(L"On", L"middlebutton.png", 1, 1, false);
		//Anirender->CreateAnimation(L"Click", L"middlebutton.png", 2, 2, false);

		//Anirender->ChangeAnimation(L"On");

		My_Ptr<FontRenderer> font = hatchGoopy->AddComponent<FontRenderer>(RG_PLAYER);
		font->SetLocalPosition({ 0.0f, 0.37f,0.0f });
		font->SetFont(L"Silkscreen");
		std::wstring text;
		text += L"WELCOME TO \nINSANIAQUARIUM";

		font->SetText(text, 20.0f, { 51.0f / 255.0f, 0.0f , 1.0f });
	}



	{
		My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");

		hatchGoopy->GetTransform()->SetLocalPosition({ 1.45f, -1.55f, -10.0f });
		hatchGoopy->GetTransform()->SetLocalScale({ 217.0f / GameWindow::Inst()->GetWindowSize().y , 66.0f / GameWindow::Inst()->GetWindowSize().x * 1.1f });
		//hatchGoopy->GetTransform()->SetLocalScale({ 1.0f , 3.0f});
		hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);
		//hatchGoopy->GetTransform()->SetLocalScale(1.2f);
		//hatchGoopy->GetTransform()->SetLocalScale({1.0f, 1.0f, 1.0f});

		//hatchGoopy->AddComponent<BoundingBox>(CG_UI);

		//My_Ptr<SpriteRenderer> render = hatchGoopy->AddComponent<SpriteRenderer>(RG_PLAYER);
		//render->SetSprite(L"battletankbutton.png");
		//My_Ptr<SpriteAnimation> Anirender = hatchGoopy->AddComponent<SpriteAnimation>();
		//Anirender->CreateAnimation(L"Base", L"battletankbutton.png", 0, 0, false);
		//Anirender->CreateAnimation(L"On", L"battletankbutton.png", 1, 1, false);
		//Anirender->CreateAnimation(L"Click", L"battletankbutton.png", 2, 2, false);

		//Anirender->ChangeAnimation(L"On");

		My_Ptr<FontRenderer> font = hatchGoopy->AddComponent<FontRenderer>(RG_PLAYER);
		font->SetLocalPosition({ 0.0f, 0.2f,0.0f });
		font->SetFont(L"Silkscreen");
		std::wstring text;
		text += L"HALL OF FAME";

		font->SetText(text, 13.0f, { 253.0f / 255.0f, 238.0f / 255.0f , 0.0f });
	}
	{
		My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");

		hatchGoopy->GetTransform()->SetLocalPosition({ 1.45f, -1.9f, -10.0f });
		hatchGoopy->GetTransform()->SetLocalScale({ 217.0f / GameWindow::Inst()->GetWindowSize().y , 66.0f / GameWindow::Inst()->GetWindowSize().x * 1.1f });
		//hatchGoopy->GetTransform()->SetLocalScale({ 1.0f , 3.0f});
		hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);
		//hatchGoopy->GetTransform()->SetLocalScale(1.2f);
		//hatchGoopy->GetTransform()->SetLocalScale({1.0f, 1.0f, 1.0f});

		//hatchGoopy->AddComponent<BoundingBox>(CG_UI);

		//My_Ptr<SpriteRenderer> render = hatchGoopy->AddComponent<SpriteRenderer>(RG_PLAYER);
		//render->SetSprite(L"battletankbutton.png");
		//My_Ptr<SpriteAnimation> Anirender = hatchGoopy->AddComponent<SpriteAnimation>();
		//Anirender->CreateAnimation(L"Base", L"battletankbutton.png", 0, 0, false);
		//Anirender->CreateAnimation(L"On", L"battletankbutton.png", 1, 1, false);
		//Anirender->CreateAnimation(L"Click", L"battletankbutton.png", 2, 2, false);

		//Anirender->ChangeAnimation(L"On");

		My_Ptr<FontRenderer> font = hatchGoopy->AddComponent<FontRenderer>(RG_PLAYER);
		font->SetLocalPosition({ 0.0f, 0.2f,0.0f });
		font->SetFont(L"Silkscreen");
		std::wstring text;
		text += L"HELP";

		font->SetText(text, 13.0f, { 253.0f / 255.0f, 238.0f / 255.0f , 0.0f });
	}
	{
		My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");

		hatchGoopy->GetTransform()->SetLocalPosition({ 2.35f, -1.9f, -10.0f });
		hatchGoopy->GetTransform()->SetLocalScale({ 217.0f / GameWindow::Inst()->GetWindowSize().y , 66.0f / GameWindow::Inst()->GetWindowSize().x * 1.1f });
		//hatchGoopy->GetTransform()->SetLocalScale({ 1.0f , 3.0f});
		hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);
		//hatchGoopy->GetTransform()->SetLocalScale(1.2f);
		//hatchGoopy->GetTransform()->SetLocalScale({1.0f, 1.0f, 1.0f});

		//hatchGoopy->AddComponent<BoundingBox>(CG_UI);

		//My_Ptr<SpriteRenderer> render = hatchGoopy->AddComponent<SpriteRenderer>(RG_PLAYER);
		//render->SetSprite(L"battletankbutton.png");
		//My_Ptr<SpriteAnimation> Anirender = hatchGoopy->AddComponent<SpriteAnimation>();
		//Anirender->CreateAnimation(L"Base", L"battletankbutton.png", 0, 0, false);
		//Anirender->CreateAnimation(L"On", L"battletankbutton.png", 1, 1, false);
		//Anirender->CreateAnimation(L"Click", L"battletankbutton.png", 2, 2, false);

		//Anirender->ChangeAnimation(L"On");


		
		My_Ptr<FontRenderer> font = hatchGoopy->AddComponent<FontRenderer>(RG_PLAYER);
		font->SetLocalPosition({ 0.0f, 0.2f,0.0f });
		font->SetFont(L"Silkscreen");
		std::wstring text;
		text += L"QUIT";

		font->SetText(text, 13.0f, { 253.0f / 255.0f, 238.0f / 255.0f , 0.0f });
	}

	{
		My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");

		hatchGoopy->GetTransform()->SetLocalPosition({ 0.55f, -1.9f, -10.0f });
		hatchGoopy->GetTransform()->SetLocalScale({ 217.0f / GameWindow::Inst()->GetWindowSize().y , 66.0f / GameWindow::Inst()->GetWindowSize().x * 1.1f });
		//hatchGoopy->GetTransform()->SetLocalScale({ 1.0f , 3.0f});
		hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);
		//hatchGoopy->GetTransform()->SetLocalScale(1.2f);
		//hatchGoopy->GetTransform()->SetLocalScale({1.0f, 1.0f, 1.0f});

		//hatchGoopy->AddComponent<BoundingBox>(CG_UI);

		//My_Ptr<SpriteRenderer> render = hatchGoopy->AddComponent<SpriteRenderer>(RG_PLAYER);
		//render->SetSprite(L"battletankbutton.png");
		//My_Ptr<SpriteAnimation> Anirender = hatchGoopy->AddComponent<SpriteAnimation>();
		//Anirender->CreateAnimation(L"Base", L"battletankbutton.png", 0, 0, false);
		//Anirender->CreateAnimation(L"On", L"battletankbutton.png", 1, 1, false);
		//Anirender->CreateAnimation(L"Click", L"battletankbutton.png", 2, 2, false);

		//Anirender->ChangeAnimation(L"On");

		My_Ptr<FontRenderer> font = hatchGoopy->AddComponent<FontRenderer>(RG_PLAYER);
		font->SetLocalPosition({ 0.0f, 0.2f,0.0f });
		font->SetFont(L"Silkscreen");
		std::wstring text;
		text += L"OPTION";

		font->SetText(text, 13.0f, { 253.0f / 255.0f, 238.0f / 255.0f , 0.0f });
	}

	//hatchGoopy->AddComponent<CreditMove>();
}

void TitleUpdater::SceneUpdate()
{
	Mouse::Inst().Update();
}


void TitleUpdater::Enter(Collider* _This, Collider* _Other)
{
	int a = 0;
}

void TitleUpdater::Stay(Collider* _This, Collider* _Other)
{
	SpriteAnimation* ani = _This->GetActor()->GetComponent<SpriteAnimation>();
	ani->ChangeAnimation(L"On");

	if (Input::Down(L"MOUSELEFT"))
	{
		Sound::Stop(L"LoadingBgm");
		GameWindow::Inst()->ChangeScene(L"AdventureScene");
		Sound::Play(L"AdventureBgm", L"BG Tank 1.wav", 100000);
	}

}

void TitleUpdater::Exit(Collider* _This, Collider* _Other)
{
	SpriteAnimation* ani = _This->GetActor()->GetComponent<SpriteAnimation>();
	ani->ChangeAnimation(L"Base");
}