#include <Name.h>
#include <Debug.h>
#include <Input.h>
#include <MyTime.h>

#include "Renderer.h"
#include "Transform.h"
#include "Camera.h"
#include "Scene.h"

Renderer::Renderer()
{
	SetName(L"Renderer");
}


Renderer::~Renderer()
{
}

void Renderer::Init()
{
	if (nullptr == GetActor()->GetTransform())
	{
		BOOM;
	}
	//actorName = GetActor()->GetName();
	SetParentTransform(GetActor()->GetTransform());
}

void Renderer::Render(const My_Ptr<Camera>& _Camera)
{

}

void Renderer::DataCreate(int _Order)
{
	order = _Order;
	GetScene()->renderMgr.PushRenderer(this);
}

void Renderer::SceneChangeStart()
{
	GetScene()->renderMgr.PushRenderer(this);
}
