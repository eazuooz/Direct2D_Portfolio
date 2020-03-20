#pragma once
#include <Maths.h>
#include <SmartPtr.h>

#include <Scene.h>
#include <Actor.h>

#include <SpriteRenderer.h>
#include <SpriteAnimation.h>
#include <BoundingSphere.h>


class Mouse 
{
private:
	static Mouse* inst;

public:
	static Mouse& Inst()
	{
		if (inst == nullptr)
		{
			inst = new Mouse();
		}

		return *inst;
	}


private:



private:
	My_Ptr<Scene>		scene;
	My_Ptr<Actor>		actor;
	My_Ptr<BoundingSphere>	collider;
	My_Ptr<SpriteRenderer> spriteRender;
	My_Ptr<SpriteAnimation> spriteAnimaion;

	std::wstring aniName;
	std::wstring gunPower;

public:
	void SetScene(My_Ptr<Scene> _Scene) 
	{
		scene = _Scene;
	}

private:
	Vector4 pos;

public:
	Vector4 GetPos() const
	{
		return pos;
	}

public:
	void Init();
	void Update();

public:
	void Enter(Collider* _This, Collider* _Other);
	void Stay(Collider* _This, Collider* _Other);
	void Exit(Collider* _This, Collider* _Other);

public:
	void Destroy();

public:
	Mouse();
	~Mouse();
};

