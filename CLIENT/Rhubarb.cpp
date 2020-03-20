#include "Rhubarb.h"
#include <SpriteRenderer.h>
//#include <ShellPetMove.h>
#include <RhubarbMove.h>
#include <BoundingSphere.h>
#include <ENUM.h>

Rhubarb::Rhubarb(My_Ptr<Scene> _Scene, const wchar_t* _TextureName, Vector4 _CntInfo) : Pet(_Scene, _TextureName, _CntInfo)
{
	CreateAnimation();
	AddComponent();
}


Rhubarb::~Rhubarb()
{
}

void Rhubarb::CreateAnimation()
{
	std::wstring createAniName;
	createAniName = fishName + L"Skill";
	spriteAnimation->CreateAnimation(createAniName.c_str(), spriteName.c_str(), 20, 29, 0.07f, false);
}

void Rhubarb::AddComponent()
{
	actor->AddComponent<BoundingSphere>(CG_RHUBARB);
	moveLogic = actor->AddComponent<RhubarbMove>();
	//moveLogic->GetSpriteRenderer()->RotateOff();
	
	


}
