#pragma once

#include <Component.h>
#include <GameObject.h>
#include <Logger.h>
#include <Util.h>

#include <string>
#include <queue>
#include <vector>
#include <memory>

class Alien : public Component {
    public:

    Alien(GameObject&, int);

    ~Alien();

    void Start();

    void Update(float);

    void Render();

    bool Is(std::string);

    private:

    class Action {
        public:
        
        enum class ActionType { 
            MOVE, 
            SHOOT 
        };
        
        Vec2 pos;

        ActionType type;

        Action (ActionType, float, float);

    };

    void Move(Action, float);

    void Shoot(Action);

    Vec2 speed;

    int hp;

    std::queue<Action> taskQueue;

    std::vector<std::weak_ptr<GameObject>> minions;

};