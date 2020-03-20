#include "FishMove.h"

#include <cmath>
//ENGINE
#include <GameWindow.h>
#include <SpriteRenderer.h>
#include <SpriteAnimation.h>

#include "FoodList.h"
#include "FoodMove.h"
#include "StartBubbleMove.h"
#include "GoopyList.h"
#include "MonsterList.h"
#include "WadsworthMove.h"
#include "GumboMove.h"

#include "ENUM.h"
#include "PetList.h"

#include "CoinList.h"
#include "CoinMove.h"
#include "CreateCoin.h"
#include <Sound.h>

//std::list<BoundingSphere*> GoopyMove::littleGoopyList;
//std::list<BoundingSphere*>::iterator GoopyMove::littleGoopyBegin;
//std::list<BoundingSphere*>::iterator GoopyMove::littleGoopyEnd;
bool GoopyMove::isAmpOn = false;

GoopyMove::GoopyMove() : direction(0.0f), moveSpeed(1.0f), movingTime(Well512Random::Instance().GetFloatValue(0.5f, 3.0f)), spriteRenderer(nullptr), spriteAnimaion(nullptr),
isFast(false), hungryTime(HUNGRYTIME), isHungry(false), deadTime(10.0f), isDeadBody(false), minDis(100.0f), existFood(false), kindsOfGoopy(LITTLE),point(0)
, createBubble(false), rhubarbTime(1.0f), rhubarbMoveSpeed(1.5f), ISDie(false)
{
}


GoopyMove::~GoopyMove()
{
}

bool GoopyMove::GetFishName()
{
	std::wstring originName = curAniName;
	for (int i = 0; i < 4; ++i)
	{
		curAniName.pop_back();
	}
	fishName = curAniName;
	curAniName = originName;

	return true;
}

void GoopyMove::Init()
{
	windowSize	= (GameWindow::Inst()->GetWindowSize() / 100.0f )/ 2.0f;
	direction	= { 0.0f, -2.0f, 0.0f };
	state		= GOOPYSTATE::START;

	float x = Well512Random::Instance().GetFloatValue(-3.0f, 3.0f);
	float y = 2.0f;
	GetActor()->GetTransform()->SetLocalPosition({x,y, __GOOPY});

	spriteRenderer	= GetActor()->GetComponent<SpriteRenderer>();
	spriteAnimaion	= GetActor()->GetComponent<SpriteAnimation>();
	curAniName		= spriteAnimaion->GetCurAni()->curAnimationName;

	collider = GetActor()->GetComponent<BoundingSphere>();
	collider->RegisterEnterFunction	(&GoopyMove::Enter,	this);
	collider->RegisterStayFunction	(&GoopyMove::Stay,	this);
	collider->RegisterExitFunction	(&GoopyMove::Exit,	this);

	GetFishName();

	pointRender = GetActor()->AddComponent<SpriteRenderer>(RG_UI);
	pointRender->SetSprite(L"items.png");
	
	pointRender->SetLocalPosition({-0.1f, 0.2f, 0.0f, 0.0f});

	pointRender->UpdateOff();

	
}

