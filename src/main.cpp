#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#include <SDL_Include.h>
#include <Game.h>
#include <Logger.h>
#include <Util.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv)
{
    UNUSED(argc);
    UNUSED(argv);

    try {
        srand((unsigned int)time(NULL));

        penguin::Logger::GetInstance();    
    
        auto g = penguin::Game::GetInstance();

        g->Run();
        g->~Game();
    } catch (std::runtime_error e) {
        penguin::Logger::Error(e.what());
    }

    return 0;
}
