#pragma once
#include <Box2D/Common/b2Math.h>
#include "AComponent.h"
#include "BodyComponent.h"

class CarSteeringComponent :  public AComponent {
public:
    void Accelerate();
    void SetSteering(b2Vec2 steering) {Steering.x = b2Clamp(steering.x, -1.0f, 1.0f); Steering.y = b2Clamp(steering.y, -1.0f, 1.0f);}
    void Update(float deltaTime) override;
    void Initialize() override;

    float SteeringRate = 0.01f;

private:
    BodyComponent* BodyReference;
    b2Vec2 Steering;
};