void GoopyMove::Update()
{
	if (PetList::existBlip == true)
	{
		if (hungryTime < 5.0f)
		{
			pointRender->UpdateOn();
		}
		else
		{
			pointRender->UpdateOff();
		}
	}

	if (state != GOOPYSTATE::START)
	{

#pragma region SET TIME AND DIR
		hungryTime -= Time::DeltaTime();
		pos = GetActor()->GetTransform()->GetLocalPosition();
		if (direction.x < 0.0f)
		{
			DIR = DIRECTION::LEFT;
		}
		else if (direction.x > 0.0f)
		{
			DIR = DIRECTION::RIGHT;
		}

		///////

		if (hungryTime < 0.0f)
		{
			isHungry = true;
			deadTime -= Time::DeltaTime();
		}
		else
		{
			deadTime = 10.0f;
			isHungry = false;
		}

		if (deadTime < 0.0f)
		{
			if (soundDie == false)
			{
				Sound::Play(L"DIE.wav");
				soundDie = true;
			}
			state = GOOPYSTATE::DIE;
			goto GOOPY_DEATH;
		}
#pragma endregion
					   
		if (true == isHungry)	//배고플때
		{
			switch (kindsOfGoopy)
			{
			case KINDSOFGOOPY::LITTLE:	
			case KINDSOFGOOPY::MIDDLE:	
				/*FindWadsWorth();
				break;*/
			case KINDSOFGOOPY::BIG:	// fallthrough
			case KINDSOFGOOPY::CROWN:
				{
					FindFood();
				}
				break;
			case KINDSOFGOOPY::PIRANA:
				{
		
					FindLittleGoopy();
							
				}
				break;
			case KINDSOFGOOPY::ULTRA:
				{
		
					FindPirana();
				
				}
				break;
			}

			if (state != GOOPYSTATE::STOP)
			{
				state = GOOPYSTATE::HUNGRY;
			}			
		}
		
		if (MonsterList::GetMonsterList().size() != 0)
		{
			switch (kindsOfGoopy)	//배고프지않을때
			{
			case KINDSOFGOOPY::LITTLE:
			case KINDSOFGOOPY::MIDDLE:
			{
				if (PetList::existWads== true)
				{
					FindWadsWorth();
				}				
			}
			break;
			case KINDSOFGOOPY::BIG:	// fallthrough
			case KINDSOFGOOPY::CROWN:
			case KINDSOFGOOPY::PIRANA:
			case KINDSOFGOOPY::ULTRA:
			{
				if (PetList::existGumbo == true)
				{
					FindGumbo();
				}

			}
			break;
			}
		}

	}

	prevkindsOfGoopy = kindsOfGoopy;
#pragma region STATE
	if (point < 20)
	{
		kindsOfGoopy = KINDSOFGOOPY::LITTLE;
		GetActor()->SetGoopy(CG_LITTLEGOOPY);
	}
	else if (point > 20 && point < 60)
	{
		kindsOfGoopy = KINDSOFGOOPY::MIDDLE;
		collider->MultipleRadius(0.6f);
		collider->SetOrder(CG_MIDDLEGOOPY);
		GetActor()->SetGoopy(CG_MIDDLEGOOPY);
	}
	else if (point > 60 && point < 120)
	{
		kindsOfGoopy = KINDSOFGOOPY::BIG;
		collider->MultipleRadius(0.7f);
		collider->SetOrder(CG_BIGGOOPY);
		GetActor()->SetGoopy(CG_BIGGOOPY);
	}
	else if (point > 120 && point < 20000)
	{
		kindsOfGoopy = KINDSOFGOOPY::CROWN;
		GetActor()->SetGoopy(CG_CROWNGOOPY);
		collider->MultipleRadius(0.7f);
		collider->SetOrder(CG_CROWNGOOPY);
		//kindsOfGoopy = KINDSOFGOOPY::PIRANA;
	}
	else if (point > 20000 && point < 2000000)
	{
		kindsOfGoopy = KINDSOFGOOPY::PIRANA;
		GetActor()->SetGoopy(CG_PIRANA);
		collider->SetOrder(CG_PIRANA);
		collider->MultipleRadius(0.7f);
		//kindsOfGoopy = KINDSOFGOOPY::PIRANA;
	}
	else if (point > 2000000)
	{
		kindsOfGoopy = KINDSOFGOOPY::ULTRA;
		GetActor()->SetGoopy(CG_ULTRAGOOPY);
		collider->MultipleRadius(0.7f);
		collider->SetOrder(CG_ULTRAGOOPY);
		//kindsOfGoopy = KINDSOFGOOPY::PIRANA;
	}

	if (prevkindsOfGoopy != kindsOfGoopy)
	{
		Sound::Play(L"grow.wav");
		prevkindsOfGoopy = kindsOfGoopy;
	}

	if (isAmpOn == true)
	{
		if (point < 2000)
		{
			//state = GOOPYSTATE::DIE;

			deadTime = -10.0f;
			hungryTime = -10.0f;

			createDiamond = true;
		}
	}

	switch (kindsOfGoopy)
	{
	case KINDSOFGOOPY::LITTLE:

		break;
	case KINDSOFGOOPY::MIDDLE:
		fishName.pop_back();
		fishName += L"2";
		
		
		break;
	case KINDSOFGOOPY::BIG:
		fishName.pop_back();
		fishName += L"3";
		break;
	case KINDSOFGOOPY::CROWN:
		fishName.pop_back();
		fishName += L"4";
		break;
	case KINDSOFGOOPY::PIRANA:
		fishName.pop_back();
		fishName += L"5";
		break;
	case KINDSOFGOOPY::ULTRA:
		fishName.pop_back();
		fishName += L"6";
		break;
	}
#pragma endregion

	switch (state)
	{
	case GoopyMove::GOOPYSTATE::START:
		Start();
		break;
	case GoopyMove::GOOPYSTATE::MOVING:
		Moving();
		break;
	case GoopyMove::GOOPYSTATE::STOP:
		Stop();
		break;	
	case GoopyMove::GOOPYSTATE::HUNGRY:
		Hungry();
		break;
	case GoopyMove::GOOPYSTATE::EATING:
		Eating();
		break;

	case GoopyMove::GOOPYSTATE::WADSWORTH:
		WadsWorth();
		break;

	case GoopyMove::GOOPYSTATE::GUMBO:
		Gumbo();
		break;

	case GoopyMove::GOOPYSTATE::RHUBARB:
		Rhubarb();
		break;

	case GoopyMove::GOOPYSTATE::DIE:
GOOPY_DEATH:
		GoopyDie();
		break;	
	}

#pragma region RELEASE CHILD ACTOR
	/////RELEASE
	if (chompAni != nullptr && chompAni->GetCurAni()->aniEnd == true)
	{
		chomp->Die();
	}
#pragma endregion
}

