#include "Logic.h"
#include "Scene.h"


Logic::Logic()
{
	SetName(L"Logic");
}


Logic::~Logic()
{
}

Scene* Logic::GetScene()
{
	return GetActor()->GetScene();
}

My_Ptr<Actor> Logic::CreateObject(const wchar_t* _Name)
{
	return GetScene()->CreateActor(_Name);
}