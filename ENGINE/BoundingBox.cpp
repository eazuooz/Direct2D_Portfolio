#include "BoundingBox.h"
#include "Transform.h"
#include "GraphicDebug.h"
#include "BoundingSphere.h"


BoundingBox::BoundingBox() : type(PLANE)
{
}


BoundingBox::~BoundingBox()
{
}


void BoundingBox::ColBefore()
{
	DebugCheck();
	UpdateTransform();

	colliderData.Center		= GetTransform()->GetLocalPosition().xmFloat3;
	colliderData.Extents	= (GetTransform()->GetLocalScale() * 0.5f).xmFloat3;

	if (type == PLANE)
	{
		colliderData.Center.z = 0.0f;
		colliderData.Extents.z = 1.0f;
	}

	rot = GetTransform()->GetRadian();

	DirectX::XMStoreFloat4(&colliderData.Orientation, DirectX::XMQuaternionRotationRollPitchYaw(rot.x, rot.y, rot.z));

	if (true == GraphicDebug::IsDebugCheck())
	{
		GraphicDebug::DrawSquare(Camera::MainCamera(), GetWorldMatrix());
	}
}

bool BoundingBox::GeometryCheck(Collider* _Other)
{
	if (true == _Other->CompareType<BoundingBox>()) //IsType<H3DOBBCOL>())
	{
		return colliderData.Intersects(((BoundingBox*)_Other)->colliderData);
	}
	else 	if (true == _Other->CompareType<BoundingSphere>()) //IsType<H3DOBBCOL>())
	{
		return colliderData.Intersects(((BoundingSphere*)_Other)->colliderData);
	}

	return true;
}
