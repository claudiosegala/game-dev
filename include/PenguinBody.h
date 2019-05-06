#pragma once

#include <Util.h>
#include <GameObject.h>
#include <Component.h>
#include <Vec2.h>

class PenguinBody : public Component{
    public:

    PenguinBody (GameObject&);

    ~PenguinBody();

    void Start();

    void Update(float);

    void Render();
    
    void NotifyCollision(GameObject&);

    bool Is(std::string);

    static PenguinBody* player;

    private:

    std::weak_ptr<GameObject> pcannon;

    Vec2 speed;

    float linearSpeed;

    float angle;

    int hp;

};