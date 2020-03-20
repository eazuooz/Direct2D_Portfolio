#include "ClydeMove.h"


#include "CoinList.h"

ClydeMove::ClydeMove()
{
}


ClydeMove::~ClydeMove()
{
}

void ClydeMove::Init()
{
	InitResource();
}

void ClydeMove::Update()
{
	pos = GetActor()->GetTransform()->GetLocalPosition();
	if (direction.x < 0.0f)
	{
		DIR = DIRECTION::LEFT;
	}
	else if (direction.x > 0.0f)
	{
		DIR = DIRECTION::RIGHT;
	}
	else //0.0f 일때는 그냥 그대로
	{
		//
	}

	if (CoinList::GetCoinList().size() > 0)
	{
		std::list<Actor*> tempList = CoinList::GetCoinList();
		std::list<Actor*>::iterator begin = tempList.begin();
		std::list<Actor*>::iterator end = tempList.end();

		for (auto& next : tempList)
		{
			Vector4 coinPos = next->GetTransform()->GetLocalPosition();

			//minVector = 100.0f;
			minDis.z = 0.0f;

			Vector4 tempDir = coinPos - pos;
			tempDir.z = 0.0f;

			findDestMap.insert(std::map<float, Actor*>::value_type(tempDir.Distance(), next));
		}

		begin = tempList.begin();
		if (begin == end)
		{
			isInterchange = false;
		}
		else
		{
			isInterchange = true;
			minDis = findDestMap.begin()->second->GetTransform()->GetLocalPosition() - pos;
			findDestMap.clear();
			interMoveSpeed = 5.0f;
		}
	}
	else
	{
		isInterchange = false;
	}




	switch (state)
	{
	case STATE::MOVING:
		InterMoving();
		break;
	case STATE::STOP:
		Stop();
		break;
	}
}

