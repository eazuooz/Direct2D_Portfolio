#include "LoadingStinkyMove.h"


float LoadingStinkyMove::loadingRate = 0.0f;
LoadingStinkyMove::LoadingStinkyMove()// : loadingRate(0.0f)
{
}


LoadingStinkyMove::~LoadingStinkyMove()
{
}


void LoadingStinkyMove::Init()
{
	dir = {0.5f, 0.0f, 0.0f, 0.0f};
}

void LoadingStinkyMove::Update()
{
	pos = GetActor()->GetTransform()->GetLocalPosition();

	if (loadingRate <= 1.0f)
	{
		loadingRate += ((dir.x* 1.0f * Time::DeltaTime()) / 2.24f);
	}
	else
	{

	}

	

	if (pos.x > 1.0f)
	{
		return;
	}

	GetActor()->GetTransform()->Move2D(dir* 1.0f * Time::DeltaTime(), -11.0f);
}