#pragma once
#include <Logic.h>
#include <SpriteRenderer.h>
#include <BoundingSphere.h>


class CoinMove :	public Logic
{
private:
	Vector4 pos;
	Vector4 dir;
	float speed;

	SpriteRenderer*		spriteRenderer;
	BoundingSphere*		collider;

	bool goCoinBox;
	bool isStinky;
	int coinLevel;

	float eraseTime;

	bool isStop;
	bool coinSoundCheck;
	bool isBomb;

public:
	void BombOn()
	{
		isBomb = true;
	}

	void BombOff()
	{
		isBomb = false;
	}

	bool GetIsBomb()
	{
		return isBomb;
	}

private:
	static bool resetCoin;
	static float coinSpeed;

public:
	static void ResetCoin()
	{
		resetCoin = true;
		coinSpeed = 0.3f;
	}

public:
	int GetCoinLevel()
	{
		return coinLevel;
	}

	void Stop()
	{
		isStop = true;
	}

	void GoCoinBox()
	{
		goCoinBox = true;
	}



public:
	void Init()		override;
	void Update()	override;

private:
	float nimbusTime;
	float nimbusMoveSpeed;
	bool isNimbus;

public:

	void Nimbus();

public:
	void Enter(Collider* _This, Collider* _Other);
	void Stay(Collider* _This, Collider* _Other);
	void Exit(Collider* _This, Collider* _Other);

public:
		CoinMove();
	~CoinMove();
};

