#pragma once
#include "FishLogic.h"
class MerylMove : public FishLogic
{
private:
	float singTime;

public:
	void Init() override;
	void Update() override;

	void Skill();

public:
	MerylMove();
	~MerylMove();
};

