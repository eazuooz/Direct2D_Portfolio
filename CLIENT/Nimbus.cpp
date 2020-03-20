#include "Nimbus.h"




#include <ENUM.h>

Nimbus::Nimbus(My_Ptr<Scene> _Scene, const wchar_t* _TextureName, Vector4 _CntInfo) : Pet(_Scene, _TextureName, _CntInfo)
{
	CreateAnimation();
	AddComponent();
}


Nimbus::~Nimbus()
{
}

void Nimbus::CreateAnimation()
{
	//std::wstring createAniName;
	//createAniName = fishName + L"Skill";
	//spriteAnimation->CreateAnimation(createAniName.c_str(), spriteName.c_str(), 20, 29, 0.1f, false);
}

void Nimbus::AddComponent()
{

	actor->AddComponent<BoundingSphere>(CG_NIMBUS);
	moveLogic = actor->AddComponent<NimbusMove>();
}

