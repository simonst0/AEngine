#include "Scene.h"
#include "GameObject.h"
#include "CollisionContactListenerSingleton.h"

Scene::Scene(b2Vec2 gravity)
{
    PhysicsWorld = new b2World(gravity);
    PhysicsWorld->SetContactListener(&CollisionContactListenerSingleton::instance());
}

void Scene::Update(float deltaTime)
{
    if(Paused)
        return;
    for (int i = 0; i < GameObjects.size(); ++i) {
            GameObjects[i]->Update(deltaTime);
    }
    PhysicsWorld->Step(PhysicsTimestep, 1, 1);
}

void Scene::Initialize()
{
    for (int i = 0; i < GameObjects.size(); ++i)
    {
        GameObjects[i]->Initialize();
    }
    PhysicsTimestep= 1.0f/PhysicsFPS;
}

void Scene::AddGameObject(GameObject* gameObject)
{
    if(std::find(GameObjects.begin(), GameObjects.end(), gameObject) == GameObjects.end()) //does not contain object yet
    {
        GameObjects.push_back(gameObject);
        gameObject->SceneReference = this;
        SpriteRendererSingleton::instance().AddSpriteComponent(gameObject);
    }
}

void Scene::RemoveGameObject(GameObject* gameObject){
    auto it = std::find(GameObjects.begin(), GameObjects.end(), gameObject);
    if(it != GameObjects.end())
    {
        GameObjects.erase(it);
        gameObject->SceneReference = nullptr;
    }
}

Scene::~Scene()
{
    delete PhysicsWorld;
}

void Scene::SetGravity(b2Vec2 gravity)
{
    PhysicsWorld->SetGravity(gravity);
}

void Scene::Pause()
{
    Paused = true;
}

void Scene::Resume()
{
    Paused = false;
}
