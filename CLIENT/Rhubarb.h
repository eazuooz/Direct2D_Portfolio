#pragma once
#include "Pet.h"
#include <Logic.h>

class RhubarbMove;
class Rhubarb : public Pet
{
private:
	RhubarbMove* moveLogic;

public:
	void CreateAnimation();
	void AddComponent();

public:
	Rhubarb(My_Ptr<Scene> _Scene, const wchar_t* _TextureName, Vector4 _CntInfo);
	~Rhubarb();
};

