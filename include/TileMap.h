#pragma once

#include <Component.h>
#include <GameObject.h>
#include <TileSet.h>

#include <string>
#include <vector>

class TileMap : public Component {
    public:

    TileMap(GameObject&, std::string, TileSet*);

    ~TileMap();

    void Load(std::string);

    void SetTileSet(TileSet*);

    unsigned int Pos(int, int, int);

    int& At(int, int, int z = 0);

    void Update(float);

    void Render();

    void RenderLayer(int, int cameraX = 0, int cameraY = 0);

    int GetWidth();

    int GetHeight();

    int GetDepth();

    bool Is(std::string);

    private:

    std::vector<int> tileMatrix;

    TileSet* tileSet;

    int mapWidth;

    int mapHeight;

    int mapDepth;

};