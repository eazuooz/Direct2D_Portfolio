#pragma once
#include "Pet.h"
#include <Logic.h>

class Meryl : public Pet
{
private:
	Logic* moveLogic;

public:
	void CreateAnimation();
	void AddComponent();

public:
	Meryl(My_Ptr<Scene> _Scene, const wchar_t* _TextureName, Vector4 _CntInfo);
	~Meryl();
};

