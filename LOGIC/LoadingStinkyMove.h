#pragma once
#include <Logic.h>
class LoadingStinkyMove :	public Logic
{
public:
	static float loadingRate;

private:
	Vector4 dir;
	Vector4 pos;

public:
	void Init() override;
	void Update() override;

public:
	LoadingStinkyMove();
	~LoadingStinkyMove();
};

