#include "TestUpdater.h"

#include <Input.h>
#include <GameWindow.h>
#include <GraphicDebug.h>

#include <Camera.h>
#include <SpriteRenderer.h>
#include <Texture.h>
#include <Sprite.h>
#include <SpriteAnimation.h>
#include <RectRenderer.h>
#include <BoundingBox.h>
#include <BoundingSphere.h>

#include <MoveLogic.h>

#include "ENUM.h"
#include "BackGround.h"


void ColPrint(Collider* _This, Collider* _Other)
{
	std::cout << "충돌했습니다." << std::endl;
}

class Test 
{
private:
	int HP = 1000000;

public:
	void Enter(Collider* _This, Collider* _Other)
	{
		//GameWindow::MainGameWindow()->ChangeScene(L"EndingScene");
		std::cout << "씬변경." << std::endl;
		std::cout << "충돌했습니다." << std::endl;
		_Other->GetActor()->Die();
	}

	void Stay(Collider* _This, Collider* _Other)
	{
		--HP;
		std::cout << "충돌 중입니다." << HP << std::endl;
	}


	void Exit(Collider* _This, Collider* _Other)
	{
		std::cout << "충돌 끝났습니다." << std::endl;
	}
};


TestUpdater::TestUpdater()
{
}


TestUpdater::~TestUpdater()
{
}