void GoopyMove::Start()
{
	ChangeAnimation();
	int a = 0;
	direction.y += 1.5f * Time::DeltaTime();

	GetActor()->GetTransform()->Move2D((direction* 1.5f * Time::DeltaTime()), __GOOPY);

	if (GetActor()->GetTransform()->GetLocalPosition().y < 1.4f && createBubble == false)
	{
		for (int i = 0; i < 5; ++i)
		{
			My_Ptr<Actor> hatchGoopy = GetScene()->CreateActor(L"bubbles");
			My_Ptr<SpriteRenderer> hatchGoopyRenderer = hatchGoopy->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
			hatchGoopyRenderer->SetSprite(L"bubbles.png");
			hatchGoopyRenderer->SetBlender(L"BLEND1TO1");
			My_Ptr<SpriteAnimation>  hatchGoopyAni = hatchGoopy->AddComponent<SpriteAnimation>();
			//hatchGoopyAni->CreateAnimation(L"egg1", L"egg.png", 0, 0, 0.1f, false);
			hatchGoopyAni->CreateAnimation(L"bubbles", L"bubbles.png", 0, 4, 0.8f, false);

			Vector4 tempPos = { GetActor()->GetTransform()->GetPosition() };
			
			
			//std::is_nan(value);
			hatchGoopy->GetTransform()->SetLocalPosition({ tempPos.x + Well512Random::Instance().GetFloatValue(0.2f, -0.2f), tempPos.y + Well512Random::Instance().GetFloatValue(0.5f, -0.5f), __UI });
			hatchGoopy->GetTransform()->SetLocalScale({ 80.0f / GameWindow::Inst()->GetWindowSize().y , 80.0f / GameWindow::Inst()->GetWindowSize().y });
			hatchGoopy->GetTransform()->LocalScaleMultiple(/*4.8f*/ GameWindow::Inst()->GetWindowSize().y / 100.0f);
			hatchGoopy->GetTransform()->LocalScaleMultiple(0.3f);
			hatchGoopy->AddComponent<StartBubbleMove>();
		}
		createBubble = true;
	}

	if (direction.y > 0.3f)
	{
		state = GOOPYSTATE::MOVING;
	}
}

void GoopyMove::Moving()
{
	ChangeAnimation();

	movingTime -= Time::DeltaTime();
	if (movingTime < 0.0f)
	{
		movingTime = Well512Random::Instance().GetFloatValue(0.5f, 5.0f);
		moveSpeed = 1.0f;

		switch (DIR)
		{
		case GoopyMove::LEFT:
		{
			float x = Well512Random::Instance().GetFloatValue(-1.0f, 1.0f);
			float y = Well512Random::Instance().GetFloatValue(-1.0f, 1.0f);
			direction = { x, y, 5.0f };

			if (direction.x > 0.0f)
			{
				state = GOOPYSTATE::STOP;
			}
			break;
		}
		case GoopyMove::RIGHT:
		{
			float x = Well512Random::Instance().GetFloatValue(-1.0f, 1.0f);
			float y = Well512Random::Instance().GetFloatValue(-1.0f, 1.0f);
			direction = { x, y, 5.0f };

			if (direction.x < 0.0f)
			{
				state = GOOPYSTATE::STOP;
			}

			break;
		}
		}
	}
	else
	{
		MoveGoopy(1.0f);
	}
}

void GoopyMove::Stop()
{
	Vector4 fast;
	fast.x = abs(direction.x);
	fast.y = abs(direction.y);

	float maxf = fast.x + fast.y;
	if (maxf > 1.0f)
	{
		isFast = true;
	}
	else
	{
		isFast = false;
	}

	if (spriteAnimaion->GetCurAni()->aniEnd == true)
	{
		std::wstring tempSwim; //= fishName + L"Swim";
		if (isFast == true)
		{
			tempSwim = fishName + L"Swimfast";
		}
		else
		{
			tempSwim = fishName + L"Swim";
		}
		
		if (true == isHungry)	//배고파지면 배고픈물고기 색으로 변하는 애니메이션
		{
			tempSwim.append(L"Hungry");
		}



		if (DIR == DIRECTION::LEFT)
		{			
			spriteRenderer->TurnLeft();			
			spriteAnimaion->ChangeAnimation(tempSwim.c_str());			
		}
		else
		{

			spriteRenderer->TurnRight();	
			spriteAnimaion->ChangeAnimation(tempSwim.c_str());
		}
		
		if (isHungry == true)
		{
			state = GOOPYSTATE::HUNGRY;
		}
		else
		{
			state = GOOPYSTATE::MOVING;
		}

		if (existWads == true && MonsterList::GetMonsterList().size() != 0)
		{
			state = GOOPYSTATE::WADSWORTH;
		}

		if (existGumbo == true && MonsterList::GetMonsterList().size() != 0)
		{
			state = GOOPYSTATE::GUMBO;
		}

		
	}
	else
	{
		std::wstring temp; //= fishName + L"Turn";
		if (isFast == true)
		{
			temp = fishName + L"Turnfast";
		}
		else
		{
			temp = fishName + L"Turn";
		}

		if (true == isHungry) //배고파지면 배고픈물고기 색으로 변하는 애니메이션
		{
			temp.append(L"Hungry");
		}

		
		spriteAnimaion->ChangeAnimation(temp.c_str());
	}



	MoveGoopy(1.0f);
	
}

