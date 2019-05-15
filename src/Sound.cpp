#include <Sound.h>
#include <Resources.h>

Sound::Sound (GameObject& go) : Component(go), chunk() {
}

Sound::Sound (GameObject& go, std::string name) : Component(go), chunk() {
    Open(name);
}

Sound::~Sound () {}

// TODO: see if this is correct
void Sound::Play (int times) {
    this->channel = Mix_PlayChannel(-1, this->chunk.get(), times - 1);

    if (this->channel < 0) {
        auto msg = Mix_GetError();
        throw std::runtime_error(msg);
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

void Sound::Open (std::string file) {
    this->chunk = Resources::GetSound(file);
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