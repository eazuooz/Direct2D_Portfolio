#pragma once
#include "FishLogic.h"

class ShrapnelMove : public FishLogic
{
private:
	float bombTime;

public:
	void Init() override;
	void Update() override;


public:
	ShrapnelMove();
	~ShrapnelMove();
};

