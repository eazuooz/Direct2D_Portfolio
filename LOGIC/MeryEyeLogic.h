#pragma once
#include <Logic.h>
#include <SpriteAnimation.h>


enum MERYSTATE
{
	BASEEYE,
	BLINKEYE,
};


class MeryEyeLogic : public Logic
{
private:
	float blinkTime;
	bool isBlink;
	MERYSTATE state;

	My_Ptr< SpriteAnimation> spriteAni;

public:
	void Init() override;
	void Update() override;

public:
	MeryEyeLogic();
	~MeryEyeLogic();
};

