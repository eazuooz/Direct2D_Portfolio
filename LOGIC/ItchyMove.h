#pragma once
#include "FishLogic.h"

class ItchyMove : public FishLogic
{
private:
	float findTime;
	bool isChange;

public:
	void Init() override;
	void Update() override;

public:
	void SkillMove();
	void SkillStop();

public:
	ItchyMove();
	~ItchyMove();
};

