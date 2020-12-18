#include "SpriteRendererSingleton.h"
#include <jni.h>
#include "GameObject.h"
#include "BodyComponent.h"

SpriteRendererSingleton::SpriteRendererSingleton() : ARenderer()
{
    Projection = glm::ortho(0.0f, Resolution.x , 0.0f, Resolution.y, -1.0f, 1.0f);
    View = glm::lookAt(CameraPosition, CameraPosition + LookAtDirection, Up);
}

void SpriteRendererSingleton::Initialize(JNIEnv *env)
{
    Shader = new ShaderProgram(FileReader::read_text_file(env, "shader.vert").c_str(),
                      FileReader::read_text_file(env, "shader.frag").c_str());
    Shader->Initialize();
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void SpriteRendererSingleton::Render()
{
    for (int i = 0; i < Sprites.size(); ++i)
    {
        SpriteComponent* Sprite = Sprites[i];
        if(Sprite->IsActive())
        {
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, Sprite->GetVertices());
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, 0, Sprite->TexCoord);

            BodyComponent* Body = Sprite->gameObject->GetComponent<BodyComponent>();
            b2Vec2 Translation = Body->GetPosition();
            glm::vec3 glmTranslation = glm::vec3(Translation.x, Translation.y, 0.f);
            float Rotation = Body->GetRotation();
            Model = glm::mat4(1.0f);
            Model = glm::translate(Model, glmTranslation);
            Model = glm::rotate(Model, Rotation, glm::vec3(0.0f,0.0f,1.0f));
            glm::mat4 MVP = GetModelViewProjection();
            glUniformMatrix4fv(Shader->GetUniformLocation("modelViewProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(MVP));

            Color c = Sprite->SpriteColor;
            glUniform4f(Shader->GetUniformLocation("color"), c.r, c.g, c.b, c.a);

            GLint UseTextureLocation = Shader->GetUniformLocation("useTex");
            if(Sprite->SpriteTexture != nullptr)
            {
                glBindTexture(GL_TEXTURE_2D, Sprite->SpriteTexture->TextureHandle);
                glUniform1i(Shader->GetUniformLocation("mainTex"), 0);
                glUniform1i(UseTextureLocation, 1);
            }
            else
            {
                glUniform1i(UseTextureLocation, 0);
            }
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }
    }
}

void SpriteRendererSingleton::PreRender()
{
    Shader->EnableProgram();
    glEnable(GL_BLEND);
}

void SpriteRendererSingleton::PostRender()
{
    Shader->DisableProgram();
    glDisable(GL_BLEND);
}

void SpriteRendererSingleton::AddSpriteComponent(SpriteComponent *sprite)
{
    Sprites.push_back(sprite);
}

void SpriteRendererSingleton::AddSpriteComponent(GameObject *gameObject)
{
    auto Component = gameObject->GetComponent<SpriteComponent>();
    if(!Component)
        return;;
    AddSpriteComponent(Component);
}