void GoopyMove::Hungry()
{
	ChangeAnimation();

	movingTime -= Time::DeltaTime();
	if (movingTime < 0.0f && existFood == false)		//먹이가 존재하지않고 무빙타임이 0보다 작아졌을때
	{
		movingTime = Well512Random::Instance().GetFloatValue(0.5f, 5.0f);
		moveSpeed = 1.0f;

		switch (DIR)
		{
			case GoopyMove::LEFT:
			{
				if (existFood == true)
				{
					direction = minDis.ReturnNormalization();
				}
				else
				{
					float x = Well512Random::Instance().GetFloatValue(-1.0f, 1.0f);
					float y = Well512Random::Instance().GetFloatValue(-1.0f, 1.0f);
					direction = { x, y, 5.0f };
				}

				if (direction.x < 0.0f)
				{
					spriteRenderer->TurnLeft();
				}
				else if (direction.x > 0.0f)
				{
					state = GOOPYSTATE::STOP;
				}
				break;
			}
			case GoopyMove::RIGHT:
			{
				if (existFood == true)
				{
					direction = minDis.ReturnNormalization();
				}
				else
				{
					float x = Well512Random::Instance().GetFloatValue(-1.0f, 1.0f);
					float y = Well512Random::Instance().GetFloatValue(-1.0f, 1.0f);
					direction = { x, y, 5.0f };
				}

				if (direction.x < 0.0f)
				{
					//spriteRenderer->TurnLeft();
					state = GOOPYSTATE::STOP;
				}
				else if (direction.x > 0.0f)
				{
					spriteRenderer->TurnRight();
				}
				break;
			}
		}
	}
	else // 먹이가 존재할때 또는 무빙타임이 0.0보다 클때
	{
		if (existFood == true)
		{
			if (kindsOfGoopy == KINDSOFGOOPY::PIRANA || kindsOfGoopy == KINDSOFGOOPY::ULTRA)
			{
				moveSpeed += 0.5f * Time::DeltaTime();
			}
			else
			{
				moveSpeed += 5.0f * Time::DeltaTime();
			}
			
		}
		else
		{
			moveSpeed = 1.0f;
		}
		switch (DIR)
		{
			case GoopyMove::LEFT:
			{
				if (existFood == true)
				{
					direction = minDis.ReturnNormalization();
				}
				else
				{
					/*float x = Well512Random::Instance().GetFloatValue(-1.0f, 1.0f);
					float y = Well512Random::Instance().GetFloatValue(-1.0f, 1.0f);
					direction = { x, y, 5.0f };*/
				}

				if (direction.x < 0.0f)
				{
					spriteRenderer->TurnLeft();
				}
				else if (direction.x > 0.0f)
				{
					state = GOOPYSTATE::STOP;
				}
				break;
			}
			case GoopyMove::RIGHT:
			{
				if (existFood == true)
				{
					direction = minDis.ReturnNormalization();
				}
				else
				{
					//float x = Well512Random::Instance().GetFloatValue(-1.0f, 1.0f);
					//float y = Well512Random::Instance().GetFloatValue(-1.0f, 1.0f);
					//direction = { x, y, 5.0f };
				}

				if (direction.x < 0.0f)
				{
					//spriteRenderer->TurnLeft();
					state = GOOPYSTATE::STOP;
				}
				else if (direction.x > 0.0f)
				{
					spriteRenderer->TurnRight();
				}
				break;
			}
		}

		MoveGoopy(moveSpeed);
	}
}

void GoopyMove::Eating()
{
	if (spriteAnimaion->GetCurAni()->aniEnd == true)
	{
		state = GOOPYSTATE::MOVING;
		//return;
	}

	std::wstring tempSwim; //= fishName + L"Swim";
	tempSwim = fishName + L"Eat";
	spriteAnimaion->ChangeAnimation(tempSwim.c_str());

	if (kindsOfGoopy == KINDSOFGOOPY::PIRANA || kindsOfGoopy == KINDSOFGOOPY::ULTRA)
	{
		MoveGoopy(1.0f);
	}
	else
	{
		MoveGoopy(10.0f);
	}

	
}

void GoopyMove::GoopyDie()
{
	pointRender->UpdateOff();

	

	if (createDiamond == true)
	{
		My_Ptr<Actor> smoke = GetScene()->CreateActor(L"SMOKE");

		Vector4 smokePos = { GetActor()->GetTransform()->GetLocalPosition() };
		smokePos.z = __UI;



		smoke->GetTransform()->SetLocalPosition(smokePos);
		smoke->GetTransform()->LocalScaleMultiple(0.45f);
		My_Ptr<SpriteRenderer> smokeRender = smoke->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
		smokeRender->SetSprite(L"smoke.png");

		My_Ptr<SpriteAnimation> smokeAni = smoke->AddComponent<SpriteAnimation>();
		smokeAni->CreateAnimation(L"smoke", L"smoke.png", 0, 20, 0.06f, false);


		My_Ptr<Actor> coin = GetScene()->CreateActor(L"Coin");
		coin->SetGoopy(GetActor()->GetGoopy());

		coin->GetTransform()->SetLocalScale({ 72.0f / GameWindow::Inst()->GetWindowSize().y , 72.0f / GameWindow::Inst()->GetWindowSize().y });
		coin->GetTransform()->LocalScaleMultiple(GameWindow::Inst()->GetWindowSize().y / 100.0f);
		Vector4 coinpos = GetActor()->GetTransform()->GetLocalPosition();
		coinpos.z = __UI;
		coin->GetTransform()->SetLocalPosition(coinpos);


		My_Ptr<SpriteRenderer> spriteRenderer = coin->AddComponent<SpriteRenderer>(RENDERGROUP::RG_COIN);
		spriteRenderer->SetSprite(L"money.png");

		My_Ptr<SpriteAnimation> spriteAnimation = coin->AddComponent<SpriteAnimation>();


		spriteAnimation->CreateAnimation(L"Level4", L"money.png", 30, 39, 0.08f, true);


		My_Ptr < BoundingSphere> collider = coin->AddComponent<BoundingSphere>(COLGROUP::CG_COIN);
		collider->MultipleRadius(0.5f);


		coin->AddComponent<CoinMove>();

		CoinList::PushCoin(coin);

		createDiamond = false;
		isAmpOn = false;
	}


	if (spriteAnimaion->GetCurAni()->aniEnd == true)
	{
		
		if (pos.y < -windowSize.y + 0.5f)
		{
			ISDie = true;
			if (spriteRenderer->GetAlphaValue().w < 0.0f)
			{
				GetActor()->Die();

				GoopyList::PopGoopy(GetActor());

				
			}

			spriteRenderer->AlphaGradationOn();

			return;
		}
	}	

	std::wstring animationName = fishName;
	animationName.append(L"Die");

	spriteAnimaion->ChangeAnimation(animationName.c_str());

	direction = {0.0f, -0.8f, 1.0f};

	GetActor()->GetTransform()->Move2D((direction* 1.0f * Time::DeltaTime()), __GOOPY);
}


