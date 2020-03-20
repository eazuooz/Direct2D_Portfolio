#pragma once
#include <Logic.h>
//#include <Collider.h>


class BoundingSphere;
class SpriteRenderer;
class FoodMove : public Logic
{
private:
	static std::list<BoundingSphere*> foodList;
	static std::list<BoundingSphere*>::iterator begin;
	static std::list<BoundingSphere*>::iterator end;

public:
	static void PushFoodActor(BoundingSphere* _Actor);
	static void PopFoodActor(const BoundingSphere* _Actor);
	static void PopFoodActor(const Collider* _Actor);

public:
	static std::list<BoundingSphere*> GetFoodList()
	{
		return foodList;
	}
	static int GetFoodListSize()
	{
		return (int)foodList.size();
	}


private:
	static int foodPoint;

public:
	static void SetFoodPoint(int _Value)
	{
		foodPoint = _Value;
	}
	static int GetFoodPoint()
	{
		return foodPoint;
	}

private:
	Vector4 pos;
	Vector4 direction;
	SpriteRenderer* spriteRenderer;
	BoundingSphere* collider;

private:
	float nimbusTime;
	float nimbusMoveSpeed;
	bool isNimbus;

public:
	void Init()		override;
	void Update()	override;


public:
	void Enter(Collider* _This, Collider* _Other);
	void Stay(Collider* _This, Collider* _Other);
	void Exit(Collider* _This, Collider* _Other);

public:
	FoodMove();
	~FoodMove();
};

