#include <TileMap.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

namespace penguin {

    // TODO: correct this
    TileMap(GameObject& obj, std::string filename, TileSet* tileSet) : tileSet(tileSet) {
        Load(filename);
    }

    void Load(std::string filename) {
        auto new_filename = CreateBetterFile(filename);

        ifstream fs(new_filename);

        if (!fs.is_open()) {
            auto msg = std::string("Could not open file created file"); 
            throw std::runtime_error(msg);
        }

        iss >> this->mapWidth >> this->mapHeight >> this->mapDepth;
        this->tileMatrix.reserve(this->mapWidth * this->mapHeight * this->mapDepth);

        for (int i = 0; i < n; i++) {
            iss >> this->tileMatrix[i];
            this->tileMatrix[i]--;
        }
        
        fs.close();
    }

    std::string CreateBetterFile (std::string filename) {
        auto _filename = std::string("_") + filename;

        ifstream in(filename);
        ofstream out(_filename);

        if (!(in.is_open() && out.is_open())) {
            auto msg = std::string("Could not open file"); 
            throw std::runtime_error(msg);
        }

        std::string line;

        while (getline(fs, line)) {
            if (line == "\n") {
                continue;
            }

            line.replace(line.begin(), line.end(), ',', ' ');
            out << line;
            std::cout << line; // TODO: remove later
        }

        in.close();
        out.close();

        return _filename;
    }

    void SetTileSet(TileSet* tileSet) {
        delete this->tileSet; // TODO: discover if I should delete
        this->tileSet = tileSet;
    }

    int& At(int x, int y, int z) {
        auto idx = z * (this->mapWidth * this->mapHeight) + y * (this->mapWidth) + x;

        return this->tileMatrix[idx];
    }

    void Render() {

    }

    void RenderLayer(int layer, int cameraX, int cameraY) {

    }

    int GetWidth() {
        return this->mapWidth;
    }

    int GetHeight() {
        return this->mapHeight;
    }

    int GetDepth() {
        return this->mapDepth;
    }

}