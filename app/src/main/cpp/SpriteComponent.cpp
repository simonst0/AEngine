
#include "SpriteComponent.h"

void SpriteComponent::Update(float deltaTime)
{

}

void SpriteComponent::Initialize()
{
    MakeVertexPositionData();
    MakeVertexColorData();
}

SpriteComponent::~SpriteComponent()
{

}

void SpriteComponent::MakeVertexPositionData()
{
    Vertices [0] = VertexData(-0.5f*Width, -0.5f*Height);
    Vertices [1] = VertexData(-0.5f*Width, 0.5f*Height);
    Vertices [2] = VertexData(0.5f*Width, -0.5f*Height);
    Vertices [3] = VertexData(-0.5f*Width, 0.5f*Height);
    Vertices [4] = VertexData(0.5f*Width, 0.5f*Height);
    Vertices [5] = VertexData(0.5f*Width, -0.5f*Height);
}

void SpriteComponent::MakeVertexColorData()
{
    for (int i = 0; i < 6; ++i) {
        VertexColor[i] = SpriteColor;
    }
}
