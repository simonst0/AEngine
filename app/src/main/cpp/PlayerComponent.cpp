
#include "PlayerComponent.h"
#include "BodyComponent.h"
#include "GameObject.h"
#include "SoundControllerSingleton.h"
#include "ParticleSystemComponent.h"
#include <random>

void PlayerComponent::Update(float deltaTime)
{
    if(ShouldReset)
    {
        ResetPlayer();
        ShouldReset = false;
    }
    if(BodyReference)
    {
      b2Rot rotation;
      rotation.c = Orientation.x;
      rotation.s = Orientation.y;
      BodyReference->SetRotation(rotation.GetAngle() + 1.5708f);
    }
}

void PlayerComponent::Initialize()
{
    BodyReference = gameObject->GetComponent<BodyComponent>();
}

void PlayerComponent::OnCollisionBegin(GameObject *other)
{
    AComponent::OnCollisionBegin(other);
    if(other->NameTag == "Goal")
    {
        ChangePlayerColor();
        ShouldReset = true;
        SoundControllerSingleton::instance().PlaySound("goal");
    }
    if(other->NameTag == "Kill")
    {
        SoundControllerSingleton::instance().PlaySound("crash");
        auto Particles = gameObject->GetComponent<ParticleSystemComponent>();
        Particles->SetActive(true);
        b2Vec2 position = BodyReference->GetPosition();
        Particles->emitterPosition.x = position.x;
        Particles->emitterPosition.y = position.y;
        Particles->ResetSystem();
        ShouldReset = true;
    }
}

void PlayerComponent::OnCollisionEnd(GameObject *other)
{
    AComponent::OnCollisionEnd(other);
}

void PlayerComponent::ResetPlayer()
{
    if(BodyReference)
        BodyReference->SetPosition(PlayerStartPosition);
}

void PlayerComponent::ChangePlayerColor()
{
    SpriteComponent* sprite = gameObject->GetComponent<SpriteComponent>();
    if(!sprite)
        return;
    sprite->SpriteColor = GetRandomColor();
    sprite->MakeVertexColorData();
}

Color PlayerComponent::GetRandomColor()
{
    return Color(RandomFloat(0.0f,1.0f), RandomFloat(0.0f,1.0f), RandomFloat(0.0f,1.0f), 1);
}

void PlayerComponent::Accelerate()
{
    if(BodyReference)
    {
        BodyReference->ApplyForce(-10000 * Orientation);
        BodyReference->ApplyImpulse(-150 * Orientation);
    }
}