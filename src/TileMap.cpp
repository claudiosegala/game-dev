#include <TileMap.h>
#include <Util.h>
#include <iostream>
#include <fstream>
#include <sstream>

namespace penguin {

    TileMap::TileMap(GameObject& obj, std::string file, TileSet* ts) : Component(obj), tileSet(ts) {
        Load(file);
    }

    TileMap::~TileMap () {
        delete this->tileSet;
    }

    void TileMap::Load(std::string file) {
        std::string line;
        std::ifstream fs(file);

        if (!fs.is_open()) {
            auto msg = std::string("Could not open file created file"); 
            throw std::runtime_error(msg);
        }

        
        getline(fs, line, ',');
        auto x = (unsigned int) std::stoi(line);
        getline(fs, line, ',');
        auto y = (unsigned int) std::stoi(line);
        getline(fs, line, ',');
        auto z = (unsigned int) std::stoi(line);

        unsigned int n = x * y * z;

        this->mapDepth = (int) z;
        this->mapHeight = (int) y;
        this->mapWidth = (int) x;
        this->tileMatrix.resize(n);

        for (unsigned int k = 0; k < z; k++){
            for (unsigned int i = 0; i < x; i++){
                for (unsigned int j = 0; j < y; j++){
                    getline(fs, line, ',');
                    unsigned int idx = Pos(j, i, k);
                    this->tileMatrix[idx] = std::stoi(line);
                    this->tileMatrix[idx]--;
                }
            }
        }
        
        fs.close();
    }

    void TileMap::SetTileSet(TileSet* ts) {
        delete this->tileSet;
        this->tileSet = ts;
    }

    unsigned int TileMap::Pos(unsigned int x, unsigned int y, unsigned int z) {
        return (z * (this->mapWidth * this->mapHeight) + y * (this->mapWidth) + x);
    }

    int& TileMap::At(int x, int y, int z) {
        auto idx = Pos(x, y, z);
        return this->tileMatrix[idx];
    }

    void TileMap::Update (float dt) {
        UNUSED(dt);
    }

    void TileMap::Render() {
        for (int k = 0; k < this->mapDepth; k++) {
            RenderLayer(k, 0, 0);
        }
    }

    void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
        UNUSED(cameraX);
        UNUSED(cameraY);

        for (int i = 0; i < this->mapHeight; i++) {
            for (int j = 0; j < this->mapWidth; j++) {
                auto idx = (unsigned int) At(i, j, layer);
                tileSet->RenderTile(idx, i, j);
            }
        }
    }

    int TileMap::GetWidth() {
        return this->mapWidth;
    }

    int TileMap::GetHeight() {
        return this->mapHeight;
    }

    int TileMap::GetDepth() {
        return this->mapDepth;
    }

    bool TileMap::Is (std::string type) {
        return (type == "TileMap");
    }

}