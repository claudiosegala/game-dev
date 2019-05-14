#pragma once

#include <Music.h>
#include <GameObject.h>
#include <Logger.h>
#include <Util.h>
#include <State.h>
#include <TileSet.h>

#include <vector>
#include <memory>
#include <algorithm>
#include <string>

class StageState : public State {
    public:

        StageState();

        ~StageState();

        void LoadAssets();

        void Update(float);

        void Render();

        void Start();

        void Pause();

        void Resume();

    private:

        // TODO: discover why this
        TileSet* tileSet;

        Music music;

        void CheckCollision();

        void CreateField();

        void CreateMainCharacter();

        void CreateEnemies();
};