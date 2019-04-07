#pragma once

#include <GameObject.h>
#include <string>

namespace penguin {

    class TileMap {
        public:

        TileMap(GameObject&, std::string, TileSet*);

        void Load(std::string);

        void SetTileSet(TileSet*);

        int& At(int, int, int z = 0);

        void Render();

        void RenderLayer(int, int cameraX = 0, int cameraY = 0);

        int GetWidth();

        int GetHeight();

        int GetDepth();

        private:

        std::vector<int> tileMatrix;

        TileSet* tileSet;

        int mapWidth;

        int mapHeight;

        int mapDepth;

    };

}