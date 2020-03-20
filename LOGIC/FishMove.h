#pragma once
#include <set>
#include <Logic.h>
#include <Collider.h>
#include <BoundingSphere.h>

#define HUNGRYTIME 20.0f

class SpriteAnimation;
class SpriteRenderer;
class GoopyMove : public Logic
{
private:
	enum DIRECTION
	{
		LEFT,
		RIGHT,
	};

	enum GOOPYSTATE
	{
		START,
		MOVING,
		STOP,
		HUNGRY,
		EATING,
		DIE,

		WADSWORTH,	//고래
		GUMBO,		//아귀
		RHUBARB,	//소라게
	};

	enum KINDSOFGOOPY
	{
		LITTLE,
		MIDDLE,
		BIG,
		CROWN,
		PIRANA,	
		ULTRA,
	};

private:
	bool isGrow1;
	bool isGrow2;
	bool isGrow3;
	bool isGrow4;

private:
	//std::set<Vector4> distanceFoods;
	std::map<float, BoundingSphere*> foodMap;
	std::map<float, BoundingSphere*> littleGoopyMap;
	std::map<float, BoundingSphere*> piranaGoopyMap;

	std::map<float, BoundingSphere*> wadsMap;
	bool existWads;

	std::map<float, BoundingSphere*> gumboMap;
	bool existGumbo;

	std::map<float, BoundingSphere*>::iterator mapBegin;
	std::map<float, BoundingSphere*>::iterator mapEnd;

	Vector4 minDis;


public:
	static bool isAmpOn;

private:
	bool soundDie;
	Vector4		direction;
	Vector4		pos;
	Vector4		windowSize;
	float		moveSpeed;
	float		movingTime;
	DIRECTION	DIR;
	GOOPYSTATE	state;
	KINDSOFGOOPY kindsOfGoopy;
	KINDSOFGOOPY prevkindsOfGoopy;

	std::wstring fishName;
	std::wstring curAniName;

	My_Ptr<Actor> chomp;
	My_Ptr<SpriteAnimation> chompAni;
	My_Ptr<SpriteRenderer> pointRender;

	bool isFast;

	float	hungryTime;
	bool	isHungry;
	bool	existFood;

	float	deadTime;
	bool	isDeadBody;

	bool createBubble;

	float rhubarbTime;
	float rhubarbMoveSpeed;

	bool ISDie;

	bool createDiamond;


private:	//구피가 가져야할 스탯들
	int point;
	
public:
	void SetPoint(int _Value)
	{
		point = _Value;
		//kindsOfGoopy = KINDSOFGOOPY::PIRANA;
	}

	int GetPoint()
	{
		return point;
	}

	void SetStateMoving()
	{
		state = GOOPYSTATE::MOVING;
	}

private:
	SpriteRenderer*		spriteRenderer;
	SpriteAnimation*	spriteAnimaion;
	BoundingSphere*		collider;

private:
	bool GetFishName();


public:
	void Init()		override;
	void Update()	override;

public:
	void Start();
	void Moving();
	void Stop();
	void Hungry();
	void Eating();
	void GoopyDie();

	//상호작용 스킬들	
	void FindFood();
	void FindLittleGoopy();
	void FindPirana();

	void FindWadsWorth();
	void FindGumbo();

	void WadsWorth();
	void Gumbo();
	void Rhubarb();

public:
	void ChangeDir();
	void MoveGoopy(float _Speed);
	void ChangeAnimation();


public:
	void Enter(Collider* _This, Collider* _Other);
	void Stay(Collider* _This, Collider* _Other);
	void Exit(Collider* _This, Collider* _Other);

//private:
//	static std::list<BoundingSphere*> littleGoopyList;
//	static std::list<BoundingSphere*>::iterator littleGoopyBegin;
//	static std::list<BoundingSphere*>::iterator littleGoopyEnd;
//
//public:
//	static void LittleGoopyList_Update();
//	static void PushLittleGoopy(BoundingSphere* _Collider);
//	static void PopLittleGoopy(const BoundingSphere* _Collider);
//	static void PopLittleGoopy(const Collider* _Collider);


public:
	GoopyMove();
	~GoopyMove();
};

