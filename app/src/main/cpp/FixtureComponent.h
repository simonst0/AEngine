#pragma once

#include <Box2D/Dynamics/b2Fixture.h>
#include "AComponent.h"

enum FixtureType
{
    Box,
    Circle
};

struct FixtureData
{
    FixtureData(){};
    FixtureData(FixtureType type, b2Vec2 position, float width, float height, float angle = 0, float radius = -1, float mass = -1)
    {
        this->type = type;
        this->position = position;
        this->radius = radius;
        this->height = height;
        this->width = width;
        this->mass = mass;
        this->angle = angle;
    }
    FixtureType type;
    b2Vec2 position;
    float width;
    float height;
    float radius;
    float mass;
    float angle;
};

class FixtureComponent : public AComponent{
public:
    void Update(float deltaTime) override;
    void Initialize() override;
    FixtureData fixtureData;
    bool IsTrigger = false;

protected:
    b2FixtureDef FixtureDef;
    b2Fixture* Fixture;
};


