#include "Angie.h"

#include <ENUM.h>
#include <EffectSpriteRenderer.h>

Angie::Angie(My_Ptr<Scene> _Scene, const wchar_t* _TextureName, Vector4 _CntInfo) : Pet(_Scene, _TextureName, _CntInfo)
{
	CreateAnimation();
	AddComponent();
}


Angie::~Angie()
{
}

void Angie::CreateAnimation()
{
	//std::wstring createAniName;
	//createAniName = fishName + L"Skill";
	//spriteAnimation->CreateAnimation(createAniName.c_str(), spriteName.c_str(), 20, 29, 0.1f, false);
}

void Angie::AddComponent()
{
	//SpriteRenderer

	Vector4 POS = GetActor()->GetTransform()->GetLocalPosition();
	POS.z = __FOOD;
	GetActor()->GetTransform()->SetLocalPosition(POS);

	EffectSpriteRenderer* halo = GetActor()->AddComponent<EffectSpriteRenderer>(RG_MONSTER);
	//SpriteRenderer* halo = GetActor()->AddComponent<SpriteRenderer>(RG_PET);
	halo->SetSprite(L"halo.png");
	halo->SetBlender(L"BLEND1TO1");

	halo->SetLocalPosition({0.0f, 0.1f, 0.0f });

	My_Ptr<SpriteAnimation> WaveAni = GetActor()->GetComponent<SpriteAnimation>();
	WaveAni->SetEffectSprite(halo);
	

	WaveAni->CreateAnimation(L"EffectSwim",		L"halo.png", 0, 9,   0.1f, true);
	WaveAni->CreateAnimation(L"EffectTurn",		L"halo.png", 10, 19, 0.1f, true);
	WaveAni->CreateAnimation(L"EffectSwimfast",	L"halo.png", 0, 9, 0.07f, true);
	WaveAni->CreateAnimation(L"EffectTurnfast",	L"halo.png", 10, 19, 0.07f, true);
	//WaveAni->ChangeAnimation(L"EffectTurn");


	//My_Ptr<SpriteAnimation> WaveAni = GetActor()->AddComponent<SpriteAnimation>();
	//WaveAni->
	//WaveAni->CreateAnimation(L"Swim", L"halo.png", 0, 9,   0.1f, true);
	//WaveAni->CreateAnimation(L"Turn", L"halo.png", 10, 19, 0.1f, true);
	//WaveAni->CreateAnimation(L"Swimfast", L"halo.png", 0, 9, 0.07f, true);
	//WaveAni->CreateAnimation(L"Turnfast", L"halo.png", 10, 19, 0.07f, true);



	GetActor()->AddComponent<BoundingSphere>(CG_ANGIE);
	moveLogic = actor->AddComponent<AngieMove>();
}