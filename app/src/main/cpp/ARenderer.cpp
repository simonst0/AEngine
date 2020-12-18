
#include "ARenderer.h"

glm::mat4 ARenderer::GetModelViewProjection()
{
    return  Projection * View * Model;
}

void ARenderer::OnSurfaceChanged()
{
    Shader->Initialize();
}
