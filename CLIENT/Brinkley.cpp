#include "Brinkley.h"
#include <SpriteRenderer.h>

Brinkley::Brinkley(My_Ptr<Scene> _Scene, const wchar_t* _TextureName, Vector4 _CntInfo) : Pet(_Scene, _TextureName, _CntInfo)
{
	CreateAnimation();
	AddComponent();
}


Brinkley::~Brinkley()
{
}

void Brinkley::CreateAnimation()
{
	//std::wstring createAniName;
	//createAniName = fishName + L"Skill";
	//spriteAnimation->CreateAnimation(createAniName.c_str(), spriteName.c_str(), 20, 29, 0.1f, false);
}

void Brinkley::AddComponent()
{
	//moveLogic = actor->AddComponent<ShellPetMove>();
	//moveLogic->GetSpriteRenderer()->RotateOff();
}
