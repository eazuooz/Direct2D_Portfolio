#include "MonsterList.h"


int MonsterList::ailenPetCnt = 0;

std::list<Actor*> MonsterList::monsterList;
std::list<Actor*>::iterator MonsterList::monsterBegin;
std::list<Actor*>::iterator MonsterList::monsterEnd;


MonsterList::MonsterList()
{
}


MonsterList::~MonsterList()
{
}

void MonsterList::MonsterList_Update()
{

}

void MonsterList::PushMonster(Actor* _Actor)
{
	if (nullptr == _Actor)
	{
		BOOM;
		return;
	}

	monsterList.push_back(_Actor);
}

void MonsterList::PopMonster(Actor* _Actor)
{
	monsterBegin = monsterList.begin();
	monsterEnd = monsterList.end();

	for (; monsterBegin != monsterEnd;)
	{
		if ((*monsterBegin) == _Actor)
		{
			monsterBegin = monsterList.erase(monsterBegin);
		}
		else
		{
			++monsterBegin;
		}
	}
}

