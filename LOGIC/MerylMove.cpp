#include "MerylMove.h"


#include "CreateCoin.h"
#include "NoteMove.h"
#include <Sound.h>

MerylMove::MerylMove() : singTime(20.0f)
{
}


MerylMove::~MerylMove()
{
}

void MerylMove::Init()
{
	InitResource();
}

void MerylMove::Update()
{
	singTime -= Time::DeltaTime();

	if (singTime < 0.0f)
	{



		state = STATE::SKILL;
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
			CreateCoin::MakeCoinOff();
		}
		break;
		case STATE::SKILL:
		{
			Skill();
		}
		break;
	}
}

void MerylMove::Skill()
{
	if (spriteAnimaion->GetCurAni()->aniEnd == true)
	{
		Sound::Play(L"sing.wav");
		Sound::Play(L"merylAppear.wav");

		CreateCoin::MakeCoin();
		singTime = 20.0f;
		state = STATE::STOP;

		My_Ptr<Actor> note = GetActor()->GetScene()->CreateActor(L"Note");

		note->GetTransform()->SetLocalPosition(pos);
		note->GetTransform()->SetLocalScale({ 72.0f / GameWindow::Inst()->GetWindowSize().y , 72.0f / GameWindow::Inst()->GetWindowSize().y });
		note->GetTransform()->LocalScaleMultiple(GameWindow::Inst()->GetWindowSize().y / 100.0f);
		My_Ptr<SpriteRenderer> monsterRender = note->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
		//Render->SetBlendOption();
		monsterRender->SetSprite(L"items.png");
		My_Ptr<SpriteAnimation> monsterAni = note->AddComponent<SpriteAnimation>();
		monsterAni->CreateAnimation(L"Note", L"items.png", 1, 1, 0.1f, true);
		note->AddComponent<NoteMove>();
	}

	spriteAnimaion->ChangeAnimation(L"merylSkill");

	Move(moveSpeed);
}
