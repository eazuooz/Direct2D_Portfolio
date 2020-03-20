#include "Presto.h"

#include <PetFishMove.h>

Presto::Presto(My_Ptr<Scene> _Scene, const wchar_t* _TextureName, Vector4 _CntInfo) : Pet(_Scene, _TextureName, _CntInfo)
{
	CreateAnimation();
	AddComponent();
}


Presto::~Presto()
{
}

void Presto::CreateAnimation()
{
	std::wstring createAniName;
	createAniName = fishName + L"Skill";
	spriteAnimation->CreateAnimation(createAniName.c_str(), spriteName.c_str(), 20, 29, 0.1f, false);
}

void Presto::AddComponent()
{
	//moveLogic = actor->AddComponent<PetFishMove>();
}
