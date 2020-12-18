#pragma once

#include "Texture.h"
#include "AComponent.h"
#include "Util.h"

class SpriteComponent : public  AComponent{

public:
    SpriteComponent(){}
    ~SpriteComponent();
    virtual void Update(float deltaTime) override;
    virtual void Initialize() override;
    Texture* SpriteTexture = nullptr;

    // Vertex-Daten
    GLfloat Width = 1;
    GLfloat Height = 1;

    Color SpriteColor = Color(1,1,1,1);

    VertexData* GetVertices(){return Vertices;};
    Color* GetVertexColor(){return VertexColor;};
    void MakeVertexPositionData();
    void MakeVertexColorData();

    VertexData TexCoord[6] =
    {
        VertexData(0,1),
        VertexData(0,0),
        VertexData(1,1),
        VertexData(0,0),
        VertexData(1,0),
        VertexData(1,1)
    };

private:

    VertexData Vertices[6] = {
                VertexData(0, 0),
                VertexData(0, 0),
                VertexData(0, 0),
                VertexData(0, 0),
                VertexData(0, 0),
                VertexData(0, 0),
    };

    Color VertexColor[6] = {
            Color(1,1,1,1),
            Color(1,1,1,1),
            Color(1,1,1,1),
            Color(1,1,1,1),
            Color(1,1,1,1),
            Color(1,1,1,1)
    };
};


