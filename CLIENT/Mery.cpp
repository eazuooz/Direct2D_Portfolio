#include "Mery.h"

//==============ENGINE================//
#include <GameWindow.h>
//#include <Resources.h>
//#include <Scene.h>
//#include <Actor.h>
//#include <Sprite.h>
//#include <Texture.h>
//===============ENGINESUB===============//

//=====================================//
#include "ENUM.h"


#pragma region EYE
MeryEye::MeryEye(My_Ptr<Scene> _Scene, const wchar_t* _TextureName, Vector4 _CntInfo) : Object(_Scene, _TextureName, _CntInfo)
{
	Init();
}


MeryEye::~MeryEye()
{
}

bool MeryEye::Init()
{
	this->InitResources();
	this->CreateAnimations();

	return true;
}

bool MeryEye::InitResources()
{
	Resources::Load<Texture>(Path::JoinPath(scene->GetName(), name.c_str()));
	sprite = Resources::Create<Sprite>(name.c_str(), name.c_str(),
		(int)spriteCountInfo.x, (int)spriteCountInfo.y, (int)spriteCountInfo.z, (int)spriteCountInfo.w);


	if (nullptr != sprite)
	{
		spriteCutSize = sprite->GetSpriteCutSize();
		texture = (sprite->GetTexture());
	}

	actor->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, 0.0f });
	actor->GetTransform()->SetLocalScale({ spriteCutSize.x / GameWindow::Inst()->GetWindowSize().y , spriteCutSize.y / GameWindow::Inst()->GetWindowSize().y });
	//actor->GetTransform()->SetScale ({ 2.0f, 1.0f });
	actor->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);

	actor->GetTransform()->SetLocalPosition({ -1.535f, 0.325f, 0.9f });

	spriteRenderer = actor->AddComponent<SpriteRenderer>(RENDERGROUP::RG_PLAYER);// 0 == player
	spriteRenderer->SetSprite(name.c_str());

	return true;
}

bool MeryEye::CreateAnimations()
{
	spriteAnimation = actor->AddComponent<SpriteAnimation>();

	spriteAnimation->CreateAnimation(L"MeryEyeBase",  name.c_str(), 0, 1, 0.1f, true);
	spriteAnimation->CreateAnimation(L"MeryEyeBlink", name.c_str(), 2, 7, 0.1f, false);

	return true;
}
#pragma endregion

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma region TAIL
MeryTail::MeryTail(My_Ptr<Scene> _Scene, const wchar_t* _TextureName, Vector4 _CntInfo) : Object(_Scene, _TextureName, _CntInfo)
{
	Init();
}


MeryTail::~MeryTail()
{
}

bool MeryTail::Init()
{
	this->InitResources();
	this->CreateAnimations();


	return true;
}

bool MeryTail::InitResources()
{
	Resources::Load<Texture>(Path::JoinPath(scene->GetName(), name.c_str()));
	sprite = Resources::Create<Sprite>(name.c_str(), name.c_str(),
		(int)spriteCountInfo.x, (int)spriteCountInfo.y, (int)spriteCountInfo.z, (int)spriteCountInfo.w);


	if (nullptr != sprite)
	{
		spriteCutSize = sprite->GetSpriteCutSize();
		texture = (sprite->GetTexture());
	}

	actor->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, 0.0f });
	actor->GetTransform()->SetLocalScale({ spriteCutSize.x / GameWindow::Inst()->GetWindowSize().y , spriteCutSize.y / GameWindow::Inst()->GetWindowSize().y });
	//actor->GetTransform()->SetScale ({ 2.0f, 1.0f });
	actor->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);
	actor->GetTransform()->SetLocalPosition({ -1.61f, -1.425f, 0.9f });

	spriteRenderer = actor->AddComponent<SpriteRenderer>(RENDERGROUP::RG_PLAYER);// 0 == player
	spriteRenderer->SetSprite(name.c_str());

	return true;
}

bool MeryTail::CreateAnimations()
{
	spriteAnimation = actor->AddComponent<SpriteAnimation>();

	spriteAnimation->CreateAnimation(L"MeryTailBase", name.c_str(), 0, 1, 0.1f, true);
	spriteAnimation->CreateAnimation(L"MeryTailBlink", name.c_str(), 2, 9, 0.1f, false);

	return true;
}
#pragma endregion


