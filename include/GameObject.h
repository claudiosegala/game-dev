#pragma once

#include <Component.h>
#include <Rectangle.h>
#include <vector>
#include <string>

namespace penguin {

    class GameObject {
        public:

        Rectangle box;

        GameObject();

        ~GameObject();

        void Update(float);

        void Render();

        bool IsDead();

        void RequestDelete();

        void AddComponent(Component*);

        void RemoveComponent(Component*);

        Component* GetComponent(std::string);

        private:

        bool isDead;

        std::vector<Component*> components;
    };

}