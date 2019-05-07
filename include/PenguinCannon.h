#pragma once

#include <Util.h>
#include <Component.h>
#include <GameObject.h>

class PenguinCannon : public Component {
    public:

        PenguinCannon(GameObject&, std::weak_ptr<GameObject>);

        void Update(float);

        void Render();

        bool Is(std::string);

        void Shoot();

    private:

        float angle;

        std::weak_ptr<GameObject> pbody;

};