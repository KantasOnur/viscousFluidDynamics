#pragma once
#include <cassert>
#include "../Core/Camera.h"

class BaseObject
{
public:
	BaseObject() = default;
	virtual void render(const Camera& camera) { assert("Implement me!"); };
};

