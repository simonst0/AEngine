#pragma once
#include "ARenderer.h"
#include "ParticleSystemComponent.h"
#include <GLES2/gl2ext.h>

class ParticleRendererSingleton : public  ARenderer{

public:
    static ParticleRendererSingleton& instance()
    {
        static ParticleRendererSingleton _instance;
        return _instance;
    }
private:
    ParticleRendererSingleton();
    ParticleRendererSingleton( const ParticleRendererSingleton& );
    ParticleRendererSingleton& operator = (const ParticleRendererSingleton&);

public:
    virtual void Render();
    virtual void PreRender();
    virtual void PostRender();
    virtual void Initialize(JNIEnv *env);

    void AddParticleSystem(ParticleSystemComponent* system);

private:
    std::vector<ParticleSystemComponent*> ParticleSystems;
    glm::mat4 VP;
};


