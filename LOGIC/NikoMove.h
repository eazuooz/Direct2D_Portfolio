#pragma once
#include <Logic.h>
#include <SpriteRenderer.h>
#include <SpriteAnimation.h>
#include <BoundingSphere.h>

#define NIKOCREATETIME 5.0f

class NikoMove :	public Logic
{
private:
	enum NIKO
	{
		IDLE,
		OPEN,
		CLOSE,
	};

	NIKO state;
	My_Ptr<Actor> pearl;

	std::wstring fishName;
	std::wstring curAniName;
	float openTime;
	bool isCreate;

private:
	SpriteRenderer* spriteRenderer;
	SpriteAnimation* spriteAnimaion;

public:
	void Init()		override;
	void Update()	override;

public:
	void Idle();
	void Open();
	void Close();

public:
	NikoMove();
	~NikoMove();
};

