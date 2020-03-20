#pragma once
#include "FishLogic.h"

class PregoMove : public FishLogic
{
private:
	float birthTime;

public:
	static int birthCnt;
	static Vector4 pregoPos;

public:
	static Vector4 GetPos()
	{
		return pregoPos;
	}

public:
	void Init() override;
	void Update() override;

	void Birth();


public:
	PregoMove();
	~PregoMove();
};

