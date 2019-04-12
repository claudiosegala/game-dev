#pragma once

#include <Music.h>
#include <GameObject.h>
#include <vector>
#include <memory>

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

    std::vector<std::shared_ptr<GameObject>> objects;

    void Input();

    void AddObject(int, int);

    void Prune();
};