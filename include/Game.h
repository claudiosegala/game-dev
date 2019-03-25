#pragma once

// Include SDL
#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_Include.h"

// Include
#include <string>
#include <stdexcept>
#include "State.h"

namespace penguin {

    class Game {
        public:

        ~Game();

        void Run();

        static Game* GetInstance();

        State* GetState();

        SDL_Renderer* GetRenderer();

        private:

        SDL_Window* window;

        SDL_Renderer* renderer;

        State* state;

        static Game* instance;

        Game(std::string, int, int);

        void Init_SDL();

        void Init_IMG();

        void Init_MIX();

        void Init_WDW(std::string, int, int);

        void Init_RDR();

        void Init_STS();

        void SDL_Error();
    };

}