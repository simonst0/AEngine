#pragma once

#include <vector>
#include <Box2D/Dynamics/b2World.h>
#include "SpriteRendererSingleton.h"
#include <jni.h>

#include <thread>
#include <chrono>

class GameObject;

class Scene{
public:
    Scene(b2Vec2 gravity  = b2Vec2(0.0f ,0.0f));
    ~Scene();
    void Update(float deltaTime);
    void Initialize();
    void AddGameObject(GameObject* gameObject);
    void RemoveGameObject(GameObject* gameObject);
    b2World* GetWorld(){return PhysicsWorld;};
    void Pause();
    void Resume();
    void SetGravity(b2Vec2 gravity);
private:
    std::vector<GameObject*> GameObjects;
    b2World* PhysicsWorld;
    bool Paused = false;

    float PhysicsFPS = 120;
    float PhysicsTimestep = 0;
};


