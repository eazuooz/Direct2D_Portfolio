#pragma once
#include "FishLogic.h"
#include <BoundingSphere.h>

class WadsworthMove : public FishLogic
{
private:
	static Vector4 returnPos;

	static BoundingSphere* collider;

	bool isClose;
	bool skillEnd;

	float closeTime;

public:
	static bool isExist;

public:
	static Vector4 GetPos()
	{
		return returnPos;
	}

	static BoundingSphere* GetCollider()
	{
		return collider;
	}

public:
	void Init() override;
	void Update() override;


public:
	void OpenMouth();
	void CloseMouth();

public:
	WadsworthMove();
	~WadsworthMove();
};

 