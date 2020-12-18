#include "ParticleSystemComponent.h"
#include "glm/glm.hpp"

void ParticleSystemComponent::Update(float deltaTime)
{
    life -= deltaTime;
    if(life <= 0)
    {
        ResetSystem();
        SetActive(false);
    }
    for (int i = 0; i < MaxParticleCount; ++i)
    {
        positions[i].x += speed[i].x * delta;
        positions[i].y += speed[i].y * delta;
    }
}

void ParticleSystemComponent::Initialize()
{
    lifeSaved = life;
    positions = new VertexData[MaxParticleCount];
    speed = new VertexData[MaxParticleCount];
    size = new float[MaxParticleCount];
    log_debug("Max particle count %d", MaxParticleCount);
    ResetSystem();
}

ParticleSystemComponent::~ParticleSystemComponent()
{
	delete[] positions;
	delete[] speed;
	delete[] size;
}

void ParticleSystemComponent::ResetSystem()
{
    for (int i = 0; i < MaxParticleCount; ++i)
    {
        speed[i].x = RandomFloat(minVelocity, maxVelocity);
        speed[i].y = RandomFloat(minVelocity, maxVelocity);
        positions[i].x = emitterPosition.x;
        positions[i].y = emitterPosition.y;
        size[i] = RandomFloat(minSize, maxSize);
        life = lifeSaved;
    }
}
