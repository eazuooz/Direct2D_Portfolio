#pragma once
#include "Pet.h"
#include <Logic.h>
#include <ShellPetMove.h>

class Brinkley : public Pet
{
private:
	ShellPetMove* moveLogic;

public:
	void CreateAnimation();
	void AddComponent();

public:
	Brinkley(My_Ptr<Scene> _Scene, const wchar_t* _TextureName, Vector4 _CntInfo);
	~Brinkley();
};

