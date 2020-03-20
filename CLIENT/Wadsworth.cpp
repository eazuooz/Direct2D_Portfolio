#include "Wadsworth.h"


#include <WadsworthMove.h>

Wadsworth::Wadsworth(My_Ptr<Scene> _Scene, const wchar_t* _TextureName, Vector4 _CntInfo) : Pet(_Scene, _TextureName, _CntInfo)
{
	CreateAnimation();
	AddComponent();
}


Wadsworth::~Wadsworth()
{
}

void Wadsworth::CreateAnimation()
{
	std::wstring createAniName;
	createAniName = fishName + L"Open";
	spriteAnimation->CreateAnimation(createAniName.c_str(), spriteName.c_str(), 20, 24, 0.1f, false);

	createAniName = fishName + L"Close";
	spriteAnimation->CreateAnimation(createAniName.c_str(), spriteName.c_str(), 25, 29, 0.1f, false);
}

void Wadsworth::AddComponent()
{
	collider = actor->AddComponent<BoundingSphere>(CG_WADSWORTH);
	collider->MultipleRadius(0.7f);

	moveLogic = actor->AddComponent<WadsworthMove>();
}