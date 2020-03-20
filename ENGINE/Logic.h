#pragma once
#include "Transform.h"
#include <MyTime.h>
#include <Input.h>

#include <Well512.h>

class Actor;
class Logic : public Component
{
public:
	Scene* GetScene();
	My_Ptr<Actor> CreateObject(const wchar_t* _Name = L"GameOBject");

public:
	Logic();
	~Logic();
};

