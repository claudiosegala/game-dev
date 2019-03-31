#pragma once

#include <SDL_Include.h>
#include <string>

namespace penguin {

    class Sprite : public Component {
        public:

        Sprite(GameObject& associated);

        Sprite(GameObject& associated, const std::string&);

        ~Sprite();

        void Open (const std::string&);

        void SetClip (int, int, int, int);

        void Update();

        void Render();

        bool Is(std::string);

        int GetWidth();

        int GetHeight();

        bool IsOpen();

        private:

        int width;

        int height;

        SDL_Texture* texture;

        SDL_Rect clipRect;

    };

}