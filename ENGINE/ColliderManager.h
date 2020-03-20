#pragma once
#include <SmartPtr.h>

#include <map>
#include <list>
#include <Debug.h>



class Collider;
class Scene;
class ColliderManager
{
public:
	friend Collider;
	friend Scene;

private:
	class ColliderGroup : public ControlBlock
	{
	public:
		friend ColliderManager;

	public:
		std::list<My_Ptr<Collider>>::iterator thisCollider_Start;
		std::list<My_Ptr<Collider>>::iterator thisCollider_End;

		std::list<My_Ptr<Collider>>::iterator otherCollider_Start;
		std::list<My_Ptr<Collider>>::iterator otherCollider_End;


	public:	
		std::list<ColliderGroup*>::iterator otherGroup_Start;
		std::list<ColliderGroup*>::iterator otherGroup_End;
		std::list<ColliderGroup*> coliiderGroup_List;	//Another group to crash to with me

	private:
		std::list<My_Ptr<Collider>> collider_List;

		void PushCollider(const My_Ptr<Collider>& _COL)
		{
			if (nullptr == _COL) { BOOM; }
			collider_List.push_back(_COL);			
		}
		void PushOtherColliderGroup(ColliderGroup* _OtherGroup)
		{
			if (nullptr == _OtherGroup) { BOOM; }
			coliiderGroup_List.push_back(_OtherGroup);
		}


	public:
		void Circulate_ColliderGroup();
		void Circulate_OtherGroupCollider(ColliderGroup* _OtherGroup);	//Circulate between This and OtherGroup
		void Circulate_ThisGroupCollider();								//Circulate between This and This
		void Release();
		void OverColliderRelease();
	};

private:
	std::map<int, My_Ptr<ColliderGroup>>::iterator colliderGroup_Start;
	std::map<int, My_Ptr<ColliderGroup>>::iterator colliderGroup_End;
	std::map<int, My_Ptr<ColliderGroup>> colliderGroup_Map;

private:
	My_Ptr<ColliderGroup> Find_ColliderGroup(const int& _Key);
	void PushCollider(const My_Ptr<Collider>& _COL);

private:
	void Circulate_ColliderGroupMap();

public:
	void Link(const int& _Src, const int& _Dest);

public:
	void Release();
	void OverColliderGroupRelease();

public:
	ColliderManager();
	~ColliderManager();
};

