#pragma once
#include <Logic.h>
class EndAngieMove :
	public Logic
{
private:
	Vector4 dir;

public:
	void Init() override;
	void Update() override;

public:
	EndAngieMove();
	~EndAngieMove();
};