//Interface
void GoopyMove::FindFood()
{
	std::list<BoundingSphere*> tempList = FoodMove::GetFoodList();
	std::list<BoundingSphere*>::iterator begin = tempList.begin();
	std::list<BoundingSphere*>::iterator end = tempList.end();

	for (auto& next : tempList)
	{
		Vector4 foodPos = next->GetTransform()->GetLocalPosition();

		//minVector = 100.0f;
		minDis.z = 0.0f;

		Vector4 tempDir = foodPos - pos;
		tempDir.z = 0.0f;

		foodMap.insert(std::map<float, BoundingSphere*>::value_type(tempDir.Distance(), next));
	}

	begin = tempList.begin();
	if (begin == end)
	{
		existFood = false;
	}
	else
	{
		existFood = true;
		if (foodMap.size() != 0)
		{
			minDis = foodMap.begin()->second->GetTransform()->GetLocalPosition() - pos;
		}
		foodMap.clear();
	}
}
void GoopyMove::FindLittleGoopy()
{
	//작은 물고기 따라다니게 해야한다.
	std::list<BoundingSphere*> tempList = GoopyList::GetLittleGoopyList();
	std::list<BoundingSphere*>::iterator begin = tempList.begin();
	std::list<BoundingSphere*>::iterator end = tempList.end();


	for (auto& next : tempList)
	{
		Vector4 foodPos = next->GetTransform()->GetLocalPosition();

		//minVector = 100.0f;
		minDis.z = 0.0f;

		Vector4 tempDir = foodPos - pos;
		tempDir.z = 0.0f;

		littleGoopyMap.insert(std::map<float, BoundingSphere*>::value_type(tempDir.Distance(), next));
	}


	begin = tempList.begin();
	if (begin == end)
	{
		existFood = false;
	}
	else
	{
		existFood = true;
		if (littleGoopyMap.size() != 0)
		{
			minDis = littleGoopyMap.begin()->second->GetTransform()->GetLocalPosition() - pos;
		}
		littleGoopyMap.clear();
	}
}
void GoopyMove::FindPirana()
{
	//작은 물고기 따라다니게 해야한다.
	std::list<BoundingSphere*> tempList = GoopyList::GetPiranaGoopyList();
	std::list<BoundingSphere*>::iterator begin = tempList.begin();
	std::list<BoundingSphere*>::iterator end = tempList.end();


	for (auto& next : tempList)
	{
		Vector4 foodPos = next->GetTransform()->GetLocalPosition();

		//minVector = 100.0f;
		minDis.z = 0.0f;

		Vector4 tempDir = foodPos - pos;
		tempDir.z = 0.0f;

		piranaGoopyMap.insert(std::map<float, BoundingSphere*>::value_type(tempDir.Distance(), next));
	}


	begin = tempList.begin();
	if (begin == end)
	{
		existFood = false;
	}
	else
	{
		existFood = true;
		if (piranaGoopyMap.size() != 0)
		{
			minDis = piranaGoopyMap.begin()->second->GetTransform()->GetLocalPosition() - pos;
		}
		piranaGoopyMap.clear();
	}
}
//void GoopyMove::FindWadsWorth()


void GoopyMove::FindWadsWorth()
{
	if (MonsterList::GetMonsterList().size() != 0)  //몬스터가있을때는 왓슨을 찾아 이동한다.
	{
		state = GOOPYSTATE::WADSWORTH;

		Vector4 wadsPos = WadsworthMove::GetPos();
		if (wadsPos == 0.0f)
		{

		}
		else
		{
			minDis.z = 0.0f;

			Vector4 tempDir = wadsPos - pos;
			tempDir.z = 0.0f;


			BoundingSphere* wadsCol = WadsworthMove::GetCollider();
			wadsMap.insert(std::map<float, BoundingSphere*>::value_type(tempDir.Distance(), wadsCol));
			
			if (MonsterList::GetMonsterList().size() == 0)
			{
				existWads = false;
			}
			else
			{
				existWads = true;
				if (wadsMap.size() != 0)
				{
					minDis = wadsMap.begin()->second->GetTransform()->GetLocalPosition() - pos;
				}
				wadsMap.clear();
			}

			if (MonsterList::GetMonsterList().size() == 0)
			{
				existWads = false;
			}
			else
			{
				existWads = true;
				if (wadsMap.size() != 0)
				{
					minDis = wadsMap.begin()->second->GetTransform()->GetLocalPosition() - pos;
				}

				wadsMap.clear();
			}
		}
	}
}

