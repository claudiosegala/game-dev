#include <Sound.h>
#include <Logger.h>
#include <Util.h>
#include <SDL_Include.h>

namespace penguin {

    Sound::Sound (GameObject& obj) : Component(obj) {
        this->chunk = nullptr;
    }

    Sound::Sound (GameObject& obj, std::string name) : Component(obj) {
        this->chunk = nullptr;
        Open(name);
    }

    Sound::~Sound () {
        if (this->channel >= 0) {
            // Make this busy wait to make sure that the sound works
            Logger::Warning("Waiting for the music stop playing");
            while(Mix_Playing(this->channel));
        }
        
        
        Stop();

        if (this->chunk != nullptr) {
            Mix_FreeChunk(this->chunk);
            this->chunk = nullptr;
        }
    }

    void Sound::Play (int times) {
        this->channel = Mix_PlayChannel(-1, this->chunk, times - 1);

        if (this->channel < 0) {
            auto mix_msg = Mix_GetError();
            throw std::runtime_error(mix_msg);
        } else {
            Logger::Info("Music is playing on channel " + std::to_string(this->channel));
        }
    }

    void Sound::Stop () {
        Logger::Info("Halting the channel " + std::to_string(this->channel));
        if (this->chunk != nullptr && this->channel >= 0) {
            Mix_HaltChannel(this->channel);
            Logger::Info("Halting the channel " + std::to_string(this->channel));
        }
    }

    void Sound::Open (std::string filename) {
        this->chunk = Mix_LoadWAV(filename.c_str());

        if (this->chunk == nullptr) {
            auto mix_msg = Mix_GetError();
            throw std::runtime_error(mix_msg);
        } else {
            Logger::Info("Loaded WAV from " + filename);
        }
    }

    bool Sound::IsOpen () {
        return (this->chunk == nullptr);
    }

    bool Sound::Is (std::string type) {
        return (type == "Sound");
    }

    void Sound::Update (float dt) {
        UNUSED(dt);
    }

    void Sound::Render () {}

}