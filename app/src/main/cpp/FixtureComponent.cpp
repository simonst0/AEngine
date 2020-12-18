
#include "FixtureComponent.h"
#include "BodyComponent.h"
#include "Util.h"
#include "GameObject.h"

void FixtureComponent::Update(float deltaTime)
{

}

void FixtureComponent::Initialize()
{
    BodyComponent* Body = gameObject->GetComponent<BodyComponent>();
    if(!Body)
    {
        log_debug("Component initialization order incorrect or no BodyComponent on %s", gameObject->NameTag.c_str());
        return;
    }

    b2PolygonShape polygonShape;
    b2CircleShape circleShape;
    switch(fixtureData.type)
    {
        case Box:
            polygonShape.SetAsBox(fixtureData.width/2, fixtureData.height/2, fixtureData.position, fixtureData.angle);
            FixtureDef.density = fixtureData.mass / (fixtureData.width * fixtureData.height);
            FixtureDef.shape = &polygonShape;
            break;
        case Circle:
            circleShape.m_radius = fixtureData.radius;
            circleShape.m_p = fixtureData.position;
            FixtureDef.density = fixtureData.mass / (fixtureData.radius * fixtureData.radius * 3.141592f);
            FixtureDef.shape = &circleShape;
            break;
    }
    FixtureDef.isSensor = IsTrigger;
    if(Body && Body->GetBody())
        Fixture = Body->GetBody()->CreateFixture(&FixtureDef);
    else
        log_debug("initialization order incorrect, trying to add fixture to uninitialized body");
}
