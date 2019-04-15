#pragma once

#include <GameObject.h>
#include <Logger.h>
#include <Util.h>

#include <string>

class Alien {
    public:

    Alien(GameObject&, int);

    ~Alien();

    void Start();

    void Update(float);

    void Render();

    bool Is(std::string);

    private:

    - Action : class (ver abaixo)
- speed : Vec2
- hp : int
- taskQueue : std::queue<Action>
- minionArray : std::vector<
std::weak_ptr<GameObject> >

};