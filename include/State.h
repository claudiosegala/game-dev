#pragma once

#include <Sprite.h>
#include <Music.h>
#include <GameObject.h>
#include <memory>

namespace penguin {

    class State {
        public:

        State();

        ~State();

        bool QuitRequested();

        void LoadAssets();

        void Update(float);

        void Render();

        private:

        bool quitRequested;

        Sprite bg;

        Music music;

        std::vector<std::unique_ptr<GameObject>> objects;

        void Input();

        void AddObject(int, int);
    };

}