#include "GoopyList.h"
#include <SpriteRenderer.h>
#include <BoundingSphere.h>

#include "FishMove.h"
#include "ENUM.h"
int GoopyList::wadsGoopyCnt = 0;

std::list<BoundingSphere*> GoopyList::littleGoopyList;
std::list<BoundingSphere*>::iterator GoopyList::littleGoopyBegin;
std::list<BoundingSphere*>::iterator GoopyList::littleGoopyEnd;

std::list<BoundingSphere*> GoopyList::piranaGoopyList;
std::list<BoundingSphere*>::iterator GoopyList::piranaGoopyBegin;
std::list<BoundingSphere*>::iterator GoopyList::piranaGoopyEnd;

std::list<Actor*> GoopyList::goopyList;
std::list<Actor*>::iterator GoopyList::goopyBegin;
std::list<Actor*>::iterator GoopyList::goopyEnd;

std::list<Actor*> GoopyList::wadsGoopyList;
std::list<Actor*>::iterator GoopyList::wadsGoopyBegin;
std::list<Actor*>::iterator GoopyList::wadsGoopyEnd;

GoopyList::GoopyList()
{
}


GoopyList::~GoopyList()
{
}

///////////
void GoopyList::LittleGoopyList_Update()
{
	//goopyList.clear();

	goopyBegin = goopyList.begin();
	goopyEnd = goopyList.end();


	littleGoopyList.clear();
	for (; goopyBegin != goopyEnd; ++goopyBegin)
	{
		int kinds = (*goopyBegin)->GetGoopy();

		if (kinds == 0)
		{
			BoundingSphere* collider = nullptr;
				
			collider = (*goopyBegin)->GetComponent<BoundingSphere>();			
			PushLittleGoopy(collider);
		}
	}
}

void GoopyList::PushLittleGoopy(BoundingSphere* _Collider)
{
	littleGoopyList.push_back(_Collider);
}

void GoopyList::PopLittleGoopy(const BoundingSphere* _Collider)
{
	littleGoopyBegin = littleGoopyList.begin();
	littleGoopyEnd = littleGoopyList.end();

	for (; littleGoopyBegin != littleGoopyEnd;)
	{
		if ((*littleGoopyEnd) == _Collider)
		{
			littleGoopyBegin = littleGoopyList.erase(littleGoopyBegin);
		}
		else
		{
			++littleGoopyBegin;
		}
	}
}

void GoopyList::PopLittleGoopy(const Collider* _Collider)
{
	littleGoopyList.push_back((BoundingSphere*)_Collider);
}

/////////////

void GoopyList::PiranaGoopyList_Update()
{
	goopyBegin = goopyList.begin();
	goopyEnd = goopyList.end();


	piranaGoopyList.clear();
	for (; goopyBegin != goopyEnd; ++goopyBegin)
	{
		int kinds = (*goopyBegin)->GetGoopy();

		if (kinds == 4)
		{
			BoundingSphere* collider = nullptr;

			collider = (*goopyBegin)->GetComponent<BoundingSphere>();
			PushPiranaGoopy(collider);
		}
	}
}
void GoopyList::PushPiranaGoopy(BoundingSphere* _Collider)
{
	piranaGoopyList.push_back(_Collider);
}
void GoopyList::PopPiranaGoopy(const BoundingSphere* _Collider)
{
	piranaGoopyBegin = piranaGoopyList.begin();
	piranaGoopyEnd = piranaGoopyList.end();

	for (; piranaGoopyBegin != piranaGoopyEnd;)
	{
		if ((*piranaGoopyBegin) == _Collider)
		{
			piranaGoopyBegin = piranaGoopyList.erase(piranaGoopyBegin);
		}
		else
		{
			++piranaGoopyBegin;
		}
	}
}
void GoopyList::PopPiranaGoopy(const Collider* _Collider)
{
	PopPiranaGoopy((BoundingSphere*)_Collider);
}

//////////////

