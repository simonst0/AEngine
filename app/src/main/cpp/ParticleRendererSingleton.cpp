#include "ParticleRendererSingleton.h"
#include "Util.h"

ParticleRendererSingleton::ParticleRendererSingleton() : ARenderer()
{
    Projection = glm::ortho(0.0f, Resolution.x , 0.0f, Resolution.y, -1.0f, 1.0f);
    View = glm::lookAt(CameraPosition, CameraPosition + LookAtDirection, Up);
    VP = Projection * View;
}


void ParticleRendererSingleton::Initialize(JNIEnv *env)
{
    Shader = new ShaderProgram(FileReader::read_text_file(env, "particle.vert").c_str(),
                               FileReader::read_text_file(env, "particle.frag").c_str());
    Shader->Initialize();
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ParticleRendererSingleton::Render()
{
    glUniformMatrix4fv(Shader->GetUniformLocation("modelViewProjectionMatrix"), 1, GL_FALSE, glm::value_ptr(VP));
    for(auto system : ParticleSystems)
    {
        if(system->IsActive())
        {
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, system->positions);
            glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 0, system->size);

            glBindTexture(GL_TEXTURE_2D, system->texture->TextureHandle);
            glUniform1i(Shader->GetUniformLocation("mainTex"), 0);

            glDrawArrays(GL_POINTS,0, system->MaxParticleCount);
        }
    }
}

void ParticleRendererSingleton::PreRender()
{
    Shader->EnableProgram();
    glEnable(GL_BLEND);
}

void ParticleRendererSingleton::PostRender()
{
    Shader->DisableProgram();
    glDisable(GL_BLEND);
}

void ParticleRendererSingleton::AddParticleSystem(ParticleSystemComponent *system)
{
    if(system)
        ParticleSystems.push_back(system);
}
