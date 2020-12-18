#pragma once

#include <Box2D/Box2D.h>
#include "AComponent.h"
#include <functional>

class BodyComponent : public AComponent
{
public:
    BodyComponent();
    void Update(float deltaTime) override;
    void Initialize() override;
    b2Vec2 GetPosition();
    float GetRotation();
    void SetPosition(b2Vec2 position);
    void SetVelocity(b2Vec2 velocity);
    void SetRotation(float rotation);
    void ApplyImpulse(b2Vec2 impulse);
    void ApplyForce(b2Vec2 force);
    void SetActive(bool active) override;
    b2Body* GetBody(){return Body;};


    b2BodyType type;
    b2Vec2 position;
    float angle;
    float linearDamping;
    float angularDamping;

protected:
    b2Body* Body;
};


