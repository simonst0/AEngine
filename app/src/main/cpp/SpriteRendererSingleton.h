#pragma once

#include "SpriteComponent.h"
#include <GLES2/gl2.h>
#include <vector>
#include "ARenderer.h"

class SpriteRendererSingleton : public ARenderer {

public:
    static SpriteRendererSingleton& instance()
    {
        static SpriteRendererSingleton _instance;
        return _instance;
    }
private:
    SpriteRendererSingleton();
    SpriteRendererSingleton( const SpriteRendererSingleton& );
    SpriteRendererSingleton& operator = (const SpriteRendererSingleton&);


public:
    void AddSpriteComponent(SpriteComponent* sprite);
    void AddSpriteComponent(GameObject* gameObject);

    void Initialize(JNIEnv *env) override;
    void Render() override;
    void PreRender() override;
    void PostRender() override;

private:
    std::vector<SpriteComponent*> Sprites;
};


