#include "Pet.h"
#include <wchar.h>
#include <GameWindow.h>
#include <SpriteRenderer.h>



#include "ENUM.h"


Pet::Pet(My_Ptr<Scene> _Scene, const wchar_t* _TextureName, Vector4 _CntInfo) : isDataLoad(false)
{
	//state = STATE::BASE;
	name = _TextureName;
	scene = _Scene;
	spriteCountInfo = _CntInfo;

	Init();
	AnimationInit();
}


Pet::~Pet()
{
}

void Pet::Init()
{
	std::wstring actorName = scene->GetName() + name;
	size_t offset = actorName.find_last_of(L'.');
	actorName = actorName.substr(0, offset);

	actor = scene->CreateActor(name.c_str());

	textureName = name;
	spriteName = name;

	if (isDataLoad == false)
	{
		Resources::Load<Texture>(Path::JoinPath(scene->GetName(), name.c_str()));
		sprite = Resources::Create<Sprite>(textureName.c_str(), textureName.c_str(),
			(int)spriteCountInfo.x, (int)spriteCountInfo.y);

		isDataLoad = true;
	}

	

	if (nullptr != sprite)
	{
		spriteCutSize = sprite->GetSpriteCutSize();
		texture = (sprite->GetTexture());
	}

	actor->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, 0.0f });
	actor->GetTransform()->SetLocalScale({ spriteCutSize.x / GameWindow::Inst()->GetWindowSize().y , spriteCutSize.y / GameWindow::Inst()->GetWindowSize().y });
	//actor->GetTransform()->SetScale ({ 2.0f, 1.0f });
	actor->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);

	actor->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, -3.0f });

	spriteRenderer = actor->AddComponent<SpriteRenderer>(RENDERGROUP::RG_PET);// 0 == player
	spriteRenderer->SetSprite(spriteName.c_str());
}

void Pet::AnimationInit()
{
	fishName = name;
	for (int i = 0; i < 4; ++i)
	{
		fishName.pop_back();
	}
	
	std::wstring createAniName;

	spriteAnimation = actor->AddComponent<SpriteAnimation>();

	createAniName = fishName + L"Swim";
	spriteAnimation->CreateAnimation(createAniName.c_str(), spriteName.c_str(), 0, 9, 0.1f, true);
	createAniName = fishName + L"Swimfast";
	spriteAnimation->CreateAnimation(createAniName.c_str(), spriteName.c_str(), 0, 9, 0.07f, true);


	createAniName = fishName + L"Turn";
	spriteAnimation->CreateAnimation(createAniName.c_str(), spriteName.c_str(), 10, 19, 0.1f, false);
	createAniName = fishName + L"Turnfast";
	spriteAnimation->CreateAnimation(createAniName.c_str(), spriteName.c_str(), 10, 19, 0.07f, false);
	   	

	
}




