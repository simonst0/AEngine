#pragma once

#include <string>
#include "AComponent.h"
#include "Util.h"
#include "Scene.h"
#include <vector>

class GameObject
{
public:
	std::string NameTag = "";
	int AllocationId = -1;
	std::vector<AComponent*> Components;
	Scene* SceneReference;


    void Initialize();
	void Update(float deltaTime);
	void AddComponent(AComponent* component);
	void OnCollisionBegin(GameObject *other);
	void OnCollisionEnd(GameObject* other);
	void SetActive(bool active);
private:
	bool Active = true;
public:
	template<class T>
	T* GetComponent()
	{
        for (int i = 0; i < Components.size(); ++i)
        {
            AComponent* component = Components[i];
            T* ComponentAsT = dynamic_cast<T*>(component);
            if(ComponentAsT)
                return ComponentAsT;
        }
        return nullptr;
	};
};