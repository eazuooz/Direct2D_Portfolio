#pragma once
#include <Scene.h>
#include "UI.h"
#include <list>
//class Hatch;
#define CREATETIME 10.0f


class GusMove;
class BossMove;
class DentacleMove;
class FontRenderer;
class MonsterMove;
class SpriteRenderer;
class AdventureUpdater : public Scene::Updater
{	
private:
	float bubbleTime1;
	float bubbleTime2;
	float bubbleTime3;
	float rebubbleTime;

private:
	static std::list<Hatch*> hatchList;


	Hatch* HatchButtonLine;
	Hatch* foodUIHatch;
	Hatch* uiFoodAmount;
	Hatch* uiPirana;
	Hatch* uiBIGFish;
	Hatch* uiGun;
	Hatch* uiPetEgg;

private:
	My_Ptr<Actor> coinScore;

private:
	enum MONSTER : int
	{
		BALROG,
		GUS,
		PSYCHOSQUID,
		BOSS,
		SMALLSYLV,		
	};

	MONSTER kindsOfMonster;
	My_Ptr<Actor> monster;


	My_Ptr<SpriteRenderer>  hpRender;

	MonsterMove* monsterLogic;
	GusMove* gusLogic;
	BossMove* bossLogic;
	DentacleMove* dentacleLogic;

	float createMonsterTime;
	static int	 monsterHp;
	 bool existMonster;
	 bool existGus;

private:
	My_Ptr<Actor> warpHole;
	My_Ptr<SpriteAnimation> warpHoleAni;
	bool createWarp;
	bool createMonster;
	Vector4 createPos;

	FontRenderer* piiCnt;

public:
	static void DeletesHatchList()
	{
		std::list<Hatch*>::iterator begin;
		std::list<Hatch*>::iterator end;

		begin	= hatchList.begin();
		end		= hatchList.end();


		for (; begin != end; )
		{
			delete *begin;
			begin = hatchList.erase(begin);
		}
	}

private:
	void Loading()		 override;
	void SceneUpdate()	override;
	void ChangeEnd()		override;


public:
	AdventureUpdater();
	~AdventureUpdater();
};

