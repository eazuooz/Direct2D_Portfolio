#include "Prego.h"

#include <PregoMove.h>

Prego::Prego(My_Ptr<Scene> _Scene, const wchar_t* _TextureName, Vector4 _CntInfo) : Pet(_Scene, _TextureName, _CntInfo)
{
	CreateAnimation();
	AddComponent();
}


Prego::~Prego()
{
}

void Prego::CreateAnimation()
{
	std::wstring createAniName;
	createAniName = fishName + L"Skill";
	spriteAnimation->CreateAnimation(createAniName.c_str(), spriteName.c_str(), 20, 39, 0.1f, false);
	 
	
	createAniName = fishName + L"Skill2";
	spriteAnimation->CreateAnimation(createAniName.c_str(), spriteName.c_str(), 30, 34, 0.1f, false);

	createAniName = fishName + L"Skill3";
	spriteAnimation->CreateAnimation(createAniName.c_str(), spriteName.c_str(), 35, 39, 0.1f, false);
}

void Prego::AddComponent()
{
	moveLogic = actor->AddComponent<PregoMove>();
}
