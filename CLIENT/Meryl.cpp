#include "Meryl.h"

#include <MerylMove.h>

Meryl::Meryl(My_Ptr<Scene> _Scene, const wchar_t* _TextureName, Vector4 _CntInfo) : Pet(_Scene, _TextureName, _CntInfo)
{
	CreateAnimation();
	AddComponent();
}


Meryl::~Meryl()
{
}

void Meryl::CreateAnimation()
{
	std::wstring createAniName;
	createAniName = fishName + L"Skill";
	spriteAnimation->CreateAnimation(createAniName.c_str(), spriteName.c_str(), 20, 34, 0.1f, false);

	
}

void Meryl::AddComponent()
{
	moveLogic = actor->AddComponent<MerylMove>();
}
