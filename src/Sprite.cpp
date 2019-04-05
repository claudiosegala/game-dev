#include <SDL_Include.h>
#include <Sprite.h>
#include <Game.h>
#include <Logger.h>
#include <Util.h>
#include <iostream>

namespace penguin {

    Sprite::Sprite(GameObject& obj) : Component(obj) {
        this->texture = nullptr;
    }

    Sprite::Sprite(GameObject& obj, const std::string &file)  : Component(obj) {
        this->texture = nullptr;

        Open(file);
    }

    Sprite::~Sprite() {
        Logger::Info("Destroying Texture...", 2);
        SDL_DestroyTexture(this->texture);
        this->texture = nullptr;
        Logger::Info("Done", 1);
    }

    void Sprite::Open (const std::string &file) {
        if (this->texture != nullptr) {
            SDL_DestroyTexture(this->texture);
            this->texture = nullptr;
        }
        
        auto g = Game::GetInstance();

        Logger::Info("test");

        Logger::Info("Loading Texture...", 2);
        this->texture = IMG_LoadTexture(g->GetRenderer(), file.c_str());

        if (this->texture == nullptr) {
            auto sdl_msg = IMG_GetError();
            throw std::runtime_error(sdl_msg);
        } else {
            Logger::Info("Done", 1);
        }
        
        Logger::Info("Querying Texture...", 2);
        auto query = SDL_QueryTexture(this->texture, nullptr, nullptr, &this->width, &this->height);

        if (query < 0) {
            auto sdl_msg = SDL_GetError();
            throw std::runtime_error(sdl_msg);
        } else {
            Logger::Info("Done", 1);
        }

        SetClip(0, 0, this->width, this->height);
        
        this->associated.box.width = static_cast<float>(this->width);
        this->associated.box.height = static_cast<float>(this->height);
    }

    void Sprite::SetClip (int x, int y, int w, int h) {
        this->clipRect = {x, y, w, h};
    }

    void Sprite::Update (float dt) {
        UNUSED(dt);
    }

    void Sprite::Render () {
        auto g = Game::GetInstance();
        auto x = static_cast<int>(this->associated.box.vector.x);
        auto y = static_cast<int>(this->associated.box.vector.y);    
        auto srcRect = this->clipRect;

        SDL_Rect dstRect{ x, y, this->clipRect.w, this->clipRect.h };

        SDL_RenderCopy(g->GetRenderer(), this->texture, &srcRect, &dstRect);
    }

    bool Sprite::Is (std::string type) {
        return (type == "Sprite");
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

}
