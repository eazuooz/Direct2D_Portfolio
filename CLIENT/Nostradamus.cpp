#include "Nostradamus.h"
#include <PetFishMove.h>

Nostradamus::Nostradamus(My_Ptr<Scene> _Scene, const wchar_t* _TextureName, Vector4 _CntInfo) : Pet(_Scene, _TextureName, _CntInfo)
{
	CreateAnimation();
	AddComponent();
}


Nostradamus::~Nostradamus()
{
}

void Nostradamus::CreateAnimation()
{
	//std::wstring createAniName;
	//createAniName = fishName + L"Skill";
	//spriteAnimation->CreateAnimation(createAniName.c_str(), spriteName.c_str(), 20, 29, 0.1f, false);
}

void Nostradamus::AddComponent()
{
	//moveLogic = actor->AddComponent<PetFishMove>();
}
