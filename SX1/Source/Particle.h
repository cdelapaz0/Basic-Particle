#pragma once

#include "DXTKInclude.h"
#include "ParticleVertex.h"


struct Particle
{
	float			lifeTime = 0;
	float			totalLifeTime = 0;
	bool			alive = false;

	Vector3			velocity = Vector3::Zero;
	float			rot = 0;

	ParticleVertex	vert;
};
