#pragma once

#include<string>

#define INCLUDE_SDL
#include <SDL_Include.h>

namespace penguin {

    class Sprite {
        public:

        Sprite();

        Sprite(const std::string&);

        ~Sprite();

        void Open (const std::string&);

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