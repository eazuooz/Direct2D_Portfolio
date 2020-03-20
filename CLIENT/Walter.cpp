#include "Walter.h"

#include <WalterMove.h>
#include <PetFishMove.h>

Walter::Walter(My_Ptr<Scene> _Scene, const wchar_t* _TextureName, Vector4 _CntInfo) : Pet(_Scene, _TextureName, _CntInfo)
{
	CreateAnimation();
	AddComponent();
}


Walter::~Walter()
{
}

void Walter::CreateAnimation()
{
	std::wstring createAniName;
	createAniName = fishName + L"Skill";
	spriteAnimation->CreateAnimation(createAniName.c_str(), spriteName.c_str(), 20, 24, 0.07f, false);
}

void Walter::AddComponent()
{
	actor->AddComponent<BoundingSphere>(CG_WALTER);

	moveLogic = actor->AddComponent<WalterMove>();
}