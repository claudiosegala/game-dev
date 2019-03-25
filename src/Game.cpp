#include "Game.h"

#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_Include.h"

namespace penguin {

    Game* Game::instance;

    Game::Game(std::string title, int width, int height) {
        // Init Instance
        if (this->instance != nullptr) {
            throw std::runtime_error("There should be only one instance!");
        }

        this->instance = this;

        Init_SDL();
        Init_IMG();
        Init_MIX();
        Init_WDW(title, width, height);
        Init_RDR();
        Init_STS();
    }

    Game::~Game() {
        SDL_DestroyRenderer(this->renderer);
        SDL_DestroyWindow(this->window);
        Mix_CloseAudio();
        Mix_Quit();
        IMG_Quit();
        SDL_Quit();
    }

    void Game::Run() {
        while(!this->state->QuitRequested()) {
            this->state->Update(1.0); // TODO: change this argument
            this->state->Render();

            SDL_RenderPresent(this->renderer);
            SDL_Delay(33);
        }
    }

    Game* Game::GetInstance () {
        if (Game::instance != nullptr) {
            return Game::instance;
        }

        return Game::instance = new Game("ClaudioSegala_150032552", 1024, 600);
    }

    State* Game::GetState () {
        return this->state;
    }

    SDL_Renderer* Game::GetRenderer () {
        return this->renderer;
    }

    void Game::Init_STS () {
        this->state = new State();
    }

    void Game::Init_RDR () {
        auto index = -1; // SDL will choose the best for us

        /*
            Available flags:
            SDL_RENDERER_SOFTWARE
            SDL_RENDERER_PRESENTVSYNC
            SDL_RENDERER_ACCELERATED
            SDL_RENDERER_TARGETTEXTURE
        */
        uint32_t flags = (
            SDL_RENDERER_ACCELERATED
        );

        this->renderer = SDL_CreateRenderer(this->window, index, flags);

        if (this->renderer == nullptr) {
            SDL_GetNumRenderDrivers();
            SDL_Error();
        }
    }

    void Game::Init_WDW (std::string title, int width, int height) {
        auto pos = SDL_WINDOWPOS_CENTERED;
        uint32_t flags = 0;

        this->window = SDL_CreateWindow(title.c_str(), (int) pos, (int) pos, width, height, flags);

        if (this->window == nullptr) {
            SDL_Error();
        }
    }

    void Game::Init_MIX () {
        /*
            Available Flags:
            MIX_INIT_FLAC
            MIX_INIT_MP3
            MIX_INIT_OGG
            MIX_INIT_MOD
            MIX_INIT_FLUIDSYNTH
            MIX_INIT_MODPLUG
        */
        auto flags = (
            MIX_INIT_OGG
        );

        auto res = Mix_Init(flags);

        if (res != flags) {
            SDL_Error();
        }

        res = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);

        if (res < 0) {
            SDL_Error();
        }

        res = Mix_AllocateChannels(32);

        if (res < 0) {
            SDL_Error();
        }
    }

    void Game::Init_IMG () {
        /*
            Available Flags:
            IMG_INIT_JPG
            IMG_INIT_PNG
            IMG_INIT_TIF
        */
        auto flags = (
            IMG_INIT_JPG |
            IMG_INIT_PNG
        );

        auto res = IMG_Init(flags);

        if (res != flags) {
            SDL_Error();
        }
    }

    void Game::Init_SDL () {
        /* 
            Available Flags:
            SDL_INIT_TIMER
            SDL_INIT_GAMECONTROLLER
            SDL_INIT_AUDIO
            SDL_INIT_EVENTS
            SDL_INIT_VIDEO
            SDL_INIT_EVERYTHING
            SDL_INIT_JOYSTICK
            SDL_INIT_NOPARACHUTE
            SDL_INIT_HAPTIC
        */
        auto flags = (
            SDL_INIT_VIDEO |
            SDL_INIT_AUDIO |
            SDL_INIT_TIMER
        );

        auto err = SDL_Init(flags);

        if (err < 0) {
            SDL_Error();
        }
    }

    void Game::SDL_Error () {
        auto sdl_msg = SDL_GetError();
        throw std::runtime_error(sdl_msg);
    }
}