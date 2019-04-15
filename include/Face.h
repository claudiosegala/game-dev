#pragma once

#include <Component.h>
#include <GameObject.h>

#include <string>

class Face : public Component {
    public:

    Face(GameObject&);

    void Damage(int);

    void Update(float);

    void Render();

    bool Is(std::string);        

    private:

    int hitpoints;
};