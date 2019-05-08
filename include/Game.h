#pragma once

#include <InputManager.h>
#include <Logger.h>
#include <SDL_Include.h>
#include <StageState.h>
#include <Util.h>

#include <string>
#include <stdexcept>
#include <iostream>

class Game {
    public:

        static int const windowWidth;

        static int const windowHeight;

        static std::string const windowName;

        ~Game();

        void Run();

        static Game* GetInstance();

        StageState* GetState();

        SDL_Renderer* GetRenderer();

        float GetDeltaTime();

    private:

        static Game* instance;

        float dt;

        unsigned int frameStart;

        StageState* state;

        SDL_Window* window;

        SDL_Renderer* renderer;

        Game(const std::string&, int, int);

        void Init_SDL();

        void Init_IMG();

        void Init_MIX();

        void Init_WDW(const std::string&, int, int);

        void Init_RDR();

        void Init_STS();

        void Start();

        void Loop();

        void End();

        void CalculateDeltaTime();

};