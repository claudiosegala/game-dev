#include <iostream>
#include "State.h"

namespace penguin {

    State::State () {
        this->quitRequested = false;
        
        LoadAssets();
        
        this->music.Play();
    }

    State::~State () {
        std::cout << "Stopping music" << std::endl;
        this->music.Stop();
    }

    void State::LoadAssets () {
        std::cout << "Loading Background" << std::endl;
        this->bg.Open("/assets/img/ocean.jpg");
        
        std::cout << "Loading Music" << std::endl;
        this->music.Open("/assets/audio/stageState.ogg");
    }

    void State::Update (float dt) {
        std::cout << "Updating" << std::endl;
            
        auto quit = SDL_QuitRequested();

        if (quit) {
            this->quitRequested = quit;
        }
    }

    void State::Render () {
        std::cout << "Rendering" << std::endl;
        this->bg.Render(0, 0);
    }

    bool State::QuitRequested () {
        return this->quitRequested;
    }

}
