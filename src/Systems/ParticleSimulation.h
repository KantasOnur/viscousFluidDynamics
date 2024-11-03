#pragma once
#include "ParticleSystem.h"

class ParticleSimulation : BaseObject
{
private:
	struct Params
	{
		glm::vec3 gravity = { 0.0f, -9.81, 0.0f };
		float dt = 0.0001f;
	};

private:

	ParticleSystem* m_target;
	Params sim;
public:
	ParticleSimulation(ParticleSystem* target);
	void step();

};

