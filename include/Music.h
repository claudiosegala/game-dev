#pragma once

// Include SDL
#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include "SDL_Include.h"

// Include
#include <string>

namespace penguin {

    class Music {
        public:

        Music();

        Music(std::string);

        ~Music();

        void Play(int times = -1);

        void Stop(int msToStop = 1500);

        void Open(std::string);

        bool IsOpen();

        private:

        Mix_Music* music;

        void SDL_Error();

    };

}