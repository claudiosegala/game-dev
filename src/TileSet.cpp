#include <TileSet.h>
#include <Util.h>

namespace penguin {

    TileSet::TileSet(GameObject& obj, int width, int height, std::string file) : tileSet(obj, file) {
        this->rows = this->tileSet.GetHeight() / height; 
        this->columns = this->tileSet.GetWidth() / width;
        this->tileWidth = width;
        this->tileHeight = height;
    }
        
    void TileSet::RenderTile(unsigned int index, float x, float y) {
        auto n = GetQuantityTiles();

        if (index < n) {
            auto i = (index % this->columns);
            auto j = (index / this->columns);

            this->tileSet.SetClip(i * this->tileWidth, j * this->tileHeight, this->tileWidth, this->tileHeight);
            this->tileSet.Render(x * this->tileWidth, y * this->tileHeight);
        } 
    }

    unsigned int TileSet::GetQuantityTiles() const {
        return this->tileWidth * this->tileHeight;
    }

    int TileSet::GetTileWidth() const {
        return this->tileWidth;
    }

    int TileSet::GetTileHeight() const {
        return this->tileHeight;
    }

}