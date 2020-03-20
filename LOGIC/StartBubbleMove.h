#pragma once
#include <Logic.h>


class StartBubbleMove : public Logic
{
private:
	enum STATE
	{
		START,
		END,
	};

	STATE state;

	bool xCheck;
	Vector4 dir;

public:
	void Init()		override;
	void Update()	override;

public:
	void Start();
	void End();

public:
	StartBubbleMove();
	~StartBubbleMove();
};

