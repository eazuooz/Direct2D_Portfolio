#pragma once
//Wadsworth
#include "Pet.h"
#include <Logic.h>
#include <BoundingSphere.h>

class Wadsworth : public Pet
{
private:
	BoundingSphere* collider;
	Logic* moveLogic;

public:
	void CreateAnimation();
	void AddComponent();

public:
	Wadsworth(My_Ptr<Scene> _Scene, const wchar_t* _TextureName, Vector4 _CntInfo);
	~Wadsworth();
};