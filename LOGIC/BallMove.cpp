#include "BallMove.h"
#include <list>

#include "ENUM.h"
#include "MonsterList.h"

BallMove::BallMove()
{
}


BallMove::~BallMove()
{
}


void BallMove::Init()
{
	std::list<Actor*> tempList;


	tempList = MonsterList::GetMonsterList();
	std::list<Actor*>::iterator begin = tempList.begin();
	std::list<Actor*>::iterator end = tempList.end();


	Actor* monster = nullptr;
	for (; begin != end; ++begin)
	{
		monster = (*begin);
	}

	

	Vector4 myVec = GetActor()->GetTransform()->GetLocalPosition();
	Vector4 destVec = monster->GetTransform()->GetLocalPosition();

	monsterDir = destVec - myVec;
	monsterDir.Normalization();
}

void BallMove::Update()
{
	GetActor()->GetTransform()->Move2D((monsterDir * 7.0f * Time::DeltaTime()), __PET);
}