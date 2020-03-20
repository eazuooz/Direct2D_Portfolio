#pragma once
#include <list>
#include <Actor.h>
#include <BoundingSphere.h>


class GoopyList
{
private:
	static int wadsGoopyCnt;

public:
	static int GetWadsGoopyCnt()
	{
		return wadsGoopyCnt;
	}

private:
	static std::list<BoundingSphere*> littleGoopyList;
	static std::list<BoundingSphere*>::iterator littleGoopyBegin;
	static std::list<BoundingSphere*>::iterator littleGoopyEnd;

public:
	static void LittleGoopyList_Update();
	static void PushLittleGoopy(BoundingSphere* _Collider);
	static void PopLittleGoopy(const BoundingSphere* _Collider);
	static void PopLittleGoopy(const Collider* _Collider);

private:
	static std::list<BoundingSphere*> piranaGoopyList;
	static std::list<BoundingSphere*>::iterator piranaGoopyBegin;
	static std::list<BoundingSphere*>::iterator piranaGoopyEnd;
public:
	static void PiranaGoopyList_Update();
	static void PushPiranaGoopy(BoundingSphere* _Collider);
	static void PopPiranaGoopy(const BoundingSphere* _Collider);
	static void PopPiranaGoopy(const Collider* _Collider);

private:
	static std::list<Actor*> goopyList;
	static std::list<Actor*>::iterator goopyBegin;
	static std::list<Actor*>::iterator goopyEnd;

public:
	static void GoopyList_Update();
	static void PushGoopy(Actor* _Actor);
	static void PopGoopy( Actor* _Actor);
	
private:
	static std::list<Actor*> wadsGoopyList;
	static std::list<Actor*>::iterator wadsGoopyBegin;
	static std::list<Actor*>::iterator wadsGoopyEnd;

public:
	static void GoopyWadsList_UpdateOn();
	static void PushWadsGoopy(Actor* _Actor);
	static void PopWadsGoopy(Actor* _Actor);
	static void SetPosWadsGoopy(Vector4 _Pos);
	static void WadsGoopyClear();

public:
	static std::list<BoundingSphere*> GetLittleGoopyList()
	{
		return littleGoopyList;
	}
	static std::list<BoundingSphere*> GetPiranaGoopyList()
	{
		return piranaGoopyList;
	}

	static std::list<Actor*> GetGoopyList()
	{
		return goopyList;
	}

	static std::list<Actor*> GetWadsGoopyList()
	{
		return wadsGoopyList;
	}

public:
	GoopyList();
	~GoopyList();
};

