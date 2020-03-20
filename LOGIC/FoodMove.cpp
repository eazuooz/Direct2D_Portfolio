#include "FoodMove.h"

#include <SpriteRenderer.h>
#include <BoundingSphere.h>

#include "ENUM.h"
#include "DataManager.h"
#include "FoodList.h"


#define FOODSPEED 0.5f


std::list<BoundingSphere*> FoodMove::foodList;
std::list<BoundingSphere*>::iterator FoodMove::begin;
std::list<BoundingSphere*>::iterator FoodMove::end;
int FoodMove::foodPoint = 5;
FoodMove::FoodMove() : direction({0.0f, -1.0f, -4.0f}), nimbusTime(1.0f), nimbusMoveSpeed(1.0f)
{
}


FoodMove::~FoodMove()
{
}

void FoodMove::PushFoodActor(BoundingSphere* _Actor)
{
	foodList.push_back(_Actor);
}


void FoodMove::PopFoodActor(const BoundingSphere* _Actor)
{
	begin = foodList.begin();
	end = foodList.end();

	for (; begin != end;)
	{
		if ((*begin) == _Actor)
		{			
			begin = foodList.erase(begin);
			//(*begin) = nullptr;
		}
		else
		{
			++begin;
		}
	}
}
void FoodMove::PopFoodActor(const Collider* _Actor)
{
	PopFoodActor((BoundingSphere*)_Actor);
}

void FoodMove::Init()
{
	spriteRenderer = GetActor()->GetComponent<SpriteRenderer>();
	collider = GetActor()->GetComponent<BoundingSphere>();

	

	collider->RegisterEnterFunction(&FoodMove::Enter, this);
	collider->RegisterStayFunction(&FoodMove::Stay, this);
	collider->RegisterExitFunction(&FoodMove::Exit, this);
}

void FoodMove::Update()
{
	foodList;

	if (GetActor()->GetTransform()->GetPosition().y < -2.0f)
	{
		if (nullptr != collider)
		{
			PopFoodActor(collider);
			collider->Die();		//충돌체를 꺼준다
			collider = nullptr;			

			Actor* foodActor = GetActor();
			FoodList::PopFood(foodActor);

			BoundingSphere* col = foodActor->GetComponent<BoundingSphere>();
			FoodMove::PopFoodActor(col);
		}

		if (spriteRenderer->GetAlphaValue().w < 0.0f)
		{			
			GetActor()->Die();
				//엑터 사라진다		
		}

		spriteRenderer->AlphaGradationOn();
		return;
	}


	if (isNimbus == true)
	{
		nimbusTime -= Time::DeltaTime();
		if (nimbusTime < 0.0f)
		{
			nimbusTime = 1.0f;
			nimbusMoveSpeed = 1.0f;
			isNimbus = false;
		}
	}


	if (isNimbus == false)
	{
		GetActor()->GetTransform()->Move2D((direction * FOODSPEED * Time::DeltaTime()), __FOOD);
	}
	else
	{
		nimbusMoveSpeed += 0.02f;
		GetActor()->GetTransform()->Move2D((Vector4::UP * nimbusMoveSpeed * Time::DeltaTime()), __FOOD);
	}

	
	pos = GetActor()->GetTransform()->GetLocalPosition();
}


void FoodMove::Enter(Collider* _This, Collider* _Other)
{
	isNimbus = true;
}

void FoodMove::Stay(Collider* _This, Collider* _Other)
{

}

void FoodMove::Exit(Collider* _This, Collider* _Other)
{

}