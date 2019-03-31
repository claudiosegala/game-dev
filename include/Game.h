#pragma once

#include <SDL_Include.h>
#include <State.h>
#include <string>
#include <stdexcept>

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

        Game(const std::string&, int, int);

        void Init_SDL();

        void Init_IMG();

        void Init_MIX();

        void Init_WDW(const std::string&, int, int);

        void Init_RDR();

        void Init_STS();

    };

}