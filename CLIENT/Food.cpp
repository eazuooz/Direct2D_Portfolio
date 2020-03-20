#include "Food.h"

#include <GameWindow.h>
#include <ENUM.h>
#include <FoodList.h>

#include <Sound.h>

int Food::foodCount = 0;
int Food::maximumFoodCount = 1;
int Food::foodLevel	= 0;

SpriteAnimation*	Food::spriteAnimation = nullptr;

Food::Food(My_Ptr<Scene> _Scene, Vector4 _Pos) 
{
	++foodCount;
	if (foodCount > maximumFoodCount)
	{
		return;
	}

	scene	= _Scene;
	pos		= _Pos;



	Init();
	CreateSprite();
	Sound::Play(L"DROPFOOD.wav");
}


Food::~Food()
{
}



void Food::Init()
{
	actor = scene->CreateActor(L"food");
	actor->GetTransform()->SetLocalScale({ 40.0f / GameWindow::Inst()->GetWindowSize().y , 40.0f / GameWindow::Inst()->GetWindowSize().y });
	actor->GetTransform()->LocalScaleMultiple(GameWindow::Inst()->GetWindowSize().y / 100.0f);
	actor->GetTransform()->SetLocalPosition(pos);
	FoodList::PushFood(actor);


	spriteRenderer = actor->AddComponent<SpriteRenderer>(RENDERGROUP::RG_FOOD);
	spriteRenderer->SetSprite(L"food.png");

	spriteAnimation = actor->AddComponent<SpriteAnimation>();

	collider = actor->AddComponent<BoundingSphere>(COLGROUP::CG_FOOD);
	collider->MultipleRadius(0.5f);

	foodMove = actor->AddComponent<FoodMove>();


	if (actor == nullptr)
	{
		BOOM;
	}
	


	FoodMove::PushFoodActor(collider);
	//DataManager::PushFoodActor(actor);
}

void Food::CreateSprite()
{
	spriteAnimation->CreateAnimation(L"Level1", L"food.png", 0, 9, 0.1f, true);
	spriteAnimation->CreateAnimation(L"Level2", L"food.png", 10, 19, 0.1f, true);
	spriteAnimation->CreateAnimation(L"Level3", L"food.png", 20, 29, 0.1f, true);
	spriteAnimation->CreateAnimation(L"Level4", L"food.png", 30, 39, 0.1f, true);
	spriteAnimation->CreateAnimation(L"Level5", L"food.png", 40, 49, 0.1f, true);
	switch (foodLevel)
	{
	case 0:
	{
		FoodMove::SetFoodPoint(5);
		spriteAnimation->ChangeAnimation(L"Level1");


	}
	break;
	case 1:
	{
		FoodMove::SetFoodPoint(10);
		spriteAnimation->ChangeAnimation(L"Level2");

	}
	break;
	case 2:
	{
		FoodMove::SetFoodPoint(20);
		spriteAnimation->ChangeAnimation(L"Level3");

	}
	break;
	case 3:
	{
		spriteAnimation->ChangeAnimation(L"Level4");

	}
	break;
	case 4:
	{
		spriteAnimation->ChangeAnimation(L"Level5");

	}
	break;
	}
}


