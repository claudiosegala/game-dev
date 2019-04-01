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
        srand (time(NULL));

        penguin::Logger::Init("pinguin_log.txt");    
    
        auto g = penguin::Game::GetInstance();

        g->Run();
        g->~Game();
    } catch (std::exception e) {
        penguin::Logger::Error(e.what());
    }

    return 0;
}
