#pragma once
#include "Pet.h"
#include <AngieMove.h>
#include <BoundingSphere.h>

class Angie : public Pet
{
private:
	AngieMove* moveLogic;

public:
	void CreateAnimation();
	void AddComponent();

public:
	Angie(My_Ptr<Scene> _Scene, const wchar_t* _TextureName, Vector4 _CntInfo);
	~Angie();
};
