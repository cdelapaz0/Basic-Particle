#pragma once

#include "DXTKInclude.h"

class ParticleEmitter
{
public:
	ParticleEmitter(unsigned int NumParticles = 500u);

	void Update(float _fdt);

	void SetSizeRange(float startS, float endS);
	void SetColorRange(float startCol, float endCol);
	void SetVelocity(float startV, float endV);

private:
	// TODO: Add particle list

	Matrix worldMatrix;
	
	// TODO: Add Emission bounds

	float startSize;
	float endSize;

	Color startColor;
	Color endColor;

	Vector3 startVelocity;
	Vector3 endVelocity;
};