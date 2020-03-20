#pragma once
#include <Actor.h>
#include <BoundingSphere.h>

class CoinList
{
private:
	static std::list<Actor*> coinList;
	static std::list<Actor*>::iterator coinBegin;
	static std::list<Actor*>::iterator coinEnd;

public:
	static std::list<Actor*> GetCoinList()
	{
		return coinList;
	}

public:
	static void CoinList_Update();
	static void PushCoin(Actor* _Actor);
	static void PopMonster(Actor* _Actor);

public:
	CoinList();
	~CoinList();
};

