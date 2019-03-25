#include "State.h"

namespace penguin {

    State::State () {
        this->quitRequested = false;
        // TODO: verify if this is correct;
        this->bg.Open("/assets/img/ocean.jpg");
        this->music.Open("/assets/audio/stageState.ogg");
    }

    void State::LoadAssets () {
        // TODO: discover what should be here
    }

    void State::Update (float dt) {
        // TODO: discover what does it serve dt
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