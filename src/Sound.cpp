#include "Sound.h"

namespace penguin {

    Sound::Sound(GameObject& obj) : Component(obj) {
        this->chunk = nullptr;
    }

    Sound::Sound(GameObject& obj, std::string name) : Component(obj) {
        Open(name);
    }

    Sound::~Sound() {
        if (this->chunck != nullptr) {
            // TODO: check if this is correct
            Stop();

            Mix_FreeChunk(this->chunk);
            this->chunk = nullptr;
        }
    }

    void Sound::Play(int times) {
        this->channel = Mix_PlayChannel(-1, this->chunk, times);

        if (this->channel < 0) {
            auto mix_msg = Mix_GetError();
            throw std::runtime_error(mix_msg);
        }
    }

    void Sound::Stop() {
        if (this->chunk != nullptr) {
            Mix_HaltChannel(this->channel);
        }
    }

    void Sound::Open(std::string filename) {
        this->chunk = Mix_LoadWAV(filename);

        if (this->chunk == nullptr) {
            auto mix_msg = Mix_GetError();
            throw std::runtime_error(mix_msg);
        }
    }

    bool Sound::IsOpen() {
        return this->chunk == nullptr;
    }

    void Sound::Update(float dt) {}

    void Sound::Render() {}

    bool Sound::Is(std::string) {
        return return type == "Sound";
    }

}