#include "Component.h"



Component::Component()
{
	//CompareType();
}


Component::~Component()
{
}

void Component::ComInit()
{	
	transform	= actor->GetTransform();
}

void Component::SceneChangeStart()
{
	//엑터에 바뀐씬이 세팅된 다음에 실행된다.
	//기억해 놓으세요
}