void GoopyMove::FindGumbo()
{
	if (MonsterList::GetMonsterList().size() != 0)  //몬스터가있을때는 왓슨을 찾아 이동한다.
	{
		state = GOOPYSTATE::GUMBO;

		Vector4 gumboPos = GumboMove::GetPos();
		if (gumboPos == 0.0f)
		{

		}
		else
		{
			minDis.z = 0.0f;

			Vector4 tempDir = gumboPos - pos;
			tempDir.z = 0.0f;


			BoundingSphere* gumboCol = GumboMove::GetCollider();
			gumboMap.insert(std::map<float, BoundingSphere*>::value_type(tempDir.Distance(), gumboCol));

			if (MonsterList::GetMonsterList().size() == 0)
			{
				existGumbo = false;
			}
			else
			{
				existGumbo = true;
				if (gumboMap.size() != 0)
				{
					minDis = gumboMap.begin()->second->GetTransform()->GetLocalPosition() - pos;
				}
				gumboMap.clear();
			}

			if (MonsterList::GetMonsterList().size() == 0)
			{
				existGumbo = false;
			}
			else
			{
				existGumbo = true;
				if (gumboMap.size() != 0)
				{
					minDis = gumboMap.begin()->second->GetTransform()->GetLocalPosition() - pos;
				}

				gumboMap.clear();
			}
		}
	}
}

void GoopyMove::WadsWorth()
{
	ChangeAnimation();

	hungryTime = HUNGRYTIME;
	deadTime = 10.0f;
	isHungry = false;

	
	ChangeDir();

	moveSpeed += 0.2f + Time::DeltaTime();
	MoveGoopy(moveSpeed);

	if (MonsterList::GetMonsterList().size() == 0)
	{
		state = GOOPYSTATE::MOVING;
	}
}

void GoopyMove::Gumbo()
{
	ChangeAnimation();

	hungryTime = HUNGRYTIME;
	deadTime = 10.0f;
	isHungry = false;

	ChangeDir();

	moveSpeed += 0.2f + Time::DeltaTime();
	MoveGoopy(moveSpeed);

	if (MonsterList::GetMonsterList().size() == 0)
	{
		state = GOOPYSTATE::MOVING;
	}

}
void GoopyMove::Rhubarb()
{
	rhubarbTime -= Time::DeltaTime();

	if (rhubarbTime < 0.0f)
	{
		rhubarbTime = 1.0f;
		rhubarbMoveSpeed = 1.5f;
		state = GOOPYSTATE::STOP;
	}

	rhubarbMoveSpeed += 0.02f;
	GetActor()->GetTransform()->Move2D((Vector4::UP * rhubarbMoveSpeed * Time::DeltaTime()), __GOOPY);
}




//BASE
void GoopyMove::ChangeDir()
{
	switch (DIR)
	{
		case GoopyMove::LEFT:
		{
			direction = minDis.ReturnNormalization();

			if (direction.x < 0.0f)
			{
				spriteRenderer->TurnLeft();
			}
			else if (direction.x > 0.0f)
			{
				state = GOOPYSTATE::STOP;
			}
			break;
		}
		case GoopyMove::RIGHT:
		{
			direction = minDis.ReturnNormalization();

			if (direction.x < 0.0f)
			{
				//spriteRenderer->TurnLeft();
				state = GOOPYSTATE::STOP;
			}
			else if (direction.x > 0.0f)
			{
				spriteRenderer->TurnRight();
			}
			break;
		}
	}
}
void GoopyMove::MoveGoopy(float _Speed)
{
	moveSpeed = _Speed;

	if (pos.x > windowSize.x - 0.3f)
	{
		direction.x = 0.0f;
		GetActor()->GetTransform()->SetPosition({ windowSize.x - 0.3f, pos.y });
		GetActor()->GetTransform()->Move2D((direction * moveSpeed * Time::DeltaTime()), __GOOPY);

		if (pos.y > windowSize.y - 1.2f)
		{
			direction.y = 0.0f;
			GetActor()->GetTransform()->SetPosition({ windowSize.x - 0.3f, windowSize.y - 1.2f });
		}
		else if (pos.y < -windowSize.y + 0.5f)
		{
			direction.y = 0.0f;
			GetActor()->GetTransform()->SetPosition({ windowSize.x - 0.3f, -windowSize.y + 0.5f });
		}
	}
	else if (pos.x < -windowSize.x + 0.3f)
	{
		direction.x = 0.0f;
		GetActor()->GetTransform()->SetPosition({ -windowSize.x + 0.3f, pos.y });
		GetActor()->GetTransform()->Move2D((direction * moveSpeed * Time::DeltaTime()), __GOOPY);

		if (pos.y > windowSize.y - 1.2f)
		{
			direction.y = 0.0f;
			GetActor()->GetTransform()->SetPosition({ -windowSize.x + 0.3f, windowSize.y - 1.2f });
		}
		else if (pos.y < -windowSize.y + 0.5f)
		{
			direction.y = 0.0f;
			GetActor()->GetTransform()->SetPosition({ -windowSize.x + 0.3f, -windowSize.y + 0.5f });
		}
	}
	else if (pos.y > windowSize.y - 1.2f)
	{
		direction.y = 0.0f;
		GetActor()->GetTransform()->SetPosition({ pos.x, windowSize.y - 1.2f });
		GetActor()->GetTransform()->Move2D((direction * moveSpeed * Time::DeltaTime()), __GOOPY);

		if (pos.x > windowSize.x - 0.3f)
		{
			direction.x = 0.0f;
			GetActor()->GetTransform()->SetPosition({ windowSize.x - 0.3f, windowSize.y - 1.2f });
		}
		else if (pos.x < -windowSize.x + 0.3f)
		{
			direction.x = 0.0f;
			GetActor()->GetTransform()->SetPosition({ -windowSize.x + 0.3f, windowSize.y - 1.2f });
		}
	}
	else if (pos.y < -windowSize.y + 0.5f)
	{
		direction.y = 0.0f;
		GetActor()->GetTransform()->SetPosition({ pos.x, -windowSize.y + 0.5f });
		GetActor()->GetTransform()->Move2D((direction * moveSpeed * Time::DeltaTime()), __GOOPY);

		if (pos.x > windowSize.x - 0.3f)
		{
			direction.x = 0.0f;
			GetActor()->GetTransform()->SetPosition({ windowSize.x - 0.3f,-windowSize.y + 0.5f });
		}
		else if (pos.x < -windowSize.x + 0.3f)
		{
			direction.x = 0.0f;
			GetActor()->GetTransform()->SetPosition({ -windowSize.x + 0.3f, -windowSize.y + 0.5f });
		}
	}
	else
	{
		GetActor()->GetTransform()->Move2D((direction * moveSpeed * Time::DeltaTime()), __GOOPY);
	}
}
void GoopyMove::ChangeAnimation()
{
	//if (state == GOOPYSTATE::EATING)
	//{
	//	
	//}



	if (isHungry == false)
	{
		std::wstring tempSwim; //= fishName + L"Swim";
		if (isFast == true)
		{
			tempSwim = fishName + L"Swimfast";
		}
		else
		{
			tempSwim = fishName + L"Swim";
		}
		spriteAnimaion->ChangeAnimation(tempSwim.c_str());
	}
	else
	{
		std::wstring tempSwim; //= fishName + L"Swim";
		if (isFast == true)
		{
			tempSwim = fishName + L"SwimfastHungry";
		}
		else
		{
			tempSwim = fishName + L"SwimHungry";
		}
		spriteAnimaion->ChangeAnimation(tempSwim.c_str());
	}
}


