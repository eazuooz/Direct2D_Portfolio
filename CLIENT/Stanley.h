#pragma once
#include "Pet.h"
#include <Logic.h>


class Stanley : public Pet
{
private:
	Logic* moveLogic;

public:
	void CreateAnimation();
	void AddComponent();

public:
	Stanley(My_Ptr<Scene> _Scene, const wchar_t* _TextureName, Vector4 _CntInfo);
	~Stanley();
};



//Stanley