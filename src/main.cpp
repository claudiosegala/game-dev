#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#include <SDL_Include.h>
#include <Game.h>
#include <Logger.h>
#include <Util.h>

int main(int argc, char** argv)
{
    UNUSED(argc);
    UNUSED(argv);

    penguin::Logger::Init("pinguin_log.txt");    
    
    auto g = penguin::Game::GetInstance();

    g->Run();
    g->~Game();

    return 0;
}
