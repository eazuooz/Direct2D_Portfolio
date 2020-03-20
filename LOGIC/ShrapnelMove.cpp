#include "ShrapnelMove.h"

#include "CoinMove.h"

ShrapnelMove::ShrapnelMove() : bombTime(5.0f)
{

}


ShrapnelMove::~ShrapnelMove()
{

}


void ShrapnelMove::Init()
{
	InitResource();
}

void ShrapnelMove::Update()
{
	bombTime -= Time::DeltaTime();

	if (bombTime < 0.0f)
	{
		My_Ptr<Actor> foodActor = GetActor()->GetScene()->CreateActor(L"Bomb");
		foodActor->GetTransform()->SetLocalPosition(pos);
		foodActor->GetTransform()->SetLocalScale({ 40.0f / GameWindow::Inst()->GetWindowSize().y , 40.0f / GameWindow::Inst()->GetWindowSize().y });
		foodActor->GetTransform()->LocalScaleMultiple(GameWindow::Inst()->GetWindowSize().y / 100.0f);
		foodActor->GetTransform()->LocalScaleMultiple(2.0f);
		My_Ptr<SpriteRenderer> monsterRender = foodActor->AddComponent<SpriteRenderer>(RENDERGROUP::RG_COIN);

		monsterRender->SetSprite(L"items.png");
		My_Ptr<SpriteAnimation> monsterAni = foodActor->AddComponent<SpriteAnimation>();


		monsterAni->CreateAnimation(L"Bomb", L"items.png", 2, 2, 0.1f, false);


		My_Ptr<BoundingSphere> monsterCollider = foodActor->AddComponent<BoundingSphere>(CG_COIN);
		monsterCollider->MultipleRadius(0.5f);

		CoinMove* logic =  foodActor->AddComponent<CoinMove>();
		logic->BombOn();
	

		bombTime = 5.0f;
	}

	pos = GetActor()->GetTransform()->GetLocalPosition();
	if (direction.x < 0.0f)
	{
		DIR = DIRECTION::LEFT;
	}
	else if (direction.x > 0.0f)
	{
		DIR = DIRECTION::RIGHT;
	}
	else //0.0f 일때는 그냥 그대로
	{
		//
	}

	switch (state)
	{
	case STATE::MOVING:
	{
		InterMoving();
	}
	break;
	case STATE::STOP:
	{
		Stop();
	}
	break;
	case STATE::SKILL:
	{

	}
	break;
	}
}