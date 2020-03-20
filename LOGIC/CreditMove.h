#pragma once
#include <Logic.h>


class CreditMove :	public Logic
{
private:
	Vector4 dir;

public:
	void Init() override;
	void Update() override;

public:
	CreditMove();
	~CreditMove();
};

