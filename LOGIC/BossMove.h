#pragma once
#include "FishLogic.h" 
#include <BoundingSphere.h>

class BossMove : public FishLogic
{
private:
	My_Ptr<Actor> chomp;
	My_Ptr<SpriteAnimation> chompAni;

	BoundingSphere* collider;


	My_Ptr<Actor> smoke;
	My_Ptr<SpriteAnimation> smokeAni;
	My_Ptr<SpriteRenderer> smokeRender;

	float attPoint;
	float hp;


	float alienTime;

public:
	float GetHp()
	{
		return hp;
	}


public:
	void Init() override;
	void Update() override;

	

public:
	void Enter(Collider* _This, Collider* _Other);
	void Stay(Collider* _This, Collider* _Other);
	void Exit(Collider* _This, Collider* _Other);

public:
	BossMove();
	~BossMove();
};

