#pragma once
#include <Logic.h>

#include <SpriteAnimation.h>


class MeryTailLogic : public Logic
{
private:
	float tailingTime;
	bool isTail;
	My_Ptr< SpriteAnimation> spriteAni;

public:
	void Init() override;
	void Update() override;
public:
	MeryTailLogic();
	~MeryTailLogic();
};

