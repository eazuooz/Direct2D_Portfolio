#pragma once
#include "FishLogic.h"
class AngieMove : public FishLogic
{
public:
	void Init() override;
	void Update() override;

public:
	AngieMove();
	~AngieMove();
};

