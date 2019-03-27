#include <Music.h>
#include <Logger.h>
#include <iostream>

namespace penguin {

    Music::Music() {
        this->music = nullptr;
    }

    Music::Music(const std::string &file) {
        Open(file);
    }

    Music::~Music() {
        Logger::Info("Destroying Music...", 2);
        Mix_FreeMusic(this->music);
        Logger::Info("Done", 1);
    }

    void Music::Play(int times) {
        if (this->music == nullptr) {
            return;
        }

        Logger::Info("Start Playing Music...", 2);
        auto err = Mix_PlayMusic(this->music, times);

        if (err < 0) {
            SDL_Error();
        } else {
            Logger::Info("Done", 1);
        }
    }

    void Music::Stop(int msToStop) {
        Logger::Info("Fading Out Music...", 2);
        auto err = Mix_FadeOutMusic(msToStop);

        if (err < 0) {
            SDL_Error();
        } else {
            Logger::Info("Done", 1);
        }
    }

    void Music::Open(const std::string &file) {
        Logger::Info("Loading Music...", 2);
        this->music = Mix_LoadMUS(file.c_str());

        if (this->music == nullptr) {
            SDL_Error();
        } else {
            Logger::Info("Done", 1);
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
