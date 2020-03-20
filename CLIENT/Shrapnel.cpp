#include "Shrapnel.h"


#include <ShrapnelMove.h>

shrapnel::shrapnel(My_Ptr<Scene> _Scene, const wchar_t* _TextureName, Vector4 _CntInfo) : Pet(_Scene, _TextureName, _CntInfo)
{
	CreateAnimation();
	AddComponent();
}


shrapnel::~shrapnel()
{
}

void shrapnel::CreateAnimation()
{
	//std::wstring createAniName;
	//createAniName = fishName + L"Skill";
	//spriteAnimation->CreateAnimation(createAniName.c_str(), spriteName.c_str(), 20, 29, 0.1f, false);
}

void shrapnel::AddComponent()
{
	moveLogic = actor->AddComponent<ShrapnelMove>();
}
