#include "MoveLogic.h"
#include <list>


#include <RectRenderer.h>



MoveLogic::MoveLogic()
{

}

MoveLogic::~MoveLogic()
{

}

void MoveLogic::Init()
{

}


void MoveLogic::Update()
{
	std::vector<My_Ptr<RectRenderer>> componentList = GetActor()->GetComponentList<RectRenderer>();
	componentList[1]->SetRadian(0.0f);
	//componentList[1]->SetRadian(0.0f);
	//componentList[1]->SetLocalPosition(0.0f);
	//componentList[1]->SetLocalPosition({ 2.0f ,0.0f,0.0f });
	//componentList[1]->SetPosition({ 2.0f ,0.0f,0.0f });


	if (Input::Press(L"LEFT"))
	{
		GetActor()->GetTransform()->LocalMove( (Vector4::LEFT * 3.0f *Time::DeltaTime()) );
	}
	if (Input::Press(L"RIGHT"))
	{
		GetActor()->GetTransform()->LocalMove((Vector4::RIGHT * 3.0f* Time::DeltaTime()));
	}
	if (Input::Press(L"UP"))
	{
		GetActor()->GetTransform()->LocalMove((Vector4::UP * 3.0f* Time::DeltaTime()));
	}
	if (Input::Press(L"DOWN"))
	{
		GetActor()->GetTransform()->LocalMove((Vector4::DOWN * 3.0f* Time::DeltaTime()));
	}
	if (Input::Press(L"ZPROT"))
	{
		GetActor()->GetTransform()->RadianPlus_Z((3.0f * Time::DeltaTime()));
	}
	if (Input::Press(L"ZMROT"))
	{
		GetActor()->GetTransform()->RadianPlus_Z((-3.0f * Time::DeltaTime()));
	}
}