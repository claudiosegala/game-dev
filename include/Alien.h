#pragma once

#include <Component.h>
#include <GameObject.h>
#include <Logger.h>
#include <Timer.h>
#include <Vec2.h>
#include <Util.h>

#include <string>
#include <queue>
#include <vector>
#include <memory>

class Alien : public Component {
    public:

    static int alienCount;

    Alien(GameObject&, int);

    ~Alien();

    void Start();

    void Update(float);

    void Render();

    void NotifyCollision(GameObject&);

    bool Is(std::string);

    private:

    void Shoot(Vec2);

    Vec2 speed;

    int hp;

    std::vector<std::weak_ptr<GameObject>> minions;

    enum class AlienState { 
        MOVING, 
        RESTING,
        NOP
    };

    AlienState state;

    Timer restTimer;

    Vec2 destination;

};