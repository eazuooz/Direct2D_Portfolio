#include "Niko.h"
#include <SpriteRenderer.h>

#include <ENUM.h>
#include <NikoMove.h>

Niko::Niko(My_Ptr<Scene> _Scene, const wchar_t* _TextureName, Vector4 _CntInfo) : Pet(_Scene, _TextureName, _CntInfo)
{
	CreateAnimation();
	AddComponent();
}


Niko::~Niko()
{
}

void Niko::CreateAnimation()
{
	std::wstring createAniName;
	createAniName = fishName + L"Skill";
	spriteAnimation->CreateAnimation(createAniName.c_str(), spriteName.c_str(), 20, 29, 0.1f, false);

	actor->AddComponent<NikoMove>();
}

void Niko::AddComponent()
{
	actor->GetTransform()->SetLocalPosition({-1.85f, -0.5f, 90.0f});

	//moveLogic = actor->AddComponent<ShellPetMove>();
	//moveLogic->GetSpriteRenderer()->RotateOff();
}
