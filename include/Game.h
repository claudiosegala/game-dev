#pragma once

#include <string>
#include <stdexcept>
#include "State.h"

#define INCLUDE_SDL
#include "SDL_Include.h"

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