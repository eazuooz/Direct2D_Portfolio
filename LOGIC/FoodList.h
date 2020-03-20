#pragma once
#include <list>
#include <Actor.h>

class FoodList
{
private:
	static std::list<Actor*> foodList;
	static std::list<Actor*>::iterator foodBegin;
	static std::list<Actor*>::iterator foodEnd;

public:
	static std::list<Actor*> GetFoodList()
	{
		return foodList;
	}

public:
	static void FoodList_Update();
	static void PushFood(Actor* _Actor);
	static void PopFood(Actor* _Actor);

public:
	FoodList();
	~FoodList();
};

