#pragma once
#include "AComponent.h"
#include "Util.h"
#include "BodyComponent.h"


#include <Box2D/Common/b2Math.h>

class PlayerComponent : public AComponent{
public:
    void Update(float deltaTime) override;
    void Initialize() override;
    void OnCollisionBegin(GameObject *other) override;
    void OnCollisionEnd(GameObject *other) override;
    void Accelerate();
    void SetOrientation(b2Vec2 orientation) {Orientation = orientation; Orientation.Normalize();};
private:
    BodyComponent* BodyReference;
    b2Vec2 Orientation;
    void ResetPlayer();
    void ChangePlayerColor();
    Color GetRandomColor();
    b2Vec2 PlayerStartPosition = b2Vec2(150, 150);
    bool ShouldReset = false;
};


