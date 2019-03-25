#include "State.h"

namespace penguin {

    State::State () {
        this->quitRequested = false;
        // TODO: fix this
        //this->bg = new Sprite("img/ocean.jpg");
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