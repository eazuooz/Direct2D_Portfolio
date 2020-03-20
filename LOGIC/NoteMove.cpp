#include "NoteMove.h"

#include "ENUM.h"

NoteMove::NoteMove()
{
}


NoteMove::~NoteMove()
{
}


void NoteMove::Init()
{
	dir = {0.0f, 1.0f, __UI};
}

void NoteMove::Update()
{
	if (GetActor()->GetTransform()->GetPosition().y > 2.0f)
	{		
		Actor* actor = GetActor();		
		actor->Die();
	}

	speed = 0.5f;
	GetActor()->GetTransform()->Move2D((dir * speed * Time::DeltaTime()), 50.0f);
}