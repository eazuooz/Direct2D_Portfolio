//#define _CRT_SECURE_NO_WARNINGS

#include "Goopy.h"
#include <wchar.h>
#include <GameWindow.h>
#include <CreateCoin.h>


#include "ENUM.h"
int Goopy::textureLoadCnt = 0;
int Goopy::fishCnt = 0;
std::wstring Goopy::textureName;

//std::list<BoundingSphere*> Goopy::littleGoopyList;
//std::list < BoundingSphere*>::iterator Goopy::littleGoopyBegin;
//std::list < BoundingSphere*>::iterator Goopy::littleGoopyEnd;

Goopy::Goopy(My_Ptr<Scene> _Scene, const wchar_t* _TextureName, Vector4 _CntInfo, int _Point, int _Collider) : Object(_Scene, _TextureName, _CntInfo), texture(nullptr), sprite(nullptr)
{
	Init(_Point, _Collider);
}


Goopy::~Goopy()
{
}

bool Goopy::Init(int _Point, int _Collider)
{


	point = _Point;
	this->InitResources(_Collider);
	this->CreateAnimations();


	logic = actor->AddComponent<GoopyMove>();
	logic->SetPoint(_Point);

	//logic->SetStateMoving();
	
	actor->AddComponent<CreateCoin>();


	return true;
}
bool Goopy::InitResources(int _Collider)
{
	if (textureLoadCnt == 0)
	{
		textureName = name;
		Resources::Load<Texture>(Path::JoinPath(scene->GetName(), name.c_str()));
	}

	wchar_t  number[100] = {0};
	//wchar_t* number = nullptr;
	_itow(fishCnt, number, 10);

	spriteName = name;	
	for (int i = 0; i < 4; ++i)
	{
		spriteName.pop_back();
	}
	spriteName.append(number);
	spriteName.append(L".png");

	sprite = Resources::Create<Sprite>(spriteName.c_str(), textureName.c_str(),
		(int)spriteCountInfo.x, (int)spriteCountInfo.y, (int)spriteCountInfo.z, (int)spriteCountInfo.w);

	if (nullptr != sprite)
	{
		spriteCutSize = sprite->GetSpriteCutSize();
		texture = (sprite->GetTexture());

		++textureLoadCnt;
		++fishCnt;
	}

	actor->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, 0.0f });
	actor->GetTransform()->SetLocalScale({ spriteCutSize.x / GameWindow::Inst()->GetWindowSize().y , spriteCutSize.y / GameWindow::Inst()->GetWindowSize().y });
	//actor->GetTransform()->SetScale ({ 2.0f, 1.0f });
	actor->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);

	actor->GetTransform()->SetLocalPosition({ 0.0f, 0.0f, 80.0f });

	if (point >= 2000000)
	{
		actor->GetTransform()->LocalScaleMultiple(1.5f);
	}

	spriteRenderer = actor->AddComponent<SpriteRenderer>(RENDERGROUP::RG_PLAYER);// 0 == player
	spriteRenderer->SetSprite(spriteName.c_str());

	collider = actor->AddComponent<BoundingSphere>((COLGROUP)_Collider);
	collider->MultipleRadius(0.5f);



	
	

	return true;
}
bool Goopy::CreateAnimations()
{
	spriteAnimation = actor->AddComponent<SpriteAnimation>();
	spriteAnimation->CreateAnimation(L"Goopy1Swim", spriteName.c_str(), 0, 9,	0.08f, true);
	spriteAnimation->CreateAnimation(L"Goopy2Swim", spriteName.c_str(), 10, 19, 0.08f, true);
	spriteAnimation->CreateAnimation(L"Goopy3Swim", spriteName.c_str(), 20, 29, 0.08f, true);
	spriteAnimation->CreateAnimation(L"Goopy4Swim", spriteName.c_str(), 30, 39, 0.08f, true);
	spriteAnimation->CreateAnimation(L"Goopy5Swim", spriteName.c_str(), 40, 49, 0.08f, true);
	spriteAnimation->CreateAnimation(L"Goopy1Turn", spriteName.c_str(), 50, 59, 0.08f, false);
	spriteAnimation->CreateAnimation(L"Goopy2Turn", spriteName.c_str(), 60, 69, 0.08f, false);
	spriteAnimation->CreateAnimation(L"Goopy3Turn", spriteName.c_str(), 70, 79, 0.08f, false);
	spriteAnimation->CreateAnimation(L"Goopy4Turn", spriteName.c_str(), 80, 89, 0.08f, false);
	spriteAnimation->CreateAnimation(L"Goopy5Turn", spriteName.c_str(), 90, 99, 0.08f, false);
	spriteAnimation->CreateAnimation(L"Goopy1Eat", spriteName.c_str(), 100, 109, 0.08f, false);
	spriteAnimation->CreateAnimation(L"Goopy2Eat", spriteName.c_str(), 110, 119, 0.08f, false);
	spriteAnimation->CreateAnimation(L"Goopy3Eat", spriteName.c_str(), 120, 129, 0.08f, false);
	spriteAnimation->CreateAnimation(L"Goopy4Eat", spriteName.c_str(), 130, 139, 0.08f, false);
	spriteAnimation->CreateAnimation(L"Goopy5Eat", spriteName.c_str(), 140, 149, 0.08f, false);

	spriteAnimation->CreateAnimation(L"Goopy1Swimfast",spriteName.c_str(), 0, 9,	0.05f, true);
	spriteAnimation->CreateAnimation(L"Goopy2Swimfast",spriteName.c_str(), 10, 19,	0.05f, true);
	spriteAnimation->CreateAnimation(L"Goopy3Swimfast",spriteName.c_str(), 20, 29,	0.05f, true);
	spriteAnimation->CreateAnimation(L"Goopy4Swimfast",spriteName.c_str(), 30, 39,	0.05f, true);
	spriteAnimation->CreateAnimation(L"Goopy5Swimfast",spriteName.c_str(), 40, 49,	0.05f, true);
	spriteAnimation->CreateAnimation(L"Goopy1Turnfast", spriteName.c_str(), 50, 59, 0.05f, false);
	spriteAnimation->CreateAnimation(L"Goopy2Turnfast", spriteName.c_str(), 60, 69, 0.05f, false);
	spriteAnimation->CreateAnimation(L"Goopy3Turnfast", spriteName.c_str(), 70, 79, 0.05f, false);
	spriteAnimation->CreateAnimation(L"Goopy4Turnfast", spriteName.c_str(), 80, 89, 0.05f, false);
	spriteAnimation->CreateAnimation(L"Goopy5Turnfast", spriteName.c_str(), 90, 99, 0.05f, false);

	//HUNGRY
	
	spriteAnimation->CreateAnimation(L"Goopy1SwimHungry", spriteName.c_str(), 150, 159, 0.08f, true);
	spriteAnimation->CreateAnimation(L"Goopy2SwimHungry", spriteName.c_str(), 160, 169, 0.08f, true);
	spriteAnimation->CreateAnimation(L"Goopy3SwimHungry", spriteName.c_str(), 170, 179, 0.08f, true);
	spriteAnimation->CreateAnimation(L"Goopy4SwimHungry", spriteName.c_str(), 180, 189, 0.08f, true);
	spriteAnimation->CreateAnimation(L"Goopy5SwimHungry", spriteName.c_str(), 190, 199, 0.08f, true);
	spriteAnimation->CreateAnimation(L"Goopy1TurnHungry", spriteName.c_str(), 200, 209, 0.08f, false);
	spriteAnimation->CreateAnimation(L"Goopy2TurnHungry", spriteName.c_str(), 210, 219, 0.08f, false);
	spriteAnimation->CreateAnimation(L"Goopy3TurnHungry", spriteName.c_str(), 220, 229, 0.08f, false);
	spriteAnimation->CreateAnimation(L"Goopy4TurnHungry", spriteName.c_str(), 230, 239, 0.08f, false);
	spriteAnimation->CreateAnimation(L"Goopy5TurnHungry", spriteName.c_str(), 240, 249, 0.08f, false);
	spriteAnimation->CreateAnimation(L"Goopy1EatHungry", spriteName.c_str(), 250, 259, 0.8f, true);
	spriteAnimation->CreateAnimation(L"Goopy2EatHungry", spriteName.c_str(), 260, 269, 0.8f, true);
	spriteAnimation->CreateAnimation(L"Goopy3EatHungry", spriteName.c_str(), 270, 279, 0.8f, true);
	spriteAnimation->CreateAnimation(L"Goopy4EatHungry", spriteName.c_str(), 280, 289, 0.8f, true);
	spriteAnimation->CreateAnimation(L"Goopy5EatHungry", spriteName.c_str(), 290, 299, 0.8f, true);

	spriteAnimation->CreateAnimation(L"Goopy1SwimfastHungry", spriteName.c_str(), 150, 159, 0.05f, true);
	spriteAnimation->CreateAnimation(L"Goopy2SwimfastHungry", spriteName.c_str(), 160, 169, 0.05f, true);
	spriteAnimation->CreateAnimation(L"Goopy3SwimfastHungry", spriteName.c_str(), 170, 179, 0.05f, true);
	spriteAnimation->CreateAnimation(L"Goopy4SwimfastHungry", spriteName.c_str(), 180, 189, 0.05f, true);
	spriteAnimation->CreateAnimation(L"Goopy5SwimfastHungry", spriteName.c_str(), 190, 199, 0.05f, true);
	spriteAnimation->CreateAnimation(L"Goopy1TurnfastHungry", spriteName.c_str(), 200, 209, 0.05f, false);
	spriteAnimation->CreateAnimation(L"Goopy2TurnfastHungry", spriteName.c_str(), 210, 219, 0.05f, false);
	spriteAnimation->CreateAnimation(L"Goopy3TurnfastHungry", spriteName.c_str(), 220, 229, 0.05f, false);
	spriteAnimation->CreateAnimation(L"Goopy4TurnfastHungry", spriteName.c_str(), 230, 239, 0.05f, false);
	spriteAnimation->CreateAnimation(L"Goopy5TurnfastHungry", spriteName.c_str(), 240, 249, 0.05f, false);


	//DIE
	spriteAnimation->CreateAnimation(L"Goopy1Die", spriteName.c_str(), 300, 309, 0.1f, false);
	spriteAnimation->CreateAnimation(L"Goopy2Die", spriteName.c_str(), 310, 319, 0.1f, false);
	spriteAnimation->CreateAnimation(L"Goopy3Die", spriteName.c_str(), 320, 329, 0.1f, false);
	spriteAnimation->CreateAnimation(L"Goopy4Die", spriteName.c_str(), 330, 339, 0.1f, false);
	spriteAnimation->CreateAnimation(L"Goopy5Die", spriteName.c_str(), 340, 349, 0.1f, false);

	//
	spriteName.clear();
	spriteName.append(L"UltraFish.png");
	//wchar_t  number[100] = { 0 };
	////wchar_t* number = nullptr;
	//_itow(fishCnt, number, 10);
	////spriteName.append(number);
	//spriteName.append(L".png");
	if (point >= 2000000)
	{
		spriteRenderer->SetSprite(spriteName.c_str());
	}
	spriteAnimation->CreateAnimation(L"Goopy6Swim",		spriteName.c_str(), 0, 9, 0.08f, true);
	spriteAnimation->CreateAnimation(L"Goopy6Swimfast", spriteName.c_str(), 0, 9, 0.05f, true);

	spriteAnimation->CreateAnimation(L"Goopy6Eat",		spriteName.c_str(), 10, 19, 0.08f, false);
	spriteAnimation->CreateAnimation(L"Goopy6Turn",		spriteName.c_str(), 20, 29, 0.08f, false);
	spriteAnimation->CreateAnimation(L"Goopy6Turnfast", spriteName.c_str(), 20, 29, 0.05f, false);

	spriteAnimation->CreateAnimation(L"Goopy6SwimHungry", spriteName.c_str(), 0, 9, 0.08f, true);
	spriteAnimation->CreateAnimation(L"Goopy6SwimfastHungry", spriteName.c_str(), 0, 9, 0.05f, true);
	spriteAnimation->CreateAnimation(L"Goopy6EatHungry", spriteName.c_str(), 10, 19, 0.08f, false);
	spriteAnimation->CreateAnimation(L"Goopy6TurnHungry", spriteName.c_str(), 20, 29, 0.08f, false);
	spriteAnimation->CreateAnimation(L"Goopy6TurnfastHungry", spriteName.c_str(), 20, 29, 0.05f, false);

	spriteAnimation->CreateAnimation(L"Goopy6Die",		spriteName.c_str(), 30, 39, 0.08f, false);
	

	spriteAnimation->ChangeAnimation(L"Goopy1Swim");


	return true;
}


//void Goopy::LittleGoopyList_Update()
//{
//
//}
//
//void Goopy::PushLittleGoopy(BoundingSphere* _Collider)
//{
//	littleGoopyList.push_back(_Collider);
//}
//void Goopy::PopLittleGoopy(const BoundingSphere* _Collider)
//{
//	littleGoopyBegin = littleGoopyList.begin();
//	littleGoopyEnd = littleGoopyList.end();
//
//	for (; littleGoopyBegin != littleGoopyEnd;)
//	{
//		if ((*littleGoopyEnd) == _Collider)
//		{
//			littleGoopyBegin = littleGoopyList.erase(littleGoopyBegin);
//		}
//		else
//		{
//			++littleGoopyBegin;
//		}
//	}
//}
//void Goopy::PopLittleGoopy(const Collider* _Collider)
//{
//	littleGoopyList.push_back((BoundingSphere*)_Collider);
//}