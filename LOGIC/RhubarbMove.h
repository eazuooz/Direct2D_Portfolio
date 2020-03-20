#pragma once
#include "FishLogic.h"
#include <BoundingSphere.h>

class RhubarbMove :  public FishLogic
{
private:
	BoundingSphere* rhCollider;

public:
	void Init() override;
	void Update() override;

public:
	void Skill();

public:
	void Enter(Collider* _This, Collider* _Other);
	void Stay(Collider* _This, Collider* _Other);
	void Exit(Collider* _This, Collider* _Other);

public:
	RhubarbMove();
	~RhubarbMove();
};