//COLLIDER

void GoopyMove::Enter(Collider* _This, Collider* _Other)
{

	switch (_Other->GetOrder())
	{
	case COLGROUP::CG_FOOD:
		{
			if (state == GOOPYSTATE::HUNGRY )
			{
				Sound::Play(L"SLURP.wav");
				point += FoodMove::GetFoodPoint();

				FoodMove::PopFoodActor(_Other);
				Actor* foodActor = _Other->GetActor();
				FoodList::PopFood(foodActor);
				FoodList::PopFood(_Other->GetActor());

				_Other->Die();		//충돌체를 꺼준다

				_Other->GetActor()->Die();
				_Other = nullptr;
				hungryTime = HUNGRYTIME;
				isHungry = false;
				state = GOOPYSTATE::EATING;
			}			
		}
		break;

	

	case COLGROUP::CG_LITTLEGOOPY:
		{
			if (state == GOOPYSTATE::HUNGRY)
			{
				Sound::Play(L"chomp.wav");
				chomp = GetScene()->CreateActor(L"Chomp");
				My_Ptr<SpriteRenderer> chompRender = chomp->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
				chompRender->SetSprite(L"chomp.png");
				Vector4 pos = { _Other->GetTransform()->GetLocalPosition() };
				
				pos.z = __UI;
				chompRender->GetTransform()->SetLocalPosition(pos);
				chompRender->GetTransform()->LocalScaleMultiple(0.45f);
				chompAni = chomp->AddComponent<SpriteAnimation>();
				chompAni->CreateAnimation(L"chomp", L"chomp.png", 0, 5, 0.1f, false);



				GoopyList::PopGoopy(_Other->GetActor());

				_Other->Die();				
				_Other->GetActor()->Die();
				_Other = nullptr;

				hungryTime = HUNGRYTIME;
				isHungry = false;
				state = GOOPYSTATE::EATING;

				//물고기 죽는 이미지 넣어준다
				//작은물고기를 죽인다.
			}
		}
		break;


	case COLGROUP::CG_PIRANA:
		{
			if (state == GOOPYSTATE::HUNGRY)
			{
				Sound::Play(L"chomp.wav");
				chomp = GetScene()->CreateActor(L"Chomp");
				My_Ptr<SpriteRenderer> chompRender = chomp->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
				chompRender->SetSprite(L"chomp.png");
				Vector4 pos = { _Other->GetTransform()->GetLocalPosition() };

				pos.z = __UI;
				chompRender->GetTransform()->SetLocalPosition(pos);
				chompRender->GetTransform()->LocalScaleMultiple(0.45f);
				chompAni = chomp->AddComponent<SpriteAnimation>();
				chompAni->CreateAnimation(L"chomp", L"chomp.png", 0, 5, 0.1f, false);

				GoopyList::PopGoopy(_Other->GetActor());


				_Other->Die();
				_Other->GetActor()->Die();
				_Other = nullptr;

				hungryTime = HUNGRYTIME;
				isHungry = false;
				state = GOOPYSTATE::EATING;
			}
		}
		break;

	case COLGROUP::CG_RHUBARB:
	{
		state = RHUBARB;
	}
	break;

	case COLGROUP::CG_PUNCH:
	{
		CreateCoin* CreateLogic = GetActor()->GetComponent<CreateCoin>();
		CreateLogic->SetCreateTime(-1.0f);
	}
	break;

	case COLGROUP::CG_COIN:
	{
		CoinMove* coinMove = _Other->GetActor()->GetComponent<CoinMove>();
		if (coinMove->GetIsBomb() == true)
		{
			deadTime = -1.0f;
			hungryTime = -1.0f;

			_Other->GetActor()->Die();

			My_Ptr<Actor> smoke = GetScene()->CreateActor(L"SMOKE");

			Vector4 pos = { GetActor()->GetTransform()->GetLocalPosition() };
			pos.z = __UI + (0.1f);

			//pos.x += Well512Random::Instance().GetFloatValue(-0.5f, 0.5f);
			//pos.y += Well512Random::Instance().GetFloatValue(-0.5f, 0.5f);

			smoke->GetTransform()->SetLocalPosition(pos);
			smoke->GetTransform()->LocalScaleMultiple(0.45f);
			My_Ptr<SpriteRenderer> smokeRender = smoke->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
			smokeRender->SetSprite(L"smoke.png");

			My_Ptr<SpriteAnimation> smokeAni = smoke->AddComponent<SpriteAnimation>();
			smokeAni->CreateAnimation(L"smoke", L"smoke.png", 0, 20, 0.06f, false);

			coinMove->BombOff();
		}
		

	}
	break;

	}
}

