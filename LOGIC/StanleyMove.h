#pragma once
#include "FishLogic.h"
class StanleyMove : public FishLogic
{
private:
	float attTime;
	bool isAngry;

	My_Ptr<Actor> coin;

public:
	void Init() override;
	void Update() override;

	void Stop() override;

public:
	void Change();
	void Skill();

public:
	void Enter(Collider* _This, Collider* _Other);
	void Stay(Collider* _This, Collider* _Other);
	void Exit(Collider* _This, Collider* _Other);

public:
	StanleyMove();
	~StanleyMove();
};

