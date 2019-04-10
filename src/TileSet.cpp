#include <TileSet.h>
#include <Util.h>

namespace penguin {

    TileSet::TileSet(GameObject& obj, int tileWidth, int tileHeight, std::string file) : tileSet(obj, file) {
        this->rows = this->tileSet.GetHeight() / tileHeight; 
        this->columns = this->tileSet.GetWidth() / tileWidth;
        this->tileWidth = tileWidth;
        this->tileHeight = tileHeight;
    }
        
    void TileSet::RenderTile(unsigned int index, float x, float y) {
        auto n = GetQuantityTiles();

        if (index < n) {
            auto i = (index % this->columns);
            auto j = (index / this->rows);

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