void TestUpdater::Loading()
{
	GraphicDebug::DebugON();
	////////////////// 리소스 로드
	//HPATH::CreatePath(L"TEX");

	//HRES::Load<HTEX>(HPATH::PlusPath(L"TEX", L"TEST.png"));
	//HRES::Create<HESPRITE>(L"TEST.png", L"TEST.png", 12, 5, 0, 20);

	////////////////// 키입력 이닛

	Input::CreateKey(L"LEFT", VK_LEFT);
	Input::CreateKey(L"RIGHT", VK_RIGHT);
	Input::CreateKey(L"UP", VK_UP);
	Input::CreateKey(L"DOWN", VK_DOWN);
	Input::CreateKey(L"ZPROT", 'Q');
	Input::CreateKey(L"ZMROT", 'W');

	////////////////// 콜리전 그룹 설정
	




	Path::CreatePath(L"TestScene", L"Texture\\TestScene");


	Resources::Load<Texture>(Path::JoinPath(L"TestScene", L"TEST.png"));
	Resources::Create<Sprite>(L"TEST.png", L"TEST.png", 1, 1, 0, 1);


	//CAMERA
	My_Ptr<Actor> mainCam = GetScene()->CreateActor(L"TESTCAM");
	mainCam->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, -100.0f });
	My_Ptr<Camera> camera = mainCam->AddComponent<Camera>(RENDERGROUP::RG_PLAYER);
	camera->SetProjMode(PROJMODE::ORTHOGONAL);
	camera->SetArea( (8.0f * 10.0f / 6.0f) ,  10.0f );
	//camera->SetArea(Window::MainWindow()->GetWindowSize().x / 100.0f, Window::MainWindow()->GetWindowSize().y / 100.0f);


	GetScene()->colliderMgr.Link(COLGROUP::CG_LITTLEGOOPY, COLGROUP::CG_MONSTER);
	GetScene()->colliderMgr.Link(COLGROUP::CG_LITTLEGOOPY, COLGROUP::CG_LITTLEGOOPY);

	{	//MAIN OBJECT
		My_Ptr<Actor> MAINRECT = GetScene()->CreateActor(L"MainRect");
		MAINRECT->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, 0.0f });
		MAINRECT->GetTransform()->LocalScaleMultiple(1.0f);
		MAINRECT->OverScene(L"TestScene", L"EndingScene");


		My_Ptr<RectRenderer> Render = MAINRECT->AddComponent<RectRenderer>(RENDERGROUP::RG_PLAYER);
		Render->SetColor({ 1.0f, 0.0f, 0.0f, 1.0f });
		MAINRECT->AddComponent<MoveLogic>();
		


		My_Ptr<RectRenderer> Render2 = MAINRECT->AddComponent<RectRenderer>(RENDERGROUP::RG_PLAYER);
		Render2->SetColor({ 1.0f, 1.0f, 0.0f, 1.0f });
		Render2->SetLocalPosition({0.0f, 3.0f, 0.0f});



		My_Ptr<BoundingBox> MainRectCollider = MAINRECT->AddComponent<BoundingBox>(COLGROUP::CG_LITTLEGOOPY);
		MainRectCollider->RegisterEnterFunction(ColPrint);




		My_Ptr<Actor> child= GetScene()->CreateActor();
		child->GetTransform()->SetLocalPosition({ 0.0f, -3.0f, 0.0f });
		child->GetTransform()->LocalScaleMultiple(1.0f);
		child->SetParent(MAINRECT);
		//child->OverScene(L"TestScene", L"EndingScene");
		My_Ptr<RectRenderer> childRender = child->AddComponent<RectRenderer>(RENDERGROUP::RG_PLAYER);
		childRender->SetColor({ 1.0f, 0.0f, 1.0f, 1.0f });
		My_Ptr<BoundingSphere> childRectCollider = child->AddComponent<BoundingSphere>(COLGROUP::CG_LITTLEGOOPY);


		Test NewTest;// = new Test();


		//MAINOBJ->AddCom<MOVESCRIPT>();
		//HPTR< H2DSPHERECOL> PTR = MAINOBJ->AddCom<H2DSPHERECOL>(CG_PLAYER);
		MainRectCollider->RegisterEnterFunction(&Test::Enter, &NewTest);
		MainRectCollider->RegisterStayFunction(&Test::Stay, &NewTest);
		MainRectCollider->RegisterExitFunction(&Test::Exit, &NewTest);
	}
	/*{
		My_Ptr<Actor> RightRect = GetScene()->CreateActor();
		RightRect->GetTransform()->SetPos({ 2.0f, 0.0f, 0.0f });
		RightRect->GetTransform()->MultipleScale(1.0f);

		My_Ptr<RectRenderer> Render = RightRect->AddComponent<RectRenderer>(RG_PLAYER);
		Render->SetColor({ 0.0f, 0.0f, 1.0f, 1.0f });

		My_Ptr<ObjectBoundingBox> RightRectCollider = RightRect->AddComponent<ObjectBoundingBox>(CG_MONSTER);
	}
	{
		My_Ptr<Actor> RightRect = GetScene()->CreateActor();
		RightRect->GetTransform()->SetPos({ -1.0f, 0.0f, 0.0f });
		RightRect->GetTransform()->MultipleScale(1.0f);

		My_Ptr<RectRenderer> Render = RightRect->AddComponent<RectRenderer>(RG_PLAYER);
		Render->SetColor({ 1.0f, 0.0f, 0.0f, 1.0f });

		My_Ptr<ObjectBoundingBox> RightRectCollider = RightRect->AddComponent<ObjectBoundingBox>(CG_PLAYER);
	}
	{
		My_Ptr<Actor> RightRect = GetScene()->CreateActor();
		RightRect->GetTransform()->SetPos({ 0.0f, 2.0f, 0.0f });
		RightRect->GetTransform()->MultipleScale(1.0f);

		My_Ptr<RectRenderer> Render = RightRect->AddComponent<RectRenderer>(RG_PLAYER);
		Render->SetColor({ 0.0f, 0.0f, 1.0f, 1.0f });

		My_Ptr<ObjectBoundingBox> RightRectCollider = RightRect->AddComponent<ObjectBoundingBox>(CG_MONSTER);
	}
	{
		My_Ptr<Actor> RightRect = GetScene()->CreateActor();
		RightRect->GetTransform()->SetPos({ -2.0f, 0.0f, 0.0f });
		RightRect->GetTransform()->MultipleScale(1.0f);

		My_Ptr<RectRenderer> Render = RightRect->AddComponent<RectRenderer>(RG_PLAYER);
		Render->SetColor({ 0.0f, 0.0f, 1.0f, 1.0f });

		My_Ptr<ObjectBoundingBox> RightRectCollider = RightRect->AddComponent<ObjectBoundingBox>(CG_MONSTER);
	}*/
	//My_Ptr<Actor> selectBack = GetScene()->CreateActor();
	//selectBack->GetTransform()->SetPos({ 0.0f, 0.0f, 1.0f });
	//selectBack->GetTransform()->SetScale({ 640.0f / 480.0f , 480.0f / 480.0f });
	//selectBack->GetTransform()->ScaleMul(4.8f);
	//My_Ptr<SpriteRenderer> selectBackRender = selectBack->AddComponent<SpriteRenderer>(RG_PLAYER);
	//selectBackRender->SetSprite(L"TEST.png");

	//BackGround backGround = BackGround(GetScene(), L"selectorback.jpg");


	
}

void TestUpdater::SceneUpdate()
{
	GraphicDebug::DrawFontUI(L"하하하", Vector4::RED);
}

void TestUpdater::ChangeStart()
{

}

void TestUpdater::ChangeEnd()
{

}