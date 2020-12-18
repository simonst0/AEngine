#pragma once

#include "AComponent.h"
#include "Util.h"
#include "Texture.h"


class ParticleSystemComponent : public AComponent {
public:
    void Update(float deltaTime) override;
    void Initialize() override;
    void ResetSystem();
    ~ParticleSystemComponent();

    u_int MaxParticleCount = 100000;
    float delta = 0.032f;

    float minVelocity = -50;
    float maxVelocity = 50;
    VertexData* speed;

    float minSize = 1;
    float maxSize = 32;
    float* size;

    float life = 10.0f;
    VertexData* positions;

    VertexData emitterPosition;
    Texture* texture;

private:
    float lifeSaved;
};


