#pragma once
#include "Collider.h"


class BoundingSphere : public Collider
{	
public:
	friend class BoundingBox;

private:
	enum MODE
	{
		CIRCLE, SPHERE,
	};

private:
	MODE type;
	DirectX::BoundingSphere colliderData;

	bool isSetRadius;
	
public:
	void MultipleRadius(float _Value);


	

public:
	void ColBefore() override;
	bool GeometryCheck(Collider* _Other) override;



public:
	BoundingSphere();
	~BoundingSphere();
};

