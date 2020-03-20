#pragma once
#include "Pet.h"
#include <Logic.h>

class shrapnel : public Pet
{
private:
	Logic* moveLogic;

public:
	void CreateAnimation();
	void AddComponent();

public:
	shrapnel(My_Ptr<Scene> _Scene, const wchar_t* _TextureName, Vector4 _CntInfo);
	~shrapnel();
};

