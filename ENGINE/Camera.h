#pragma once
#include "Component.h"
#include <set>

enum PROJMODE
{
	PERSPECTIVE,
	ORTHOGONAL,	
};

class Camera final : public Component
{
private:
	static Camera* mainCamera;

public:
	static Camera* MainCamera()
	{
		return mainCamera;
	}

private:
	PROJMODE mode;

	Matrix viewMatrix;
	Matrix projectionMatrix;
	Matrix viewPortMatrix;

	

	std::set<int> groupList;
	float fov;
	float width;
	float height;
	float nearPlane;
	float farPlane;
	
public:
	void SetArea(float _Width, float _Height)
	{
		SetWidth(_Width);
		SetHeight(_Height);
	}
	void SetWidth(float _Width)	{ width = _Width; }
	void SetHeight(float _Height) { height= _Height; }
	void SetProjMode(PROJMODE _Mode) { mode = _Mode; }

public:
	bool isAllView;
	bool IsAllView()
	{
		return isAllView;
	}
	int order;
	int GetOrder()
	{
		return order;
	}
	void SetOrder(int _Order);

	inline bool IsRender(int _Order)
	{
		return groupList.find(_Order) != groupList.end();
	}

	template<typename... Types>
	void DataCreate(Types&&... _Args)
	{
		PushRenderGroup(_Args...);
		return;
	}

	template<typename... Types>
	void PushRenderGroup(int _Order, Types&&... _Args)
	{
		if (groupList.find(_Order) != groupList.end())
		{
			BOOM;
			return;
		}

		groupList.insert(_Order);
		PushRenderGroup(_Args...);
	}
	void PushRenderGroup() {}

public:
	Matrix GetProjectionMatrix() { return projectionMatrix; }
	Matrix GetViewMatrix() { return viewMatrix; }
	Matrix GetViewPortMatrix() { return viewPortMatrix; }

public:
	Vector4 GetOrthMousePos();

public:
	void Init() override;

private:
	void RenderObjBefore() override;

public:
	Camera();
	~Camera();
};

