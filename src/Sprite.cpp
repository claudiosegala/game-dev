#include <SDL_Include.h>
#include <Sprite.h>
#include <Game.h>
#include <Logger.h>
#include <iostream>

namespace penguin {

    Sprite::Sprite() {
        this->texture = nullptr;
    }

    Sprite::Sprite(const std::string &file) {
        this->texture = nullptr;

        Open(file);
    }

    Sprite::~Sprite() {
        Logger::Info("Destroying Texture...", 2);
        SDL_DestroyTexture(this->texture);
        Logger::Info("Done", 1);
    }

    void Sprite::Open (const std::string &file) {
        if (this->texture != nullptr) {
            SDL_DestroyTexture(this->texture);
        }

        auto g = Game::GetInstance();

        Logger::Info("Loading Texture...", 2);
        this->texture = IMG_LoadTexture(g->GetRenderer(), file.c_str());

        if (this->texture == nullptr) {
            SDL_Error();
        } else {
            Logger::Info("Done", 1);
        }
        
        Logger::Info("Querying Texture...", 2);
        auto query = SDL_QueryTexture(this->texture, nullptr, nullptr, &this->width, &this->height);

        if (query < 0) {
            SDL_Error();
        } else {
            Logger::Info("Done", 1);
        }

        SetClip(0, 0, this->width, this->height);
    }

    void Sprite::SetClip (int x, int y, int w, int h) {
        this->clipRect = {x, y, w, h};
    }

    void Sprite::Render () {
        auto x = this->associated.x;
        auto y = this->associated.y;
        
        auto g = Game::GetInstance();
        auto srcRect = this->clipRect;

        SDL_Rect dstRect{ x, y, this->clipRect.w, this->clipRect.h };

        Logger::Info("Rendering Copy...", 2);
        SDL_RenderCopy(g->GetRenderer(), this->texture, &srcRect, &dstRect);
        Logger::Info("Done", 1);
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
