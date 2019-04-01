#pragma once

#include <State.h>
#include <Sound.h>
#include <Sprite.h>
#include <Music.h>
#include <Rectangle.h>
#include <GameObject.h>
#include <Vector.h>
#include <Face.h>
#include <Util.h>
#include <Logger.h>
#include <vector>
#include <algorithm>
#include <string>
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

        Music music;

        std::vector<std::unique_ptr<GameObject>> objects;

        void Input();

        void AddObject(int, int);

        void Prune();
    };

}