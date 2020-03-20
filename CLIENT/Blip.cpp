#include "Blip.h"
#include <PetFishMove.h>
#include <PetList.h>


Blip::Blip(My_Ptr<Scene> _Scene, const wchar_t* _TextureName, Vector4 _CntInfo) : Pet(_Scene, _TextureName, _CntInfo)
{
	CreateAnimation();
	AddComponent();
}


Blip::~Blip()
{
}

void Blip::CreateAnimation()
{
	//std::wstring createAniName;
	//createAniName = fishName + L"Skill";
	//spriteAnimation->CreateAnimation(createAniName.c_str(), spriteName.c_str(), 20, 29, 0.1f, false);
}

void Blip::AddComponent()
{
	moveLogic = actor->AddComponent<PetFishMove>();

	PetList::existBlip = true;
}
