#pragma once
#include <Actor.h>
#include <BoundingSphere.h>

class MonsterList
{
public:
	static int ailenPetCnt;

private:
	static std::list<Actor*> monsterList;
	static std::list<Actor*>::iterator monsterBegin;
	static std::list<Actor*>::iterator monsterEnd;

public:
	static std::list<Actor*> GetMonsterList()
	{
		return monsterList;
	}

public:
	static void MonsterList_Update();
	static void PushMonster(Actor* _Actor);
	static void PopMonster(Actor* _Actor);

public:
	MonsterList();
	~MonsterList();
};

