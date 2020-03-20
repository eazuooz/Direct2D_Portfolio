#include "Zorf.h"

#include <ZorfMove.h>

Zorf::Zorf(My_Ptr<Scene> _Scene, const wchar_t* _TextureName, Vector4 _CntInfo) : Pet(_Scene, _TextureName, _CntInfo)
{
	CreateAnimation();
	AddComponent();
}


Zorf::~Zorf()
{
}

void Zorf::CreateAnimation()
{
	std::wstring createAniName;
	createAniName = fishName + L"Skill";
	spriteAnimation->CreateAnimation(createAniName.c_str(), spriteName.c_str(), 20, 29, 0.1f, false);
}

void Zorf::AddComponent()
{
	moveLogic = actor->AddComponent<ZorfMove>();
}


