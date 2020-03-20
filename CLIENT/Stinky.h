#pragma once
#include "Pet.h"
#include <Logic.h>
#include <BoundingSphere.h>


class Stinky : public Pet
{
private:
	Logic* moveLogic;

	BoundingSphere*		collider;

public:
	void CreateAnimation();
	void AddComponent();

public:
	Stinky(My_Ptr<Scene> _Scene, const wchar_t* _TextureName, Vector4 _CntInfo);
	~Stinky();
};


