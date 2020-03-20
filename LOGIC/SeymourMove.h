#pragma once
#include "FishLogic.h"
class SeymourMove :
	public FishLogic
{
private:


public:
	void Init() override;
	void Update() override;

public:
	SeymourMove();
	~SeymourMove();
};

