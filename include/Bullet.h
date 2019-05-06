#pragma once

#include <Util.h>
#include <GameObject.h>
#include <Vec2.h>

class Bullet : public Component {
    public:

    bool targetPlayer;
    
    Bullet(GameObject&, float, float, int, float, std::string, int frameCount = 1, float frameTime = 1.0f, bool targetPlayer = false);

    void Update(float);

    void Render();

    void NotifyCollision(GameObject&);

    bool Is(std::string);

    int GetDamage();

    private:

    Vec2 speed;

    float distanceLeft;

    int damage;
};