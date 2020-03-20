#include "WadsworthMove.h"

#include "MonsterList.h"
#include "GoopyList.h"
#include "PetList.h"

Vector4 WadsworthMove::returnPos = { 0.0f,0.0f,0.0f,0.0f };
BoundingSphere* WadsworthMove::collider;
bool WadsworthMove::isExist = false;

WadsworthMove::WadsworthMove() : isClose(false),skillEnd(false), closeTime(2.5f)
{
}


WadsworthMove::~WadsworthMove()
{
}

void WadsworthMove::Init()
{
	isExist = true;
	InitResource();

	collider = GetActor()->GetComponent<BoundingSphere>();

	PetList::existWads = true;
}

void WadsworthMove::Update()
{
	if (MonsterList::GetMonsterList().size() != 0)
	{
		if(isClose == false)
		{
			state = STATE::SKILL;
		}
		else
		{
			
		}
	}
	else //
	{
		if (skillEnd == true)
		{
			state = STATE::SKILL2;
		}
		else
		{
			if (isClose == true)
			{
				state = STATE::SKILL;
			}
		}



		//if (skillEnd == true)
		//{
		//	state = STATE::SKILL2;
		//}

	}


	pos = GetActor()->GetTransform()->GetLocalPosition();
	returnPos = pos;
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

	switch (state)
	{
	case STATE::MOVING:
	{
		InterMoving();
	}
	break;
	case STATE::STOP:
	{
		Stop();
	}
	break;
	case STATE::SKILL:
	{
		OpenMouth();
	}
	break;
	case STATE::SKILL2:
	{
		CloseMouth();
	}
	break;
	}
}


void WadsworthMove::OpenMouth()
{
	if (isClose == false)
	{
		closeTime -= Time::DeltaTime();

		if (closeTime < 0.0f)
		{
			state = STATE::SKILL2;
			isClose = true;

			std::wstring aniName = fishName + L"Close";
			spriteAnimaion->ChangeAnimation(aniName.c_str());

			closeTime = 2.5f;
		}

		//GoopyList::GoopyList_Update();
		//int curWadsGoopyCnt = (int)GoopyList::GetWadsGoopyList().size();



		/*if (GoopyList::GetWadsGoopyCnt() == curWadsGoopyCnt)
		{
		return;
		}*/
	}
	else // isclose == true
	{
		if (spriteAnimaion->GetCurAni()->aniEnd == true)
		{
			Vector4 wadsPos = GetActor()->GetTransform()->GetLocalPosition();
			GoopyList::SetPosWadsGoopy(wadsPos);
			GoopyList::GoopyWadsList_UpdateOn();

			state = STATE::SKILL2;
			skillEnd = true;

			std::wstring aniName = fishName + L"Close";
			spriteAnimaion->ChangeAnimation(aniName.c_str());

			return;
		}
	}


	std::wstring aniName = fishName + L"Open";
	spriteAnimaion->ChangeAnimation(aniName.c_str());
	Move(0.25);
}


void WadsworthMove::CloseMouth()
{

	if (spriteAnimaion->GetCurAni()->aniEnd == true)
	{
		state = STATE::STOP;

		if (skillEnd == true)
		{
			Vector4 wadsPos = GetActor()->GetTransform()->GetLocalPosition();

			skillEnd = false;
			isClose = false;
		}


		std::wstring tempSwim = fishName + L"Swim";
		spriteAnimaion->ChangeAnimation(tempSwim.c_str());
	}



	Move(0.25);
}