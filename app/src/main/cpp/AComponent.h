#pragma once

#include <string>

class GameObject;

class AComponent
{
public:
	AComponent(){}
	~AComponent() {}
	GameObject* gameObject;
	virtual void Update(float deltaTime) = 0;
	virtual void Initialize() = 0;
    virtual void OnCollisionBegin(GameObject *other) {};
    virtual void OnCollisionEnd(GameObject *other) {};
    virtual void SetActive(bool active) {Active = active;};
    bool IsActive(){return Active;};
protected:
    bool Active = true;
};

