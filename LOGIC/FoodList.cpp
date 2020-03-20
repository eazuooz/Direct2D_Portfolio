#include "FoodList.h"


#include "FoodMove.h"

std::list<Actor*> FoodList::foodList;
std::list<Actor*>::iterator FoodList::foodBegin;
std::list<Actor*>::iterator FoodList::foodEnd;


FoodList::FoodList()
{
}


FoodList::~FoodList()
{
}


void FoodList::FoodList_Update()
{

}
void FoodList::PushFood(Actor* _Actor)
{
	foodList.push_back(_Actor);
}
void FoodList::PopFood(Actor* _Actor)
{
	foodBegin = foodList.begin();
	foodEnd = foodList.end();

	for (; foodBegin != foodEnd;)
	{
		if ((*foodBegin) == _Actor)
		{
			foodBegin = foodList.erase(foodBegin);
		}
		else
		{
			++foodBegin;
		}
	}
}


