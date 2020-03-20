#include "CoinList.h"



std::list<Actor*> CoinList::coinList;
std::list<Actor*>::iterator CoinList::coinBegin;
std::list<Actor*>::iterator CoinList::coinEnd;


CoinList::CoinList()
{
}


CoinList::~CoinList()
{
}

void CoinList::CoinList_Update()
{

}

void CoinList::PushCoin(Actor* _Actor)
{
	if (nullptr == _Actor)
	{
		BOOM;
		return;
	}

	coinList.push_back(_Actor);
}

void CoinList::PopMonster(Actor* _Actor)
{
	coinBegin = coinList.begin();
	coinEnd = coinList.end();

	for (; coinBegin != coinEnd;)
	{
		if ((*coinBegin) == _Actor)
		{
			coinBegin = coinList.erase(coinBegin);
		}
		else
		{
			++coinBegin;
		}
	}
}