#include "TileSet.h"

namespace penguin {

    TileSet::TileSet(GameObject& obj, int tileWidth, int tileHeight, std::string file) {
        this->tileSet = new Sprite(obj, file); // TODO: is this correct?
        this->rows = this->tileSet.GetHeight() / tileHeight; 
        this->columns = this->tileSet.GetWidth() / tileWidth;
        this->tileWidth = tileWidth;
        this->tileHeight = tileHeight;
    }
        
    void TileSet::RenderTile(unsigned int index, float x, float y) {
        auto idx = (int) index;
        auto n = GetQuantityTiles();

        if (idx < n) {
            auto i = (idx % this->columns);
            auto j = (idx / this->rows);

            this->tileSet.SetClip(i * this->tileWidth, j * this->tileHeight, this->tileWidth, this->tileHeight);
            this->tileSet.Render(x, y);
        } 
    }

    int TileSet::GetQuantityTiles() const {
        return this->tileWidth * this->tileHeight;
    }

    int TileSet::GetTileWidth() const {
        return this->tileWidth;
    }

    int TileSet::GetTileHeight() const {
        return this->tileHeight;
    }

}