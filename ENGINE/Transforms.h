#pragma once
#include "Transform.h"

class Transforms :	public Transform
{
private:
	bool rotateLock;
	bool positionLock;
	bool scaleLock;

public:
	Transforms();
	~Transforms();
};

