#include "Actor.h"
#include "Component.h"
#include "Transform.h"

Actor::Actor() : isChildReady(false)
{
}


Actor::~Actor()
{
}

bool Actor::CheckFunc(Component* _Com, const type_info* _TypeInfo)
{
	return _Com->CompareType(_TypeInfo);
}

void Actor::SetScene(Scene* _Scene)
{
	scene = _Scene;

	childAcotr_Start	= childActor_List.begin();
	childAcotr_End		= childActor_List.end();

	for (; childAcotr_Start != childAcotr_End; ++childAcotr_Start)
	{
		(*childAcotr_Start)->SetScene(_Scene);
	}
}

void Actor::PushComponent(Component* _Com)
{
	_Com->SetActor(this);
	_Com->TypeSetting();
	_Com->ComInit();
	_Com->Init();

	componentList.push_back(_Com);
}


void Actor::UpdateAfter()
{
	ITERFOR(componentStart, componentEnd, componentList, UpdateAfter);
	ITERFOR(childAcotr_Start, childAcotr_End, childActor_List, UpdateAfter);
}
void Actor::Update()
{
	componentStart = componentList.begin();
	componentEnd = componentList.end();

	for (; componentStart != componentEnd; ++componentStart)
	{
		if (false == (*componentStart)->IsUpdate())
		{
			continue;
		}
		(*componentStart)->Update();
	}

	childAcotr_Start = childActor_List.begin();
	childAcotr_End = childActor_List.end();

	for (; childAcotr_Start != childAcotr_End; ++childAcotr_Start)
	{
		if (false == (*childAcotr_Start)->IsUpdate())
		{
			continue;
		}
		(*childAcotr_Start)->Update();
	}

	//ITERFOR(ComStart, ComEnd, m_ComList, Update);
	//ITERFOR(ChildStart, ChildEnd, m_ChildList, Update);
}
void Actor::UpdateBefore()
{
	ITERFOR(componentStart, componentEnd, componentList, UpdateBefore);
	ITERFOR(childAcotr_Start, childAcotr_End, childActor_List, UpdateBefore);
}
void Actor::FinalUpdate()
{
	ITERFOR(componentStart, componentEnd, componentList, FinalUpdate);
	ITERFOR(childAcotr_Start, childAcotr_End, childActor_List, FinalUpdate);
}
void Actor::RenderObjBefore()
{
	ITERFOR(componentStart, componentEnd, componentList, RenderObjBefore);
	ITERFOR(childAcotr_Start, childAcotr_End, childActor_List, RenderObjBefore);
}
//void Actor::RenderObj()
//{
//	ITERFOR(componentStart, componentEnd, componentList, RenderObj);
//
//}
void Actor::RenderObjAfter()
{
	ITERFOR(componentStart, componentEnd, componentList, RenderObjAfter);
	ITERFOR(childAcotr_Start, childAcotr_End, childActor_List, RenderObjAfter);
}
void Actor::ColBefore()
{
	ITERFOR(componentStart, componentEnd, componentList, ColBefore);
	ITERFOR(childAcotr_Start, childAcotr_End, childActor_List, ColBefore);
}

void Actor::ColAfter()
{
	ITERFOR(componentStart, componentEnd, componentList, ColAfter);
	ITERFOR(childAcotr_Start, childAcotr_End, childActor_List, ColAfter);
}
void Actor::Release()
{

	componentStart = componentList.begin();
	componentEnd = componentList.end();

	for (; componentStart != componentEnd; )
	{
		(*componentStart)->Release();
		if (true == (*componentStart)->IsDeath())
		{
			componentStart = componentList.erase(componentStart);
		}
		else {
			++componentStart;
		}
	}

	childAcotr_Start = childActor_List.begin();
	childAcotr_End = childActor_List.end();

	for (; childAcotr_Start != childAcotr_End; )
	{
		(*childAcotr_Start)->Release();
		if (true == (*childAcotr_Start)->IsDeath())
		{
			childAcotr_Start = childActor_List.erase(childAcotr_Start);
		}
		else {
			++childAcotr_Start;
		}
	}


	// 이녀석만 좀 특별.
	//ITERFOR(childAcotr_Start, childAcotr_End, childActor_List, Release);
	//ITERFOR(componentStart, componentEnd, componentList, Release);
}
void Actor::ReleaseAfter()
{
	ITERFOR(childAcotr_Start, childAcotr_End, childActor_List, ReleaseAfter);
	ITERFOR(componentStart, componentEnd, componentList, ReleaseAfter);
}

void Actor::SceneChangeStart()
{
	ITERFOR(childAcotr_Start, childAcotr_End, childActor_List, SceneChangeStart);
	ITERFOR(componentStart, componentEnd, componentList, SceneChangeStart);
}


////부모자식

void Actor::ChildReadyUpdate()
{
	if (nullptr != parentActor)
	{
		parentActor->childActor_List.push_back(this);
		isChildReady = false;
	}
}


void Actor::SetParent(My_Ptr<Actor>	_ParentActor)
{
	if (nullptr == _ParentActor)
	{
		BOOM;
	}

	parentActor = _ParentActor;

	if (nullptr != GetTransform() && _ParentActor->GetTransform())
	{
		GetTransform()->SetParentTransform(parentActor->GetTransform());
	}
	
	isChildReady = true;
	// m_ParentActor->ChildList.push_back(this);
}