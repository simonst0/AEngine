#pragma once
#include <unordered_map>
#include "FactoryTemplate.h"
#include "BodyComponent.h"
#include "GameObject.h"
#include "Util.h"
#include "FixtureComponent.h"

class TileMap {
public:
    TileMap(std::vector<int> tileIndices, int mapSizeX, int mapSizeY, int spriteSheetSizeX, int spriteSheetSizeY, float tileSize, b2Vec2 position);
    void SetTileTexture(Texture* texture);
    void GenerateObjects();
    void RegisterTilesToScene(Scene* scene);
    void AddFixtureDataToTile(int tileId, FixtureData fixtureData);
    ~TileMap();
private:
    b2Vec2 Position;
    float TileSize;
    float AntiPositionErrorOffset = 0.001f;
    int MapSizeX;
    int MapSizeY;
    int SpriteSheetSizeX;
    int SpriteSheetSizeY;
    Texture* TileTexture;
    std::vector<int> TileIndices;
    std::vector<GameObject*> Tiles;
    Factory<GameObject>* GameObjectFactory;
    Factory<SpriteComponent>* SpriteComponentFactory;
    Factory<BodyComponent>* BodyComponentFactory;
    Factory<FixtureComponent>* FixtureComponentFactory;
    std::vector<VertexData*> TileUVCoordinates;
    std::unordered_map<int, FixtureData> Fixtures;
    void GenerateUVCoordinates();
};


