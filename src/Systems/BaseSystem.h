#pragma once
#include "BaseObject.h"
#include "../Core/Mesh.h"
#include <memory>

class BaseSystem : public BaseObject
{
public:
	BaseSystem() : BaseObject() {};
	virtual void getState(void* p) const { assert("Implement me!"); };
	virtual void setState(void* p) { assert("Implement me!"); };
protected:
	//std::unique_ptr<Mesh> m_mesh;
	void* m_state;
};
