#include "CarSteeringComponent.h"
#include "GameObject.h"

void CarSteeringComponent::Update(float deltaTime)
{

}

void CarSteeringComponent::Initialize()
{
    BodyReference = gameObject->GetComponent<BodyComponent>();
}

void CarSteeringComponent::Accelerate()
{
    if(BodyReference)
    {
        float CurrentOrientation = BodyReference->GetRotation();
        b2Rot DesiredRotation;
        DesiredRotation.c = Steering.x;
        DesiredRotation.s = Steering.y;
        float DesiredFloatRotation = DesiredRotation.GetAngle();
        float DeltaOrientation = (DesiredFloatRotation - CurrentOrientation) * SteeringRate;
        BodyReference->SetRotation(CurrentOrientation + DeltaOrientation);
        DesiredRotation.Set(CurrentOrientation + DeltaOrientation);
        b2Vec2 CurrentForwardVector = b2Vec2(DesiredRotation.GetXAxis().x, DesiredRotation.GetYAxis().y);
        BodyReference->ApplyForce(-10000 * CurrentForwardVector);
        BodyReference->ApplyImpulse(-150 * CurrentForwardVector);
    }
}
