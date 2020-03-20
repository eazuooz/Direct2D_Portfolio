#include "Camera.h"
#include "Transform.h"
#include "Scene.h"
#include "GameWindow.h"


Camera* Camera::mainCamera = nullptr;

Camera::Camera() : isAllView(false), order(0), fov(60.0f), nearPlane(1.0f), farPlane(1000.0f), groupList(std::set<int>())
{
}


Camera::~Camera()
{
}

void Camera::SetOrder(int _Order)
{
	order = _Order;
	GetScene()->renderMgr.SortByCameraOrder();
}

Vector4 Camera::GetOrthMousePos()
{
	Vector4 pos = GameWindow::Inst()->MousePos();
	
	pos.y *= -1.0f;
	pos.x -= GameWindow::Inst()->GetWindowSize().x * 0.5f;
	pos.y += GameWindow::Inst()->GetWindowSize().y * 0.5f;

	float XRatio = width  / GameWindow::Inst()->GetWindowSize().x;
	float YRatio = height / GameWindow::Inst()->GetWindowSize().y;

	// 10 / 600;

	pos.x *= XRatio;
	pos.y *= YRatio;

	pos += GetTransform()->GetPosition();


	return pos;
	//actor->GetTransform()->SetLocalPosition(pos);
}

void Camera::Init()
{
	if (nullptr == GetActor()->GetTransform())
	{
		BOOM;
	}

	if (nullptr == mainCamera)
	{
		mainCamera = this;
	}
	height	= GetActor()->GetScene()->GetWindow()->GetWindowSize().y;
	width	= GetActor()->GetScene()->GetWindow()->GetWindowSize().x;




	GetScene()->renderMgr.PushCamera(this);
}

void Camera::RenderObjBefore()
{
	viewMatrix.SetViewMatrix(GetActor()->GetTransform()->GetPosition(), GetActor()->GetTransform()->LookForward(), GetActor()->GetTransform()->LookUp());
	

	switch (mode)
	{
	case PROJMODE::PERSPECTIVE:
		projectionMatrix.SetPerspectiveMatrix(fov, width, height, nearPlane, farPlane);
		break;
	case PROJMODE::ORTHOGONAL:
		projectionMatrix.SetOrthgonalMatrix( width, height, nearPlane, farPlane);
		break;
	default:
		break;
	}

	viewPortMatrix = viewMatrix * projectionMatrix;
}
