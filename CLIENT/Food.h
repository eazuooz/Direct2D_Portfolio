#pragma once
#include <Scene.h>
#include <Actor.h>
#include <SpriteRenderer.h>
#include <SpriteAnimation.h>
#include <BoundingSphere.h>
#include <FoodMove.h>




class Food
{
private:
	Scene*				scene;
	Actor*				actor;
	SpriteRenderer*		spriteRenderer;
	
	BoundingSphere*		collider;
	FoodMove*			foodMove;


	static SpriteAnimation*	spriteAnimation;
private:
	static int foodCount;
	static int maximumFoodCount;
	Vector4 pos;
	static int foodLevel;
	
public:
	static void FoodLevelUp()
	{
		++foodLevel;
	}


public:
	static void SetFoodCount(const int _Count)
	{
		foodCount = _Count;
	}

	static int GetMaxFoodCount()
	{
		return maximumFoodCount;
	}
	static void SetMaxFoodCount(const int _Count)
	{
		maximumFoodCount = _Count;
	}

public:
	void Init();
	void CreateSprite();

public:
	Food(My_Ptr<Scene> _Scene, Vector4 _Pos);
	~Food();
};

