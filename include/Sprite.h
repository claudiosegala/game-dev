#pragma once

// Include SDL
#define INCLUDE_SDL
#include "SDL_Include.h"

// Include
#include<string>

namespace penguin {

    class Sprite {
        public:

        Sprite();

        Sprite(std::string);

        ~Sprite();

        void Open (std::string);

        void SetClip (int, int, int, int);

        void Render (int, int);

        int GetWidth();

        int GetHeight();

        bool IsOpen();

        private:

        int width;

        int height;

        SDL_Texture* texture;

        SDL_Rect clipRect;

        void SDL_Error();

    };

}