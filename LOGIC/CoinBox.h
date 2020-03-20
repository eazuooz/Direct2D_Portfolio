#pragma once
#include <Logic.h>
#include <BoundingBox.h>
#include <BoundingSphere.h>
#include <FontRenderer.h>

#include "CoinMove.h"



class CoinBox : public Logic
{
private:
	BoundingBox* collider;
	FontRenderer* font;

public:
	static int money;

public:
	void Init()		override;
	void Update()	override;


public:
	void Enter(Collider* _This, Collider* _Other);
	void Stay(Collider* _This, Collider* _Other);
	void Exit(Collider* _This, Collider* _Other);

public:
	CoinBox();
	~CoinBox();
};

