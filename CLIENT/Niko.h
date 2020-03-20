#pragma once
#include <Logic.h>
#include <ShellPetMove.h>
#include "Pet.h"


class Niko : public Pet
{
private:
	ShellPetMove* moveLogic;

public:
	void CreateAnimation();
	void AddComponent();

public:
	Niko(My_Ptr<Scene> _Scene, const wchar_t* _TextureName, Vector4 _CntInfo);
	~Niko();
};


