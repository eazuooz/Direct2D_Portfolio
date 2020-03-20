#pragma once
#include <Logic.h>

class BubbleMove : public Logic
{
private:
	bool xCheck;
	Vector4 dir;

	static bool isEndingScene;

public:
	static void EndingSceneOn()
	{
		isEndingScene = true;
	}

public:
	void Init()		override;
	void Update()	override;

public:
	BubbleMove();
	~BubbleMove();
};

