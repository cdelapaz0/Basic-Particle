#include "ParticleEmitter.h"
#include "Particle.h"

ParticleEmitter::ParticleEmitter(unsigned int _numParticles)
{
	particles = new Particle[_numParticles];
	numParticles = _numParticles;
}

void ParticleEmitter::Update(float _fdt)
{
	numAliveParticles = 0;
	for (unsigned int i = 0; i < numParticles; i++)
	{
		if (particles[i].Update(_fdt, attributes))
		{
			numAliveParticles++;
		}
	}
}

void ParticleEmitter::Initialize(const EmitterAttributes & _attribs)
{
	attributes = _attribs;
	for (unsigned int i = 0; i < numParticles; i++)
	{
		particles[i].Initialize(_attribs);
	}
}

void ParticleEmitter::SetAttributes(const EmitterAttributes & _attribs)
{
	attributes = _attribs;
}

void ParticleEmitter::SetLifeRange(float minLife, float maxLife)
{
	attributes.minLifeTime = minLife;
	attributes.maxLifeTime = maxLife;
}

void ParticleEmitter::SetSizeRange(float startS, float endS)
{
	attributes.startSize = startS;
	attributes.endSize = endS;
}

void ParticleEmitter::SetColorRange(Color startCol, Color endCol)
{
	attributes.startColor = startCol;
	attributes.endColor = endCol;
}

void ParticleEmitter::SetVelocity(Vector3 startV, Vector3 endV)
{
	attributes.startVelocity = startV;
	attributes.endVelocity = endV;
}

unsigned int ParticleEmitter::GetNumParticles() const
{
	return numParticles;
}

unsigned int ParticleEmitter::GetNumAliveParticle() const
{
	return numAliveParticles;
}
