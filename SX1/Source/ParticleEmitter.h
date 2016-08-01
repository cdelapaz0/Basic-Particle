#pragma once

#include "DXTKInclude.h"
#include "EmitterAttributes.h"

class Particle;

class ParticleEmitter
{
public:
	ParticleEmitter(unsigned int _numParticles = 500u);

	void Update(float _fdt);
	void Initialize(const EmitterAttributes& _attribs);

	void SetAttributes(const EmitterAttributes& _attribs);

	void SetLifeRange(float minLife, float maxLife);
	void SetSizeRange(float startS, float endS);
	void SetColorRange(Color startCol, Color endCol);
	void SetVelocity(Vector3 startV, Vector3 endV);

	//GetParticleVerts
	unsigned int GetNumParticles() const;
	unsigned int GetNumAliveParticle() const;

private:
	// TODO: Add particle list
	Particle* particles;
	unsigned int numParticles;
	unsigned int numAliveParticles;

	Matrix worldMatrix;
	
	// TODO: Add Emission bounds

	EmitterAttributes attributes;
};