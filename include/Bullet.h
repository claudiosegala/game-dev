#pragma once

#include <Util.h>
#include <GameObject.h>
#include <Vec2.h>

class Bullet : public Component {
    public:
    
    void Bullet(GameObject&, float, float, int, float, std::string);

    void Update(float);

    void Render();

    bool Is(std::string);

    int GetDamage();

    private:

    Vec2 speed;

    float distanceLeft;

    int damage;
}