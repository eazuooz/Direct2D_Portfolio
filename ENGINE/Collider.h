#pragma once

#include <set>
#include <functional>

#include "Transforms.h"


class ColliderManager;
class Collider : public Transforms
{
//private:
//	std::wstring actorName;

private:
	enum MODE
	{
		COL_2D, COL_3D,
	};

public:
	friend ColliderManager;

	int order;

	int GetOrder()
	{
		return order;
	}

	void SetOrder(int _Order)
	{
		order = _Order;
	}

private:
	std::list<std::function<void(Collider*, Collider*)>>::iterator function_Start;
	std::list<std::function<void(Collider*, Collider*)>>::iterator function_End;

	std::list<std::function<void(Collider*, Collider*)>> enterFunction_List;
	std::list<std::function<void(Collider*, Collider*)>> stayFunction_List;
	std::list<std::function<void(Collider*, Collider*)>> exitFunction_List;


public:
	template<typename T>
	void RegisterEnterFunction(void(T::* _Function)(Collider*, Collider*), T* _Object)
	{
		std::function<void(Collider*, Collider*)> Func = 
			std::bind(_Function, _Object, std::placeholders::_1, std::placeholders::_2);

		if (nullptr == Func) { BOOM; }
		enterFunction_List.push_back(Func);
	}

	//World Function
	void RegisterEnterFunction(void(* _Function)(Collider*, Collider*))
	{
		std::function<void(Collider*, Collider*)> Func = _Function;

		if (nullptr == Func) { BOOM; }
		enterFunction_List.push_back(Func);
	}
	//
	template<typename T>
	void RegisterStayFunction(void(T::* _Function)(Collider*, Collider*), T* _Object)
	{
		std::function<void(Collider*, Collider*)> Func =
			std::bind(_Function, _Object, std::placeholders::_1, std::placeholders::_2);

		if (nullptr == Func) { BOOM; }
		stayFunction_List.push_back(Func);
	}

	//World Function
	void RegisterStayFunction(void(*_Function)(Collider*, Collider*))
	{
		std::function<void(Collider*, Collider*)> Func = _Function;

		if (nullptr == Func) { BOOM; }
		stayFunction_List.push_back(Func);
	}
	//
	template<typename T>
	void RegisterExitFunction(void(T::* _Function)(Collider*, Collider*), T* _Object)
	{
		std::function<void(Collider*, Collider*)> Func =
			std::bind(_Function, _Object, std::placeholders::_1, std::placeholders::_2);

		if (nullptr == Func) { BOOM; }
		exitFunction_List.push_back(Func);
	}

	//World Function
	void RegisterExitFunction(void(*_Function)(Collider*, Collider*))
	{
		std::function<void(Collider*, Collider*)> Func = _Function;

		if (nullptr == Func) { BOOM; }
		exitFunction_List.push_back(Func);
	}

private:
	// 함수 포인터를 받는다.
	// 함수 포인터로
	void ColliderEnter(Collider* _Other);
	void ColliderStay(Collider* _Other);
	void ColliderExit(Collider* _Other);

	//void ColStaticEnterFunc(Collider* _Other);

private:
	std::set<Collider*>::iterator Find_ColliderIter;
	//나랑 충돌한 녀석들을 보관해 놓는것
	//도형끼리 닿아있으면
	//충돌이 시작되면 보관한다	
	//충돌이 끝나면 버린다

	std::set<Collider*> otherCollider_Set;

private:
	void Init() override;

public:
	void DataCreate(int _Order = 0);

private:
	void CollisionCheck(Collider* _Other);

public:
	virtual bool GeometryCheck(Collider* _Other) = 0;

public:
	void SceneChangeStart() override;

public:
	Collider();
	~Collider();
};

