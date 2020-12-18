#include "GameObjectFactory.h"

GameObjectFactory::GameObjectFactory(int objectCount)
{
	gameObjectFactory = new Factory<GameObject>(objectCount);
	bodyComponentFactory = new Factory<BodyComponent>(objectCount);
	spriteComponentFactory = new Factory<SpriteComponent>(objectCount);
	playerComponentFactory = new Factory<PlayerComponent>(objectCount);
	fixtureComponentFactory = new Factory<FixtureComponent>(objectCount);
	particleSystemComponentFactory = new Factory<ParticleSystemComponent>(objectCount);
}

GameObjectFactory::~GameObjectFactory()
{
	delete gameObjectFactory;
	delete bodyComponentFactory;
	delete spriteComponentFactory;
	delete playerComponentFactory;
	delete fixtureComponentFactory;
	delete particleSystemComponentFactory;
}

GameObject * GameObjectFactory::NewGameObject()
{
	GameObject* NewObject = gameObjectFactory->GetNew();
	NewObject->AllocationId = newCounter;
	newCounter++;
	return NewObject;
}

GameObject* GameObjectFactory::GenerateDefaultGameObject()
{
	GameObject* New = NewGameObject();
	AddSpriteComponent(New);
	AddBodyComponent(New);
	AddFixtureComponent(New);
	return New;
}

void GameObjectFactory::AddBodyComponent(GameObject* target)
{
	BodyComponent* Body = bodyComponentFactory->GetNew();
	target->AddComponent(Body);
	Body->gameObject = target;
}

void GameObjectFactory::AddSpriteComponent(GameObject *target)
{
	SpriteComponent* Sprite = spriteComponentFactory->GetNew();
	target->AddComponent(Sprite);
	Sprite->gameObject = target;
}

void GameObjectFactory::AddPlayerComponent(GameObject *target)
{
	PlayerComponent* Player = playerComponentFactory->GetNew();
	target->AddComponent(Player);
	Player->gameObject = target;
}

void GameObjectFactory::AddFixtureComponent(GameObject *target)
{
	FixtureComponent* Fixture = fixtureComponentFactory->GetNew();
	target->AddComponent(Fixture);
	Fixture->gameObject = target;
}

void GameObjectFactory::AddParticleSystemComponent(GameObject *target)
{
	ParticleSystemComponent* Particles = particleSystemComponentFactory->GetNew();
	target->AddComponent(Particles);
	Particles->gameObject = target;
}


