#include "Music.h"

namespace penguin {

    Music::Music() {
        this->music = nullptr;
    }

    Music::Music(std::string file) {
        Open(file);
    }

    Music::~Music() {
        Mix_FreeMusic(this->music);
    }

    void Music::Play(int times) {
        if (this->music == nullptr) {
            return;
        }

        auto err = Mix_PlayMusic(this->music, times);

        if (err < 0) {
            SDL_Error();
        }
    }

    void Music::Stop(int msToStop) {
        auto err = Mix_FadeOutMusic(msToStop);

        if (err < 0) {
            SDL_Error();
        }
    }

    void Music::Open(std::string file) {
        this->music = Mix_LoadMUS(file.c_str());

        if (this->music == nullptr) {
            SDL_Error();
        }
    }

    bool Music::IsOpen() {
        return (this->music != nullptr);
    }

    void Music::SDL_Error () {
        auto sdl_msg = SDL_GetError();
        throw std::runtime_error(sdl_msg);
    }

}