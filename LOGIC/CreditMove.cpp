#include "CreditMove.h"

#include "ENUM.h"

CreditMove::CreditMove()
{
}


CreditMove::~CreditMove()
{
}

void CreditMove::Init()
{
	dir = { 0.0f, 0.4f, 0.0f };
}

void CreditMove::Update()
{
	GetActor()->GetTransform()->Move2D((dir* 1.5f * Time::DeltaTime()), __GOOPY);
}
