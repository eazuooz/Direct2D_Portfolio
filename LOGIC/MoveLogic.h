#pragma once
#include <Logic.h>

class MoveLogic : public Logic
{
public:
	void Init() override;
	void Update() override;

public:
	MoveLogic();
	~MoveLogic();
};

