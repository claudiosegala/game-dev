#include <Resources.h>
#include <Game.h>

int const Game::windowWidth = 1024;

int const Game::windowHeight = 600;

std::string const Game::windowName = "ClaudioSegala_150032552";

Game* Game::instance;

Game::Game(const std::string &title, int width, int height) {
    if (this->instance != nullptr) {
        throw std::runtime_error("There should be only one instance!");
    }

    this->instance = this;
    this->frameStart = 0.0;
    this->dt = 0;
    this->storedState = nullptr;

    Init_SDL();
    Init_IMG();
    Init_MIX();
    Init_WDW(title, width, height);
    Init_RDR();

    Logger::Info("Created the game instance");
}

Game::~Game() {
    if (this->storedState != nullptr) {
        Logger::Info("Erasing Stored State");
        delete this->storedState;
    }

    Logger::Info("Cleaning Stack of States");
    while(!this->stateStack.empty()) {
        this->stateStack.pop();
    }

    // Clean the resources
    Logger::Info("Destroying Resources");
    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();

    // Clean SDL instances
    Logger::Info("Destroying Renderer");
    SDL_DestroyRenderer(this->renderer);
    
    Logger::Info("Destroying Window");
    SDL_DestroyWindow(this->window);
    
    Logger::Info("Quiting SDL Mix Audio");
    Mix_CloseAudio();
    
    Logger::Info("Quiting SDL Mixer");
    while(Mix_Init(0)) {
        Mix_Quit(); // The best way (by documentation)
    }
    
    Logger::Info("Quiting SDL Image");
    IMG_Quit();
    
    Logger::Info("Quiting SDL");
    SDL_Quit();
}

void Game::Push (State* state) {
    this->storedState = state;
}

void Game::Run() {
    if (this->storedState == nullptr) {
        return;    
    }

    Start();
    Loop();
    End();    
}

void Game::Start() {
    Logger::Info("Started Game");

    this->stateStack.emplace(this->storedState);

    this->storedState->Start();

    this->storedState = nullptr;
}

void Game::Loop () {
    auto& in = InputManager::GetInstance();


    while (!this->stateStack.empty()) {
        auto state = this->stateStack.top().get();

        if (state->QuitRequested()) {
            break;
        }

        if (state->PopRequested()) {
            this->stateStack.pop();

            if (!this->stateStack.empty()) {
                state = this->stateStack.top().get();
                state->Resume();
            }
        }

        if (this->storedState != nullptr) {
            if (state != nullptr) {
                state->Pause();
            }

            this->stateStack.emplace(this->storedState);

            state = this->stateStack.top().get();

            state->Start();
        }

        CalculateDeltaTime();

        in.Update();

        state->Update(this->dt);
        state->Render();

        SDL_RenderPresent(this->renderer);
    }
}

void Game::End() {
    Logger::Info("Ended Game");
}

Game* Game::GetInstance () {
    if (Game::instance != nullptr) {
        return Game::instance;
    }
    
    return Game::instance = new Game(Game::windowName, Game::windowWidth, Game::windowHeight);
}

State* Game::GetCurrentState () {
    return this->stateStack.top().get();
}

SDL_Renderer* Game::GetRenderer () {
    return this->renderer;
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
    
    Logger::Info("Creating Renderer");
    this->renderer = SDL_CreateRenderer(this->window, index, flags);

    if (this->renderer == nullptr) {
        SDL_GetNumRenderDrivers();

        auto sdl_msg = SDL_GetError();
        throw std::runtime_error(sdl_msg);
    }
}

void Game::Init_WDW (const std::string &title, int width, int height) {
    auto pos = SDL_WINDOWPOS_CENTERED;
    uint32_t flags = 0;
    
    Logger::Info("Creating Window");
    this->window = SDL_CreateWindow(title.c_str(), (int) pos, (int) pos, width, height, flags);

    if (this->window == nullptr) {
        auto sdl_msg = SDL_GetError();
        throw std::runtime_error(sdl_msg);
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
    
    Logger::Info("Initing Mixer");
    auto res = Mix_Init(flags);

    if (res != flags) {
        auto mix_msg = "MixError: " + std::string(Mix_GetError()) + "\n";
        auto msg = "The flag sent was " + std::to_string(flags) + ", but the result of initing mixer was " + std::to_string(res) + "\n";
        throw std::runtime_error(mix_msg + msg);
    }

    Logger::Info("Configuring Audio");
    res = Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);

    if (res < 0) {
        auto mix_msg = Mix_GetError();
        throw std::runtime_error(mix_msg);
    }
    
    Logger::Info("Allocating Channels");
    res = Mix_AllocateChannels(32);

    if (res < 0) {
        auto mix_msg = Mix_GetError();
        throw std::runtime_error(mix_msg);
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
    
    Logger::Info("Initing SDL Image");
    auto res = IMG_Init(flags);

    if (res != flags) {
        auto img_msg = "ImageError: " + std::string(IMG_GetError())  + "\n";
        auto msg = "The flag sent was " + std::to_string(flags) + ", but the result of initing image was " + std::to_string(res) + "\n";
        throw std::runtime_error(img_msg + msg);
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
    
    Logger::Info("Initing SDL");
    auto err = SDL_Init(flags);

    if (err < 0) {
        auto sdl_msg = "SDLError: " + std::string(SDL_GetError()) + "\n";
        throw std::runtime_error(sdl_msg);
    }
}

float Game::GetDeltaTime() {
    return this->dt;
}

void Game::CalculateDeltaTime() {
    auto newFrameStart = (float) SDL_GetTicks();
    auto oldFrameStart = (float) this->frameStart;

    this->dt = (newFrameStart - oldFrameStart) / 1000.0f;
    this->frameStart = newFrameStart;
}
