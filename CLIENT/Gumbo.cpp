#include "Gumbo.h"



#include <GumboMove.h>
#include <BoundingSphere.h>

Gumbo::Gumbo(My_Ptr<Scene> _Scene, const wchar_t* _TextureName, Vector4 _CntInfo) : Pet(_Scene, _TextureName, _CntInfo)
{
	CreateAnimation();
	AddComponent();
}


Gumbo::~Gumbo()
{
}

void Gumbo::CreateAnimation()
{
	std::wstring createAniName;
	createAniName = fishName + L"Swimlight";
	spriteAnimation->CreateAnimation(createAniName.c_str(), spriteName.c_str(), 20, 29, 0.1f, true);

	createAniName = fishName + L"Swimfastlight";
	spriteAnimation->CreateAnimation(createAniName.c_str(), spriteName.c_str(), 20, 29, 0.07f, true);

	createAniName = fishName + L"Turnlight";
	spriteAnimation->CreateAnimation(createAniName.c_str(), spriteName.c_str(), 30, 39, 0.1f, false);

	createAniName = fishName + L"Turnfastlight";
	spriteAnimation->CreateAnimation(createAniName.c_str(), spriteName.c_str(), 30, 39, 0.07f, false);
}

void Gumbo::AddComponent()
{
	BoundingSphere* collider = actor->AddComponent<BoundingSphere>(CG_GUMBO);
	collider->MultipleRadius(0.7f);
	moveLogic = actor->AddComponent<GumboMove>();

}
