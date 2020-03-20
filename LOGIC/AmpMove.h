#pragma once
#include "FishLogic.h"
#include <BoundingBox.h>
#include <EffectSpriteRenderer.h>


class AmpMove :	public FishLogic
{
private:
	EffectSpriteRenderer* light;

	float lightTime;

public:
	void Init() override;
	void Update() override;


public:
	void Enter(Collider* _This, Collider* _Other);
	void Stay(Collider* _This, Collider* _Other);
	void Exit(Collider* _This, Collider* _Other);

public:
	AmpMove();
	~AmpMove();
};

