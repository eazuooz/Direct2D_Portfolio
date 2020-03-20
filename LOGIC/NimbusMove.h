#pragma once
#include "FishLogic.h"
#include <BoundingSphere.h>

class NimbusMove : public FishLogic
{
private:
	BoundingSphere* niCollider;

public:
	void Init() override;
	void Update() override;

public:
	void ShellMoving() override;

public:
	void Enter(Collider* _This, Collider* _Other);
	void Stay(Collider* _This, Collider* _Other);
	void Exit(Collider* _This, Collider* _Other);

public:
	NimbusMove();
	~NimbusMove();
};

