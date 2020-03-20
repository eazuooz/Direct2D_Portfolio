#pragma once
#include "Pet.h"
#include <Logic.h>
#include <BoundingSphere.h>
#include <NimbusMove.h>

class Nimbus : public Pet
{
private:
	NimbusMove* moveLogic;

public:
	void CreateAnimation();
	void AddComponent();

public:
	Nimbus(My_Ptr<Scene> _Scene, const wchar_t* _TextureName, Vector4 _CntInfo);
	~Nimbus();
};

