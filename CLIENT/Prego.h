#pragma once
#include "Pet.h"
#include <Logic.h>

class Prego : public Pet
{
private:
	Logic* moveLogic;

public:
	void CreateAnimation();
	void AddComponent();

public:
	Prego(My_Ptr<Scene> _Scene, const wchar_t* _TextureName, Vector4 _CntInfo);
	~Prego();
};

