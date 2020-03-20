#include "EndAngieMove.h"

#include "ENUM.h"

EndAngieMove::EndAngieMove()
{
}


EndAngieMove::~EndAngieMove()
{
}


void EndAngieMove::Init()
{
	dir = { 0.5f, 0.3f, 0.0f };
}

void EndAngieMove::Update()
{
	GetActor()->GetTransform()->Move2D((dir* 1.5f * Time::DeltaTime()), __GOOPY);
}