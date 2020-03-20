#include "Itchy.h"



#include <ItchyMove.h>

Itchy::Itchy(My_Ptr<Scene> _Scene, const wchar_t* _TextureName, Vector4 _CntInfo) : Pet(_Scene, _TextureName, _CntInfo)
{
	CreateAnimation();
	AddComponent();
}


Itchy::~Itchy()
{
}

void Itchy::CreateAnimation()
{
	std::wstring createAniName;
	createAniName = fishName + L"Skill";
	spriteAnimation->CreateAnimation(createAniName.c_str(), spriteName.c_str(), 20, 29, 0.07f, true);

	createAniName = fishName + L"Skill2";
	spriteAnimation->CreateAnimation(createAniName.c_str(), spriteName.c_str(), 30, 39, 0.06f, false);
}

void Itchy::AddComponent()
{
	moveLogic = actor->AddComponent<ItchyMove>();
}