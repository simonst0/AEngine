#pragma once
#include "GameObject.h"
#include "FactoryTemplate.h"
#include "BodyComponent.h"
#include "SpriteComponent.h"
#include "PlayerComponent.h"
#include "FixtureComponent.h"
#include "ParticleSystemComponent.h"
#include <vector>

class GameObjectFactory
{
private:
	Factory<GameObject>* gameObjectFactory;
	Factory<BodyComponent>* bodyComponentFactory;
	Factory<SpriteComponent>* spriteComponentFactory;
	Factory<PlayerComponent>* playerComponentFactory;
	Factory<FixtureComponent>* fixtureComponentFactory;
	Factory<ParticleSystemComponent>* particleSystemComponentFactory;
	int newCounter = 0;

public:
	GameObjectFactory(int objectCount);
	~GameObjectFactory();
	GameObject* NewGameObject();
	void AddBodyComponent(GameObject* target);
	void AddSpriteComponent(GameObject* target);
	void AddPlayerComponent(GameObject* target);
	void AddFixtureComponent(GameObject* target);
	void AddParticleSystemComponent(GameObject* target);

	GameObject* GenerateDefaultGameObject();
};

