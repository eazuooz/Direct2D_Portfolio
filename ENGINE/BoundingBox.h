#pragma once
#include "Collider.h"

class BoundingBox : public Collider
{
public:
	friend class BoundingSphere;

private:
	enum MODE
	{
		PLANE,CUBE,
	};
	
	MODE type;
	DirectX::BoundingOrientedBox colliderData;
	Vector4 rot;

public:
	void ColBefore() override;
	bool GeometryCheck(Collider* _Other) override;

public:
	BoundingBox();
	~BoundingBox();
};

