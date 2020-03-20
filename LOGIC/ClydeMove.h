#pragma once
#include "FishLogic.h"

class ClydeMove :	public FishLogic
{
public:
	void Init() override;
	void Update() override;

public:
	ClydeMove();
	~ClydeMove();
};

