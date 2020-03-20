#pragma once
#include "Pet.h"
#include <Logic.h>
#include <EffectSpriteRenderer.h>

class Amp : public Pet
{
private:
	Logic* moveLogic;

public:
	void CreateAnimation();
	void AddComponent();

public:
	Amp(My_Ptr<Scene> _Scene, const wchar_t* _TextureName, Vector4 _CntInfo);
	~Amp();
};