void GoopyList::GoopyList_Update()
{
	LittleGoopyList_Update();
	PiranaGoopyList_Update();

	goopyBegin = goopyList.begin();
	goopyEnd = goopyList.end();


	wadsGoopyCnt = 0;
	for (; goopyBegin != goopyEnd; ++goopyBegin)
	{
		if ((*goopyBegin)->GetGoopy() == 0 || (*goopyBegin)->GetGoopy() == 1)
		{
			++wadsGoopyCnt;
		}
	}
}
void GoopyList::PushGoopy(Actor* _Actor)
{
	goopyList.push_back(_Actor);
}
void GoopyList::PopGoopy( Actor* _Actor)
{
	goopyBegin = goopyList.begin();
	goopyEnd = goopyList.end();

	for (; goopyBegin != goopyEnd;)
	{
		if ((*goopyBegin) == _Actor)
		{
			goopyBegin = goopyList.erase(goopyBegin);
		}
		else
		{
			++goopyBegin;
		}
	}


	LittleGoopyList_Update();
	PiranaGoopyList_Update();
	//My_Ptr<BoundingSphere> COL = _Actor->GetComponent<BoundingSphere>();

	//littleGoopyBegin = littleGoopyList.begin();
	//littleGoopyEnd = littleGoopyList.end();

	//for (; littleGoopyBegin != littleGoopyEnd;)
	//{
	//	if ((*littleGoopyEnd) == COL)
	//	{
	//		littleGoopyBegin = littleGoopyList.erase(littleGoopyBegin);
	//	}
	//	else
	//	{
	//		++littleGoopyBegin;
	//	}
	//}
}

void GoopyList::GoopyWadsList_UpdateOn()
{


	wadsGoopyBegin = wadsGoopyList.begin();
	wadsGoopyEnd = wadsGoopyList.end();

	for (; wadsGoopyBegin != wadsGoopyEnd; ++wadsGoopyBegin)
	{
		SpriteRenderer* spriteRender = (*wadsGoopyBegin)->GetComponent< SpriteRenderer>();
		BoundingSphere* collider = (*wadsGoopyBegin)->GetComponent< BoundingSphere>();
		


		spriteRender->UpdateOn();
		collider->UpdateOn();

		//PopWadsGoopy((*wadsGoopyBegin));
		//Vector4 actorPos =  (*wadsGoopyBegin)->GetTransform()->GetLocalPosition();
		//spriteRender->SetLocalPosition(actorPos);
		//collider->SetLocalPosition(actorPos);
	}

	wadsGoopyList.clear();
}

void GoopyList::PushWadsGoopy(Actor* _Actor)
{
	if (_Actor != nullptr)
	{
		wadsGoopyList.push_back(_Actor);
	}


}

void GoopyList::PopWadsGoopy(Actor* _Actor)
{
	wadsGoopyBegin = wadsGoopyList.begin();
	wadsGoopyEnd = wadsGoopyList.end();

	for (; wadsGoopyBegin != wadsGoopyEnd;)
	{
		if ((*wadsGoopyBegin) == _Actor)
		{
			wadsGoopyBegin = wadsGoopyList.erase(wadsGoopyBegin);
		}
		else
		{
			++wadsGoopyBegin;
		}
	}
}

void GoopyList::SetPosWadsGoopy(Vector4 _Pos)
{
	wadsGoopyBegin = wadsGoopyList.begin();
	wadsGoopyEnd = wadsGoopyList.end();


	Vector4 goopyPos = _Pos;
	goopyPos.z = __GOOPY;
	float zDepth = 0.0001f;
	

	for (; wadsGoopyBegin != wadsGoopyEnd; ++wadsGoopyBegin)
	{
		zDepth += 0.0001f;
		goopyPos.z += zDepth;
		(*wadsGoopyBegin)->GetTransform()->SetLocalPosition(goopyPos);
	}	
}

void GoopyList::WadsGoopyClear()
{
	wadsGoopyList.clear();
}