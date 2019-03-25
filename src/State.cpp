#include "State.h"

namespace penguin {

    State::State () {
        this->quitRequested = false;
        this->bg.Open("/assets/img/ocean.jpg");
        this->music.Open("/assets/audio/stageState.ogg");
    }

    void State::LoadAssets () {
        // load assets here
    }

    void State::Update (float dt) {
        // TODO: discover what does it serve dt
        auto quit = SDL_QuitRequested();

        if (quit) {
            this->quitRequested = quit;
        }
    }

    void State::Render () {
        // render do bg?????
    }

    bool State::QuitRequested () {
        return this->quitRequested;
    }

}