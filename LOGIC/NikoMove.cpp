#include "NikoMove.h"
#include <GameWindow.h>
#include <Scene.h>
#include "ENUM.h"

#include "CoinMove.h"
#include <Sound.h>

NikoMove::NikoMove() : state(IDLE), openTime(NIKOCREATETIME), isCreate(false)
{
}


NikoMove::~NikoMove()
{
}

void NikoMove::Init()
{
	spriteRenderer = GetActor()->GetComponent<SpriteRenderer>();
	spriteAnimaion = GetActor()->GetComponent<SpriteAnimation>();	

	curAniName = spriteAnimaion->GetCurAni()->curAnimationName;

	fishName = L"niko";
}

void NikoMove::Update()
{
	openTime -= Time::DeltaTime();



	switch (state)
	{
	case NikoMove::IDLE:
		{
			Idle();
		}
		break;
	case NikoMove::OPEN:
		{
			Open();
		}
		break;
	case NikoMove::CLOSE:
		{
			Close();
		}
		break;
	}
}

void NikoMove::Idle()
{
	std::wstring aniName = fishName + L"Swim";
	spriteAnimaion->ChangeAnimation(aniName.c_str());

	if (openTime < 0.0f)
	{

		state = NikoMove::OPEN;
	}
}
void NikoMove::Open()
{
	std::wstring aniName = fishName + L"Turn";
	spriteAnimaion->ChangeAnimation(aniName.c_str());

	if (isCreate == true)
	{
		Vector4 pearlPos = pearl->GetTransform()->GetLocalPosition();

		if (pearlPos.x != -1.85f || pearlPos.y != -0.55f)
		{
			Sound::Play(L"nikoclose.wav");
			state = NIKO::CLOSE;
			openTime = NIKOCREATETIME;
		}

	}
	

	if (spriteAnimaion->GetCurAni()->aniEnd == true && isCreate == false)
	{
		Sound::Play(L"nikoopen.wav");

		pearl = GetActor()->GetScene()->CreateActor(L"Pearl");
		pearl->GetTransform()->SetLocalPosition({ -1.85f, -0.55f, 80.0f });
		pearl->GetTransform()->SetLocalScale({ 72.0f / GameWindow::Inst()->GetWindowSize().y , 72.0f / GameWindow::Inst()->GetWindowSize().y });
		pearl->GetTransform()->LocalScaleMultiple(GameWindow::Inst()->GetWindowSize().y / 100.0f);

		My_Ptr<SpriteRenderer> pearlRender = pearl->AddComponent<SpriteRenderer>(RENDERGROUP::RG_PET);
		pearlRender->SetSprite(L"pearl.png");
	
		My_Ptr<BoundingSphere> pearlCollider = pearl->AddComponent<BoundingSphere>(CG_COIN);
		pearlCollider->MultipleRadius(0.5f);

		My_Ptr<CoinMove> logic = pearl->AddComponent<CoinMove>();
		logic->Stop();

		isCreate = true;
	}


}
void NikoMove::Close()
{
	std::wstring aniName = fishName + L"Skill";
	spriteAnimaion->ChangeAnimation(aniName.c_str());

	if (spriteAnimaion->GetCurAni()->aniEnd == true && isCreate == true)
	{
		isCreate = false;
		state = NIKO::IDLE;		
	}
}
