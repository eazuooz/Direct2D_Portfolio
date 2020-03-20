#pragma once
#include <list>


#include <Actor.h>

class DataManager
{
private:
	static std::list<Actor*> foodList;

public:
	static void PushFoodActor(Actor* _Actor);
	static void PopFoodActor();

public:
	DataManager();
	~DataManager();
};

