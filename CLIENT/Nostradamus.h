#pragma once
//Nostradamus
#include "Pet.h"
#include <Logic.h>

class Nostradamus : public Pet
{
private:
	Logic* moveLogic;

public:
	void CreateAnimation();
	void AddComponent();

public:
	Nostradamus(My_Ptr<Scene> _Scene, const wchar_t* _TextureName, Vector4 _CntInfo);
	~Nostradamus();
};