void GoopyMove::Stay(Collider* _This, Collider* _Other)
{
	switch (_Other->GetOrder())
	{
	case COLGROUP::CG_FOOD:
	{
		if (state == GOOPYSTATE::HUNGRY)
		{
			Sound::Play(L"SLURP.wav");
			point += FoodMove::GetFoodPoint();

			FoodMove::PopFoodActor(_Other);

			FoodList::PopFood(_Other->GetActor());

			_Other->Die();		//충돌체를 꺼준다

			_Other->GetActor()->Die();
			_Other = nullptr;
			hungryTime = HUNGRYTIME;
			isHungry = false;
			state = GOOPYSTATE::EATING;
		}
	}
	break;

	case COLGROUP::CG_LITTLEGOOPY:
	{
		if (state == GOOPYSTATE::HUNGRY)
		{
			Sound::Play(L"chomp.wav");
			chomp = GetScene()->CreateActor(L"Chomp");
			My_Ptr<SpriteRenderer> chompRender = chomp->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
			chompRender->SetSprite(L"chomp.png");
			Vector4 pos = { _Other->GetTransform()->GetLocalPosition() };

			pos.z = __UI;
			chompRender->GetTransform()->SetLocalPosition(pos);
			chompRender->GetTransform()->LocalScaleMultiple(0.45f);
			chompAni = chomp->AddComponent<SpriteAnimation>();
			chompAni->CreateAnimation(L"chomp", L"chomp.png", 0, 5, 0.1f, false);



			GoopyList::PopGoopy(_Other->GetActor());

			_Other->Die();
			_Other->GetActor()->Die();
			_Other = nullptr;

			hungryTime = HUNGRYTIME;
			isHungry = false;
			state = GOOPYSTATE::EATING;

			//물고기 죽는 이미지 넣어준다
			//작은물고기를 죽인다.
		}
	}
	break;


	case COLGROUP::CG_PIRANA:
	{
		if (state == GOOPYSTATE::HUNGRY)
		{
			Sound::Play(L"chomp.wav");
			chomp = GetScene()->CreateActor(L"Chomp");
			My_Ptr<SpriteRenderer> chompRender = chomp->AddComponent<SpriteRenderer>(RENDERGROUP::RG_UI);
			chompRender->SetSprite(L"chomp.png");
			Vector4 pos = { _Other->GetTransform()->GetLocalPosition() };

			pos.z = __UI;
			chompRender->GetTransform()->SetLocalPosition(pos);
			chompRender->GetTransform()->LocalScaleMultiple(0.45f);
			chompAni = chomp->AddComponent<SpriteAnimation>();
			chompAni->CreateAnimation(L"chomp", L"chomp.png", 0, 5, 0.1f, false);

			GoopyList::PopGoopy(_Other->GetActor());

			_Other->Die();
			_Other->GetActor()->Die();
			_Other = nullptr;

			hungryTime = HUNGRYTIME;
			isHungry = false;
			state = GOOPYSTATE::EATING;
		}
	}
	break;

	case COLGROUP::CG_WADSWORTH:
	{

		int kinds = _This->GetActor()->GetGoopy();

		if (kinds == 0 || kinds == 1)
		{
			if (MonsterList::GetMonsterList().size() != 0)
			{
				spriteRenderer->UpdateOff();
				collider->UpdateOff();

				Actor* actor = GetActor();

				if (actor != nullptr)
				{
					GoopyList::PushWadsGoopy(actor);
				}
				
			}
		}

	}
	break;

	case COLGROUP::CG_ANGIE:
	{
		if (state == GOOPYSTATE::DIE && ISDie == false)
		{
			Sound::Play(L"HEAL.wav");
			state = GOOPYSTATE::STOP;
			deadTime = 10.0f;
			hungryTime = 10.0f;
			isHungry = false;			
			soundDie = true;
		}
	}
	break;

	case COLGROUP::CG_RHUBARB:
	{
		state = RHUBARB;
	}
	break;

	case COLGROUP::CG_PUNCH:
		{		
			Vector4 thisVector = pos;
			Vector4 OtherVector = _Other->GetActor()->GetTransform()->GetLocalPosition();

			Vector4 pDir = OtherVector- thisVector ;
			pDir.y  = 0.0f;
			pDir.z  = 0.0f;
			pDir.x *= -1.0f;
			   
			GetActor()->GetTransform()->Move2D((direction * 2.0 * Time::DeltaTime()), __GOOPY);		
		}
	break;
	}
}

void GoopyMove::Exit(Collider* _This, Collider* _Other)
{
	int a = 0;
}

