#include <SDL_Include.h>
#include <Game.h>
#include <Util.h>

#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv)
{
    UNUSED(argc);
    UNUSED(argv);

    try {
        srand((unsigned int)time(NULL));

        Logger::GetInstance();    
    
        auto g = Game::GetInstance();

        g->Run();
        g->~Game();
    } catch (std::runtime_error e) {
        Logger::Error(e.what());
    }

    return 0;
}
