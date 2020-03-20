#include "Seymour.h"


#include <SeymourMove.h>

Seymour::Seymour(My_Ptr<Scene> _Scene, const wchar_t* _TextureName, Vector4 _CntInfo) : Pet(_Scene, _TextureName, _CntInfo)
{
	CreateAnimation();
	AddComponent();
}


Seymour::~Seymour()
{
}

void Seymour::CreateAnimation()
{
	//std::wstring createAniName;
	//createAniName = fishName + L"Skill";
	//spriteAnimation->CreateAnimation(createAniName.c_str(), spriteName.c_str(), 20, 29, 0.1f, false);
}

void Seymour::AddComponent()
{
	moveLogic = actor->AddComponent<SeymourMove>();
}

