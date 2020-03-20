#pragma once
#include "FishLogic.h"
#include <BoundingSphere.h>

class GumboMove : public FishLogic
{
private:
	static Vector4 returnPos;
	static BoundingSphere* collider;

public:
	static Vector4 GetPos()
	{
		return returnPos;
	}
	static BoundingSphere* GetCollider()
	{
		return collider;
	}

private:
	bool existMonster;

public:
	void Init() override;
	void Update() override;

public:
	void FindDestination(std::list<Actor*> _DestList) override;


	void InterMoving() override;
	void Stop() override;

public:
	GumboMove();
	~GumboMove();
};

