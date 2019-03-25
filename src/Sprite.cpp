#include "Game.h"
#include "Sprite.h"

namespace penguin {

    Sprite::Sprite() {
        this->texture = nullptr;
    }

    Sprite::Sprite(std::string file) {
        this->texture = nullptr;

        Open(file);
    }

    Sprite::~Sprite() {
        SDL_DestroyTexture(this->texture);
    }

    void Sprite::Open (std::string file) {
        if (this->texture != nullptr) {
            SDL_DestroyTexture(this->texture);
        }

        auto g = Game::GetInstance();

        this->texture = IMG_LoadTexture(g->GetRenderer(), file.c_str());

        if (this->texture == nullptr) {
            SDL_Error();
        }

        auto query = SDL_QueryTexture(this->texture, nullptr, nullptr, &this->width, &this->height);

        if (query < 0) {
            SDL_Error();
        }

        SetClip(0, 0, this->width, this->height);
    }

    void Sprite::SetClip (int x, int y, int w, int h) {
        this->clipRect = {x, y, w, h};
    }

    void Sprite::Render (int x, int y) {
        auto g = Game::GetInstance();
        auto srcRect = this->clipRect;

        SDL_Rect dstRect{ x, y, this->clipRect.w, this->clipRect.h };

        SDL_RenderCopy(g->GetRenderer(), this->texture, &srcRect, &dstRect);
    }

    int Sprite::GetWidth() {
        return this->width;
    }

    int Sprite::GetHeight() {
        return this->height;
    }

    bool Sprite::IsOpen() {
        return (this->texture != nullptr);
    }

    void Sprite::SDL_Error() {
        auto sdl_msg = SDL_GetError();
        throw std::runtime_error(sdl_msg);
    }

}