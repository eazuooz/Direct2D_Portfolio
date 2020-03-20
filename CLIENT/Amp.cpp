#include "Amp.h"


#include <AmpMove.h>
#include <ENUM.h>
#include <BoundingBox.h>

Amp::Amp(My_Ptr<Scene> _Scene, const wchar_t* _TextureName, Vector4 _CntInfo) : Pet(_Scene, _TextureName, _CntInfo)
{
	CreateAnimation();
	AddComponent();
}


Amp::~Amp()
{
}

void Amp::CreateAnimation()
{
	//std::wstring createAniName;
	//createAniName = fishName + L"Skill";
	//spriteAnimation->CreateAnimation(createAniName.c_str(), spriteName.c_str(), 20, 29, 0.1f, false);
}

void Amp::AddComponent()
{
	Vector4 POS = GetActor()->GetTransform()->GetLocalPosition();
	POS.z = __FOOD;
	GetActor()->GetTransform()->SetLocalPosition(POS);

	EffectSpriteRenderer* halo = GetActor()->AddComponent<EffectSpriteRenderer>(RG_MONSTER);
	halo->SetSprite(L"ampcharge.png");
	halo->SetBlender(L"BLEND1TO1");

	
	Vector4 scale = { 1.0f,1.0f,1.0f };
	halo->SetLocalScale(scale);
	Vector4 temp = GetActor()->GetTransform()->GetLocalPosition();

	halo->GetTransform()->SetLocalPosition({0.0f, 0.0f, 0.0f});

	My_Ptr<SpriteAnimation> WaveAni = GetActor()->GetComponent<SpriteAnimation>();
	WaveAni->SetEffectSprite(halo);

	WaveAni->CreateAnimation(L"EffectSwim", L"ampcharge.png", 0, 9, 0.1f, true);
	WaveAni->CreateAnimation(L"EffectTurn", L"ampcharge.png", 10, 19, 0.1f, true);
	WaveAni->CreateAnimation(L"EffectSwimfast", L"ampcharge.png", 0, 9, 0.07f, true);
	WaveAni->CreateAnimation(L"EffectTurnfast", L"ampcharge.png", 10, 19, 0.07f, true);


	GetActor()->AddComponent<BoundingBox>(CG_AMP);
	moveLogic = actor->AddComponent<AmpMove>();
}