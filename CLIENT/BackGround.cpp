#include "BackGround.h"

//==============ENGINE================//
#include <GameWindow.h>
#include <Resources.h>
#include <Scene.h>
#include <Actor.h>
#include <Sprite.h>
#include <Texture.h>
//===============ENGINESUB===============//
//#include <SpriteAnimation.h>
#include <SpriteRenderer.h>

//=====================================//
#include "ENUM.h"


BackGround::BackGround(My_Ptr<Scene> _Scene, const wchar_t* _TextureName, Vector4 _CntInfo) : Object(_Scene, _TextureName, _CntInfo)
{
	Init();
}


BackGround::~BackGround()
{

}


bool BackGround::Init()
{
	this->InitResources();


	return true;
}

bool BackGround::InitResources()
{
	Resources::Load<Texture>(Path::JoinPath(scene->GetName(), name.c_str()));
	sprite = Resources::Create<Sprite>(name.c_str(), name.c_str(),
		(int)spriteCountInfo.x, (int)spriteCountInfo.y, (int)spriteCountInfo.z, (int)spriteCountInfo.w);


	if (nullptr != sprite)
	{
		spriteCutSize = sprite->GetSpriteCutSize();
		texture = (sprite->GetTexture());
	}

	actor->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, __BACKGROUND });
	actor->GetTransform()->SetLocalScale({ spriteCutSize.x / GameWindow::Inst()->GetWindowSize().y , spriteCutSize.y / GameWindow::Inst()->GetWindowSize().y });
	//actor->GetTransform()->SetScale ({ 2.0f, 1.0f });
	actor->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);

	actor->GetTransform()->SetPosition({ 0.0f, 0.0f, 100.0f });

	spriteRenderer = actor->AddComponent<SpriteRenderer>(RENDERGROUP::RG_BACKGROUND);// 1 == player
	spriteRenderer->SetSprite(name.c_str());	

	return true;
}