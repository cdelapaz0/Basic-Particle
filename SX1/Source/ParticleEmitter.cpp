#include "ParticleEmitter.h"
#include "Utilities.h"

#include <algorithm>
using std::sort;
using std::begin;
using std::end;

bool compLifeGreater(const Particle& a, const Particle& b)
{
	return a.lifeTime > b.lifeTime;
}

ParticleEmitter::ParticleEmitter()
{

}

void ParticleEmitter::Initialize(unsigned int NumParticles, float startS, float endS, Color startCol, Color endCol, Vector3 startV, Vector3 endV, Vector3 pos, float minLT, float maxLT, float spawnI, unsigned int spawnCount, float spawnW, float spawnH)
{
	particles.resize(NumParticles);
	verts.resize(NumParticles);
	maxParticlesCount = NumParticles;
	aliveCount = 0;

	worldMatrix = Matrix::Identity;

	SetParticleSizeRange(startS, endS);
	SetParticleColorRange(startCol,endCol);
	SetParticleVelocityRange(startV, endV);
	SetParticleLifeTimeRange(minLT, maxLT);

	SetPosition(pos);
	SetSpawnInterval(spawnI);
	SetSpawnCount(spawnCount);
	SetSpawnBounds(spawnW, spawnH);

	elapsedTime = spawnInterval;
}

void ParticleEmitter::Update(float _fdt)
{
	elapsedTime += _fdt;
	if (elapsedTime >= spawnInterval)
	{
		elapsedTime -= spawnInterval;
		for (unsigned int i = 0; i < spawnAmount; i++)
		{
			unsigned int index = aliveCount;
			if (index < maxParticlesCount)
			{
				particles[index].alive = true;
				particles[index].lifeTime = Random::NextFloat(minLifeTime, maxLifeTime);
				particles[index].totalLifeTime = particles[index].lifeTime;
				particles[index].rot = 0;
				particles[index].velocity = Vector3::Zero;

				particles[index].vert.color = startColor;
				particles[index].vert.size = startSize;
				float x = Random::NextFloat(-boundWidth, boundWidth);
				float y = Random::NextFloat(-boundHeight, boundHeight);
				particles[index].vert.position = (worldMatrix.Translation() + Vector3(x, y, 0));
				aliveCount++;
			}
		}
	}


	unsigned int currAliveCount = aliveCount;
	for (unsigned int i = 0; i < aliveCount; ++i)
	{
		if (particles[i].alive)
		{
			particles[i].lifeTime -= _fdt;
			if (particles[i].lifeTime <= 0)
			{
				particles[i].lifeTime = 0;
				particles[i].alive = false;
				currAliveCount--;
				continue;
			}

			float r = particles[i].lifeTime / particles[i].totalLifeTime;

			particles[i].vert.color = Color::Lerp(endColor, startColor, r);
			particles[i].velocity = Vector3::Lerp(endVelocity, startVelocity, r);
			particles[i].vert.size = Math::Lerp(endSize, startSize, r);

			Vector3 pos = particles[i].vert.position + (particles[i].velocity * _fdt);
			particles[i].vert.position = pos;
		}
	}


	//sort
	sort(particles.begin(), particles.begin() + aliveCount, compLifeGreater);

	aliveCount = currAliveCount;
	for (unsigned int i = 0; i < aliveCount; i++)
	{
		verts[i] = particles[i].vert;
	}
}

void ParticleEmitter::SetParticleSizeRange(float startS, float endS)
{
	startSize = startS;
	endSize = endS;
}

void ParticleEmitter::SetParticleColorRange(Color startCol, Color endCol)
{
	startColor = startCol;
	endColor = endCol;
}

void ParticleEmitter::SetParticleVelocityRange(Vector3 startV, Vector3 endV)
{
	startVelocity = startV;
	endVelocity = endV;
}

void ParticleEmitter::SetPosition(Vector3 pos)
{
	worldMatrix.Translation(pos);
}

void ParticleEmitter::SetSpawnInterval(float spawnI)
{
	spawnInterval = spawnI;
}

void ParticleEmitter::SetSpawnCount(float spawnCount)
{
	spawnAmount = spawnCount;
}

void ParticleEmitter::SetSpawnBounds(float width, float height)
{
	boundWidth = width;
	boundHeight = height;
}


void ParticleEmitter::SetParticleLifeTimeRange(float minLT, float maxLT)
{
	minLifeTime = minLT;
	maxLifeTime = maxLT;
}

const Matrix & ParticleEmitter::GetWorldMatrix()
{
	return worldMatrix;
}

unsigned int ParticleEmitter::GetMaxParticleCount()
{
	return maxParticlesCount;
}

unsigned int ParticleEmitter::GetAliveCount()
{
	return aliveCount;
}

ParticleVertex * ParticleEmitter::GetVertexArray()
{
	return &verts[0];
}

unsigned int ParticleEmitter::GetVertexArraySize()
{
	return aliveCount * sizeof(ParticleVertex);
}
