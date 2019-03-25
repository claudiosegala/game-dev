#pragma once

// Include
#include "Sprite.h"
#include "Music.h"

namespace penguin {

    class State {
        public:

        State();

        bool QuitRequested();

        void LoadAssets();

        void Update(float);

        void Render();

        private:

        Sprite bg;

        Music music;

        bool quitRequested;
    };

}