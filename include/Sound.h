#pragma once

#include "GameObject.h"
#include "SDL_Include.h"

// TODO: add logs

namespace penguin {

    class Sound : public GameObject {
        public:

        Sound(GameObject&);

        Sound(GameObject&, std::string);

        ~Sound();

        void Play(int times = 1);

        void Stop();

        void Open(std::string);

        bool IsOpen();

        void Update(float);

        void Render();

        bool Is(std::string);
        
        private:

        int channel;

        Mix_Chunk* chunk;

    };

}