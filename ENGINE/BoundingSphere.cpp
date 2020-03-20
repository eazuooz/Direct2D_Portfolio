#include "BoundingSphere.h"
#include "GraphicDebug.h"
#include "Transform.h"
#include "BoundingBox.h"

BoundingSphere::BoundingSphere() : type(CIRCLE), isSetRadius(false)
{
}


BoundingSphere::~BoundingSphere()
{
}

void BoundingSphere::MultipleRadius(float _Value)
{
	colliderData.Radius = GetTransform()->GetLocalScale().diameter * 0.5f;
	colliderData.Radius *= _Value;
	isSetRadius = true;
}

void BoundingSphere::ColBefore()
{
	// xyz 중 제일큰 녀석의 절반
	DebugCheck();
	UpdateTransform();

	colliderData.Center = GetTransform()->GetLocalPosition().xmFloat3;
	if (type == CIRCLE)
	{
		colliderData.Center.z = 0.0f;
	}

	if (isSetRadius == false)
	{
		colliderData.Radius = GetTransform()->GetLocalScale().diameter * 0.5f;	//diameter * 0.5f == radius
		//colliderData.Radius = GetLocalScale().diameter * 0.5f;
	}
	else
	{
		//colliderData.Radius = colliderData.Radius;
	}

	if (true == GraphicDebug::IsDebugCheck())
	{
		Matrix temp = GetWorldMatrix();

		temp.Arr2D[0][0] = colliderData.Radius * 2.0f;
		temp.Arr2D[1][1] = colliderData.Radius * 2.0f;



		GraphicDebug::DrawSphere(Camera::MainCamera(), temp);
	}
}

bool BoundingSphere::GeometryCheck(Collider* _Other)
{
	if (true == _Other->CompareType<BoundingSphere>())
	{
		return colliderData.Intersects(((BoundingSphere*)_Other)->colliderData);
	}
	else if (true == _Other->CompareType<BoundingBox>())
	{
		return colliderData.Intersects(((BoundingBox*)_Other)->colliderData);
	}

	return true;
}
