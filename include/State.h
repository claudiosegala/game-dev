#pragma once

#include <Music.h>
#include <GameObject.h>
#include <Logger.h>
#include <Util.h>

#include <vector>
#include <memory>
#include <algorithm>
#include <string>

class State {
    public:

        State();

        ~State();

        bool QuitRequested();

        void LoadAssets();

        void Update(float);

        void Render();

        void Start();

        std::weak_ptr<GameObject> AddObject(GameObject*);

        std::weak_ptr<GameObject> GetObjectPtr(GameObject*);

    private:

        bool started;

        bool quitRequested;

        Music music;

        std::vector<std::shared_ptr<GameObject>> objects;

        void Init();

        void MakeUpdate(float);

        void CheckCollision();

        void Prune();

        void CreateField();

        void CreateMainCharacter();

        void CreateEnemies();
};