#include "TileMap.h"

TileMap::TileMap(std::vector<int> tileIndices, int mapSizeX, int mapSizeY, int spriteSheetSizeX, int spriteSheetSizeY, float tileSize, b2Vec2 position)
{
    Position = position;
    MapSizeX = mapSizeX;
    MapSizeY = mapSizeY;
    TileSize = tileSize;
    TileIndices = tileIndices;
    SpriteSheetSizeX = spriteSheetSizeX;
    SpriteSheetSizeY = spriteSheetSizeX;

    int TileCount = 0;
    for (int i = 0; i < tileIndices.size(); ++i)
    {
        if(tileIndices[i] != 0)
            TileCount++;
    }
    GameObjectFactory = new Factory<GameObject>(TileCount);
    SpriteComponentFactory = new Factory<SpriteComponent>(TileCount);
    BodyComponentFactory = new Factory<BodyComponent>(TileCount);
    FixtureComponentFactory = new Factory<FixtureComponent>(tileIndices.size());
    Tiles.reserve(TileCount);
    TileUVCoordinates = std::vector<VertexData*>(spriteSheetSizeX * spriteSheetSizeY);
}

TileMap::~TileMap()
{
    delete GameObjectFactory;
    delete SpriteComponentFactory;
    delete BodyComponentFactory;
    delete FixtureComponentFactory;
    for (int i = 0; i < TileUVCoordinates.size(); ++i)
        delete TileUVCoordinates[i];
}

void TileMap::SetTileTexture(Texture *texture)
{
    TileTexture = texture;
}

void TileMap::GenerateObjects()
{
    GenerateUVCoordinates();
    for (int i = 0; i < TileIndices.size(); ++i)
    {
        int TileIndex = TileIndices[i];
        if(TileIndex == 0)
            continue;
        GameObject* Tile = GameObjectFactory->GetNew();

        SpriteComponent* Sprite = SpriteComponentFactory->GetNew();
        Sprite->gameObject = Tile;
        Tile->AddComponent(Sprite);
        Sprite->SpriteTexture = TileTexture;
        Sprite->SpriteColor = Color(1,1,1,1);
        Sprite->Width = TileSize + AntiPositionErrorOffset;
        Sprite->Height = TileSize + AntiPositionErrorOffset;
        for (int j = 0; j < 6; ++j)
        {
            Sprite->TexCoord[j].x = TileUVCoordinates[TileIndex-1][j].x;
            Sprite->TexCoord[j].y = TileUVCoordinates[TileIndex-1][j].y;
        }
        BodyComponent* Body = BodyComponentFactory->GetNew();
        Body->gameObject = Tile;
        Tile->AddComponent(Body);
        int indexX = i % MapSizeX;
        int indexY = i / MapSizeX;
        Body->position = b2Vec2(indexX * TileSize, (TileSize * MapSizeY) - indexY * TileSize) + b2Vec2(TileSize/2, TileSize/2)+ Position;

        if(Fixtures.count(TileIndex) >= 1)
        {
            FixtureComponent* Fixture = FixtureComponentFactory->GetNew();
            Fixture->gameObject = Tile;
            Tile->AddComponent(Fixture);
            Fixture->fixtureData = Fixtures[TileIndex];
            Fixture->fixtureData.width *= TileSize;
            Fixture->fixtureData.height *= TileSize;
            Fixture->fixtureData.radius *= TileSize;
            Fixture->fixtureData.position *= TileSize;
        }
        Tiles.push_back(Tile);
    }
}

void TileMap::RegisterTilesToScene(Scene *scene)
{
    for(auto Tile : Tiles)
        scene->AddGameObject(Tile);
}

void TileMap::GenerateUVCoordinates()
{
    float stepSizeX = 1.0f / SpriteSheetSizeX;
    float stepSizeY = 1.0f / SpriteSheetSizeY;
    for (int y = 0; y < SpriteSheetSizeY; ++y)
    {
        for (int x = 0; x < SpriteSheetSizeX; ++x)
        {
            int i = y * SpriteSheetSizeY + x;
            TileUVCoordinates[i] = new VertexData[6];
            TileUVCoordinates[i][0] = VertexData(stepSizeX * x + AntiPositionErrorOffset, stepSizeY * (y + 1) - AntiPositionErrorOffset);
            TileUVCoordinates[i][1] = VertexData(stepSizeX * x + AntiPositionErrorOffset, stepSizeY * y + AntiPositionErrorOffset);
            TileUVCoordinates[i][2] = VertexData(stepSizeX * (x + 1) - AntiPositionErrorOffset, stepSizeY * (y + 1) - AntiPositionErrorOffset);
            TileUVCoordinates[i][3] = VertexData(stepSizeX * x + AntiPositionErrorOffset, stepSizeY * y + AntiPositionErrorOffset);
            TileUVCoordinates[i][4] = VertexData(stepSizeX * (x + 1)- AntiPositionErrorOffset, stepSizeY * y + AntiPositionErrorOffset);
            TileUVCoordinates[i][5] = VertexData(stepSizeX * (x + 1) - AntiPositionErrorOffset, stepSizeY * (y + 1) - AntiPositionErrorOffset);

        }
    }
}

void TileMap::AddFixtureDataToTile(int tileId, FixtureData fixtureData)
{
    Fixtures[tileId] = fixtureData;
}
