#include "State.h"
#include "Logger.h"

namespace penguin {

    State::State () {
        this->quitRequested = false;
        
        LoadAssets();
        
        this->music.Play();
    }

    State::~State () {
        this->music.Stop();
    }

    void State::LoadAssets () {
        this->bg.Open("/assets/img/ocean.jpg");
        this->music.Open("/assets/audio/stageState.ogg");
    }

    void State::Update (float dt) {
        Logger::Info("Updating...");
        auto quit = SDL_QuitRequested();

        if (quit) {
            this->quitRequested = quit;
        }
    }

    void State::Render () {
        this->bg.Render(0, 0);
    }

    bool State::QuitRequested () {
        return this->quitRequested;
    }

}
