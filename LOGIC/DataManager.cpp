#include "DataManager.h"


std::list<Actor*> DataManager::foodList;
DataManager::DataManager()
{
}


DataManager::~DataManager()
{
}

void DataManager::PushFoodActor(Actor* _Actor)
{
	if (nullptr == _Actor)
	{
		//BOOM;
	}

	foodList.push_back(_Actor);
}

void DataManager::PopFoodActor()
{
	
}
