#pragma once

#include <jni.h>
#include "Shader.h"
#include "glm/glm.hpp"

class ARenderer{
public:
    virtual void Render() = 0;
    virtual void PreRender() = 0;
    virtual void PostRender() = 0;
    virtual void Initialize(JNIEnv* env) = 0;
    void OnSurfaceChanged();
    glm::mat4 GetModelViewProjection();

    glm::vec3 CameraPosition = glm::vec3(0, 0, 0);
    glm::vec3 LookAtDirection = glm::vec3(0,0, -1);
    glm::vec3 Up = glm::vec3(0,1,0);
    glm::vec2 Resolution = glm::vec2(1080.0f, 1920.0f);

    glm::mat4 View;
    glm::mat4 Projection;
    glm::mat4 Model;

    ARenderer(){};
    ~ARenderer(){delete Shader;};

protected:
    ShaderProgram* Shader;
};


