#pragma once

#include <SDL_Include.h>
#include <string>

namespace penguin {

    class Music {
        public:

        Music();

        Music(const std::string&);

        ~Music();

        void Play(int times = -1);

        void Stop(int msToStop = 1500);

        void Open(const std::string&);

        bool IsOpen();

        private:

        Mix_Music* music;

        void SDL_Error();

    };

}