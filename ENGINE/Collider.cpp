#include "Collider.h"
#include "Scene.h"


Collider::Collider()
{
	SetName(L"Collider");
}


Collider::~Collider()
{
}

void Collider::CollisionCheck(Collider* _Other)
{
	//³ª¿Í ³ÊÀÇ µµÇüÀº ´ê¾Ó¤¶´Ù.

	if (true == GeometryCheck(_Other)) 
	{
		if (otherCollider_Set.end() == otherCollider_Set.find(_Other))
		{
			otherCollider_Set.insert(_Other);
			ColliderEnter(_Other);
		}
		else
		{
			ColliderStay(_Other);
		}
	}
	else
	{
		if (otherCollider_Set.end() != otherCollider_Set.find(_Other))
		{
			ColliderExit(_Other);
			otherCollider_Set.erase(_Other);
		}
	}
}

//
bool Collider::GeometryCheck(Collider* _Other)
{
	BOOM;

	return false;
}


void Collider::ColliderEnter(Collider* _Other)
{
	function_Start	= enterFunction_List.begin();
	function_End	= enterFunction_List.end();

	for (; function_Start != function_End; ++function_Start)
	{
		(*function_Start)(this, _Other);
	}

}

void Collider::ColliderStay(Collider* _Other)
{
	function_Start = stayFunction_List.begin();
	function_End = stayFunction_List.end();

	for (; function_Start != function_End; ++function_Start)
	{
		(*function_Start)(this, _Other);
	}

}

void Collider::ColliderExit(Collider* _Other)
{
	function_Start = exitFunction_List.begin();
	function_End = exitFunction_List.end();

	for (; function_Start != function_End; ++function_Start)
	{
		(*function_Start)(this, _Other);
	}

}


void Collider::Init()
{
	if (nullptr == GetActor()->GetTransform())
	{
		BOOM;
	}
	//actorName = GetActor()->GetName();
	SetParentTransform(GetActor()->GetTransform());
}

void Collider::DataCreate(int _Order )
{
	order = _Order;	
	GetScene()->colliderMgr.PushCollider(this);
}

void Collider::SceneChangeStart()
{
	GetScene()->colliderMgr.PushCollider(this);
}