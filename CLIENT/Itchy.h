#pragma once
#include "Pet.h"
#include <Logic.h>

class Itchy : public Pet
{
private:
	Logic* moveLogic;

public:
	void CreateAnimation();
	void AddComponent();

public:
	Itchy(My_Ptr<Scene> _Scene, const wchar_t* _TextureName, Vector4 _CntInfo);
	~Itchy();
};

