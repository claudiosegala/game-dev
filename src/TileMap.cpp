#include <TileMap.h>
#include <Util.h>
#include <iostream>
#include <fstream>
#include <sstream>

namespace penguin {

    // TODO: correct this
    TileMap::TileMap(GameObject& obj, std::string file, TileSet* ts) : tileSet(ts) {
        Load(file);
    }

    void TileMap::Load(std::string file) {
        auto new_file = CreateBetterFile(file);

        std::ifstream fs(new_file);

        if (!fs.is_open()) {
            auto msg = std::string("Could not open file created file"); 
            throw std::runtime_error(msg);
        }

        fs >> this->mapWidth >> this->mapHeight >> this->mapDepth;
        this->tileMatrix.reserve(this->mapWidth * this->mapHeight * this->mapDepth);

        for (unsigned int i = 0; i < this->tileMatrix.size(); i++) {
            fs >> this->tileMatrix[i];
            this->tileMatrix[i]--;
        }
        
        fs.close();
    }

    std::string TileMap::CreateBetterFile (std::string file) {
        auto _file = std::string("_") + file;

        std::ifstream in(file);
        std::ofstream out(_file);

        if (!(in.is_open() && out.is_open())) {
            auto msg = std::string("Could not open file"); 
            throw std::runtime_error(msg);
        }

        std::string line;

        while (getline(in, line)) {
            if (line == "\n") {
                continue;
            }

            line.replace(line.begin(), line.end(), ',', ' ');
            out << line;
            std::cout << line; // TODO: remove later
        }

        in.close();
        out.close();

        return _file;
    }

    void TileMap::SetTileSet(TileSet* ts) {
        delete this->tileSet; // TODO: discover if I should delete
        this->tileSet = ts;
    }

    int& TileMap::At(int x, int y, int z) {
        auto idx = (unsigned int) (z * (this->mapWidth * this->mapHeight) + y * (this->mapWidth) + x);

        return this->tileMatrix[idx];
    }

    void TileMap::Render() {

    }

    void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
        UNUSED(cameraX);
        UNUSED(cameraY);
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

}