#include "Mouse.h"
#include <set>
#include <Input.h>

#include <GameWindow.h>
#include <Collider.h>
#include <BoundingSphere.h>

#include "ENUM.h"


Mouse* Mouse::inst = nullptr;
Mouse::Mouse() : scene(nullptr), actor(nullptr), collider(nullptr), pos(1.0f)
{

}


Mouse::~Mouse()
{
	int a = 0;
}

void Mouse::Init()
{
	if (actor != nullptr)	//이미 만들어져 있는 액터라면 만들지않는다
	{
		return;
	}

	actor = scene->CreateActor(L"Mouse");	
	
	std::set<std::wstring>::iterator begin	= GameWindow::Inst()->sceneNameSet.begin();
	std::set<std::wstring>::iterator end	= GameWindow::Inst()->sceneNameSet.end();

	for (; begin != end; ++begin)	//모든씬으로의 이동이 가능하다
	{
		actor->OverScene(begin->c_str());
	}

	actor->GetTransform()->SetLocalPosition({0.0f, 0.0f, -99.0f});
	//actor->GetTransform()->SetLocalScale({ 0.2f, 0.2f, 1.0f });

	actor->GetTransform()->SetLocalScale({ 182.0f / GameWindow::Inst()->GetWindowSize().x , 206.0f / GameWindow::Inst()->GetWindowSize().y });
	actor->GetTransform()->LocalScaleMultiple(GameWindow::Inst()->GetWindowSize().y / 100.0f);
	actor->GetTransform()->LocalScaleMultiple(0.5f);
	//actor->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);

	collider = actor->AddComponent<BoundingSphere>(COLGROUP::CG_MOUSE);
	collider->MultipleRadius(0.2f);


	collider->RegisterEnterFunction	(&Mouse::Enter, this);
	collider->RegisterStayFunction	(&Mouse::Stay, this);
	collider->RegisterExitFunction	(&Mouse::Exit, this);

	

	spriteRender = actor->AddComponent<SpriteRenderer>(RG_UI);
	spriteRender->SetSprite(L"GunShoot.png");
	spriteAnimaion = actor->AddComponent<SpriteAnimation>();
	spriteAnimaion->CreateAnimation(L"None", L"GunShoot.png",	15, 15, 0.04f, true);
	spriteAnimaion->CreateAnimation(L"GunShoot", L"GunShoot.png",	0, 15, 0.02f, false);
	spriteAnimaion->CreateAnimation(L"GunShoot1", L"GunShoot1.png", 0, 15, 0.02f, false);
	spriteAnimaion->CreateAnimation(L"GunShoot2", L"GunShoot2.png", 0, 15, 0.02f, false);
	spriteAnimaion->CreateAnimation(L"GunShoot3", L"GunShoot3.png", 0, 15, 0.02f, false);
	spriteAnimaion->CreateAnimation(L"GunShoot4", L"GunShoot4.png", 0, 15, 0.02f, false);
	spriteAnimaion->CreateAnimation(L"GunShoot5", L"GunShoot5.png", 0, 15, 0.02f, false);
	spriteAnimaion->CreateAnimation(L"GunShoot6", L"GunShoot6.png", 0, 15, 0.02f, false);
	spriteAnimaion->CreateAnimation(L"GunShoot7", L"GunShoot7.png", 0, 15, 0.02f, false);
	spriteAnimaion->CreateAnimation(L"GunShoot8", L"GunShoot8.png", 0, 15, 0.02f, false);
		
	aniName = L"GunShoot";
}


void Mouse::Update()
{
	Vector4 windowPos;
	windowPos = GameWindow::Inst()->MousePos();
	
	//if (windowPos.x < 0.0f || GameWindow::Inst()->GetWindowSize().x > windowPos.x)
	//{
	//	return;
	//}
	//if (windowPos.y < 0.0f || GameWindow::Inst()->GetWindowSize().y > windowPos.y)
	//{
	//	return;
	//}

	windowPos.x =  -((GameWindow::Inst()->GetWindowSize().x / 2.0f) - windowPos.x);
	windowPos.y =	((GameWindow::Inst()->GetWindowSize().y / 2.0f) - windowPos.y);
	windowPos /= 100.0f;
	windowPos.z = -5.0f;

	pos = windowPos;

	
	actor->GetTransform()->SetLocalPosition(pos);

	if (spriteAnimaion->GetCurAni()->aniEnd == true)
	{
		spriteAnimaion->ChangeAnimation(L"None");
	}

}

///COL
void Mouse::Enter(Collider* _This, Collider* _Other)
{

}

void Mouse::Stay(Collider* _This, Collider* _Other)
{
	if (Input::Down(L"MOUSELEFT") == true)
	{
		aniName += L"";

		spriteAnimaion->ChangeAnimation(aniName.c_str());
	}
}

void Mouse::Exit(Collider* _This, Collider* _Other)
{
	int a = 0;
}
///

void Mouse::Destroy()
{
	if (nullptr != inst)
	{
		delete inst;
		inst = nullptr;
	}
}