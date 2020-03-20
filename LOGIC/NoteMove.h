#pragma once
#include <Logic.h>


class NoteMove : public Logic
{
private:
	Vector4 dir;
	float speed;

public:
	void Init() override;
	void Update() override;


public:
	NoteMove();
	~NoteMove();
};

