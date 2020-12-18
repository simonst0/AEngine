#include "GameObject.h"

void GameObject::Update(float deltaTime)
{
    for (auto& component : Components) {
         component->Update(deltaTime);
    }
}

void GameObject::Initialize()
{
    for (auto component : Components)
    {
        component->Initialize();
    }
}

void GameObject::AddComponent(AComponent* component)
{
    Components.push_back(component);
}

void GameObject::OnCollisionBegin(GameObject *other)
{
    for (auto Component : Components)
        Component->OnCollisionBegin(other);
}

void GameObject::OnCollisionEnd(GameObject *other)
{    for (auto Component : Components)
        Component->OnCollisionEnd(other);
}

void GameObject::SetActive(bool active)
{
    for (auto Component : Components)
        Component->SetActive(active);
    Active = active;
}