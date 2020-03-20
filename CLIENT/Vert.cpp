#include "Vert.h"



#include <PetFishMove.h>
#include <CreateCoin.h>

Vert::Vert(My_Ptr<Scene> _Scene, const wchar_t* _TextureName, Vector4 _CntInfo) : Pet(_Scene, _TextureName, _CntInfo)
{
	CreateAnimation();
	AddComponent();
}


Vert::~Vert()
{
}

void Vert::CreateAnimation()
{
	//std::wstring createAniName;
	//createAniName = fishName + L"Skill";
	//spriteAnimation->CreateAnimation(createAniName.c_str(), spriteName.c_str(), 20, 29, 0.1f, false);
}

void Vert::AddComponent()
{
	moveLogic = actor->AddComponent<PetFishMove>();
	actor->AddComponent<CreateCoin>();
	actor->SetGoopy(3);

}
