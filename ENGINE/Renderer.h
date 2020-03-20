#pragma once

#include "Camera.h"
#include "Actor.h"
#include "Transforms.h"

class RenderManager;
class Renderer : public Transforms
{
//private:
//	std::wstring actorName;

public:
	friend RenderManager;

public:
	virtual void Init();

private:
	int order;
	int GetOrder()
	{
		return order;
	}
	void SetOrder(int _Order)
	{
		order = _Order;
	}

private:	
	virtual void Render(const My_Ptr<Camera>& _Camera);

public:
	void DataCreate(int _Order);

public:
	void SceneChangeStart() override;

public:
	Renderer();
	~Renderer();
};

