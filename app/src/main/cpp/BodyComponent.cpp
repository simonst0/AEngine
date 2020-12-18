
#include "BodyComponent.h"
#include "GameObject.h"
#include "CollisionContactListenerSingleton.h"

void BodyComponent::Update(float deltaTime)
{

}

void BodyComponent::Initialize()
{
    b2BodyDef def;
    def.position = position;
    def.angle = angle;
    def.angularDamping = angularDamping;
    def.linearDamping = linearDamping;
    def.type = type;
    Body = gameObject->SceneReference->GetWorld()->CreateBody(&def);
    Body->SetUserData(gameObject);
}

b2Vec2 BodyComponent::GetPosition() {
    return Body->GetPosition();
}

float BodyComponent::GetRotation() {
    return Body->GetAngle();
}

BodyComponent::BodyComponent()
{
    position.Set(0.0f, 0.0f);
    angle = 0.0f;
    linearDamping = 0.0f;
    angularDamping = 0.0f;
    type = b2_staticBody;
}

void BodyComponent::SetPosition(b2Vec2 position)
{
    float rotation = Body->GetTransform().q.GetAngle();
    Body->SetTransform(position, rotation);
}

void BodyComponent::SetVelocity(b2Vec2 velocity)
{
    Body->SetLinearVelocity(velocity);
}

void BodyComponent::ApplyImpulse(b2Vec2 impulse)
{
    Body->ApplyLinearImpulseToCenter(impulse, true);
}

void BodyComponent::ApplyForce(b2Vec2 force)
{
    Body->ApplyForceToCenter(force, true);
}


void BodyComponent::SetActive(bool active)
{
    AComponent::SetActive(active);
    Body->SetActive(active);
}

void BodyComponent::SetRotation(float rotation)
{
    Body->SetTransform(Body->GetTransform().p, rotation);
}
