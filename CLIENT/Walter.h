#pragma once


#include "Pet.h"
#include <Logic.h>
#include <BoundingSphere.h>


class Walter : public Pet
{
private:
	Logic* moveLogic;

public:
	void CreateAnimation();
	void AddComponent();

public:
	Walter(My_Ptr<Scene> _Scene, const wchar_t* _TextureName, Vector4 _CntInfo);
	~Walter();
};
