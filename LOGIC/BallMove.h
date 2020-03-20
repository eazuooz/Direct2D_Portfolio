#pragma once
#include <Logic.h>

class BallMove : public Logic
{
private:
	Vector4 pos;

	Vector4 monsterDir;

public:
	void Init() override;
	void Update() override;

public:
	BallMove();
	~BallMove();
};

