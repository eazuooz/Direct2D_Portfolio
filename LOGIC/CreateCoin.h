#pragma once
#include <Logic.h>




class CreateCoin : public Logic
{
private:
	float crateTime;
	static bool makeCoin;

public:
	void SetCreateTime(float _Time)
	{
		crateTime = _Time;
	}
public:
	static void MakeCoin()
	{
		makeCoin = true;
	}

	static void MakeCoinOff()
	{
		makeCoin = false;
	}

	My_Ptr<Actor> coin;
	int coinLevel;
	
public:
	int GetCoinLevel()
	{
		return coinLevel;
	}

public:
	void Init()		override;
	void Update()	override;

public:
	CreateCoin(int _Level);
	CreateCoin();
	~CreateCoin();
};

