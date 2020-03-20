#include "Stanley.h"


#include <StanleyMove.h>


Stanley::Stanley(My_Ptr<Scene> _Scene, const wchar_t* _TextureName, Vector4 _CntInfo) : Pet(_Scene, _TextureName, _CntInfo)
{
	CreateAnimation();
	AddComponent();
}


Stanley::~Stanley()
{
}

void Stanley::CreateAnimation()
{
	std::wstring createAniName;
	createAniName = fishName + L"SwimChange";
	spriteAnimation->CreateAnimation(createAniName.c_str(), spriteName.c_str(), 20, 29, 0.1f, true);

	createAniName = fishName + L"TurnChange";
	spriteAnimation->CreateAnimation(createAniName.c_str(), spriteName.c_str(), 30, 39, 0.1f, false);
		
	createAniName = fishName + L"SwimfastChange";
	spriteAnimation->CreateAnimation(createAniName.c_str(), spriteName.c_str(), 20, 29, 0.1f, true);

	createAniName = fishName + L"TurnfastChange";
	spriteAnimation->CreateAnimation(createAniName.c_str(), spriteName.c_str(), 30, 39, 0.1f, false);


	createAniName = fishName + L"Attack";
	spriteAnimation->CreateAnimation(createAniName.c_str(), spriteName.c_str(), 40, 49, 0.1f, false);

	createAniName = fishName + L"Change";
	spriteAnimation->CreateAnimation(createAniName.c_str(), spriteName.c_str(), 50, 59, 0.1f, false);

}

void Stanley::AddComponent()
{
	moveLogic = actor->AddComponent<StanleyMove>();
}
