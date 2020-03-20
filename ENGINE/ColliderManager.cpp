#include "ColliderManager.h"
#include "Collider.h"

#pragma region COLLIDERGROUP
void ColliderManager::ColliderGroup::Circulate_ColliderGroup() 
{
	otherGroup_Start = coliiderGroup_List.begin();
	otherGroup_End = coliiderGroup_List.end();

	for (; otherGroup_Start != otherGroup_End; ++otherGroup_Start)
	{
		if (this != *otherGroup_Start)
		{
			Circulate_OtherGroupCollider(*otherGroup_Start);		//다른 충돌체와 충돌할떄
		}
		else
		{
			Circulate_ThisGroupCollider();					//나랑 충돌할떄
		}
	}
}

void ColliderManager::ColliderGroup::Circulate_OtherGroupCollider(ColliderGroup* _OtherGroup)
{
	thisCollider_Start = collider_List.begin();
	thisCollider_End = collider_List.end();

	for (; thisCollider_Start != thisCollider_End; ++thisCollider_Start)
	{
		if (false == (*thisCollider_Start)->IsUpdate())
		{
			continue;
		}

		otherCollider_Start	= _OtherGroup->collider_List.begin();
		otherCollider_End		= _OtherGroup->collider_List.end();

		for (; otherCollider_Start != otherCollider_End; ++otherCollider_Start)
		{
			if (false == (*otherCollider_Start)->IsUpdate())
			{
				continue;
			}

			(*thisCollider_Start)->CollisionCheck((*otherCollider_Start));
		}
	}

}

void ColliderManager::ColliderGroup::Circulate_ThisGroupCollider()
{
	thisCollider_Start = collider_List.begin();
	thisCollider_End = collider_List.end();

	for (; thisCollider_Start != thisCollider_End; ++thisCollider_Start)
	{
		if (false == (*thisCollider_Start)->IsUpdate())
		{
			continue;
		}

		otherCollider_Start = thisCollider_Start;
		++otherCollider_Start;

		otherCollider_End = collider_List.end();

		for (; otherCollider_Start != otherCollider_End; ++otherCollider_Start)
		{
			if (false == (*otherCollider_Start)->IsUpdate())
			{
				continue;
			}

			(*thisCollider_Start)->CollisionCheck((*otherCollider_Start));
		}
	}
}

void ColliderManager::ColliderGroup::Release()
{
	std::list<My_Ptr<Collider>>::iterator start		= collider_List.begin();
	std::list<My_Ptr<Collider>>::iterator end		= collider_List.end();

	for (; start != end; )
	{
		if (true == (*start)->IsDeath())
		{
			start = collider_List.erase(start);
		}
		else
		{
			++start;
		}
	}
}


void ColliderManager::ColliderGroup::OverColliderRelease()
{
	std::list<My_Ptr<Collider>>::iterator start = collider_List.begin();
	std::list<My_Ptr<Collider>>::iterator end	= collider_List.end();

	for (; start != end; )
	{
		if (true == (*start)->GetActor()->IsOverScene())
		{
			start = collider_List.erase(start);
		}
		else
		{
			++start;
		}
	}
}
#pragma endregion




#pragma region COLLIDERMANAGER
ColliderManager::ColliderManager()
{
}


ColliderManager::~ColliderManager()
{
}

My_Ptr<ColliderManager::ColliderGroup> ColliderManager::Find_ColliderGroup(const int& _Key)
{
	std::map<int, My_Ptr<ColliderGroup>>::iterator FindIter = colliderGroup_Map.find(_Key);
	
	if (FindIter == colliderGroup_Map.end())
	{
		return nullptr;
	}

	return FindIter->second;
}

void ColliderManager::PushCollider(const My_Ptr<Collider>& _COL)
{
	std::map<int, My_Ptr<ColliderGroup>>::iterator FindIter = colliderGroup_Map.find(_COL->GetOrder());

	if (FindIter == colliderGroup_Map.end())
	{
		colliderGroup_Map.insert(std::map<int, My_Ptr<ColliderGroup>>::value_type(_COL->GetOrder(), new ColliderGroup()));
		FindIter = colliderGroup_Map.find(_COL->GetOrder());
	}

	FindIter->second->PushCollider(_COL);
}

void ColliderManager::Circulate_ColliderGroupMap()
{
	colliderGroup_Start = colliderGroup_Map.begin();
	colliderGroup_End	= colliderGroup_Map.end();

	for (; colliderGroup_Start != colliderGroup_End; ++colliderGroup_Start)
	{
		colliderGroup_Start->second->Circulate_ColliderGroup();
	}
}

void ColliderManager::Link(const int& _Src, const int& _Dest)
{
	ColliderGroup* src	= Find_ColliderGroup(_Src);
	ColliderGroup* dest = Find_ColliderGroup(_Dest);

	if (nullptr == src)
	{
		src = new ColliderGroup();
		colliderGroup_Map.insert(std::map<int, My_Ptr<ColliderGroup>>::value_type(_Src, src));
	}
	if (nullptr == dest)
	{
		dest = new ColliderGroup();
		colliderGroup_Map.insert(std::map<int, My_Ptr<ColliderGroup>>::value_type(_Dest, dest));
	}

	src->PushOtherColliderGroup(dest);
}

void ColliderManager::Release()
{
	colliderGroup_Start = colliderGroup_Map.begin();
	colliderGroup_End = colliderGroup_Map.end();

	for (; colliderGroup_Start != colliderGroup_End; ++colliderGroup_Start)
	{
		colliderGroup_Start->second->Release();
	}
}

void ColliderManager::OverColliderGroupRelease()
{
	colliderGroup_Start = colliderGroup_Map.begin();
	colliderGroup_End = colliderGroup_Map.end();

	for (; colliderGroup_Start != colliderGroup_End; ++colliderGroup_Start)
	{
		colliderGroup_Start->second->Release();
	}
}

#pragma endregion


