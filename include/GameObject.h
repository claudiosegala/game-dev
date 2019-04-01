#pragma once

#include <Component.h>
#include <Rectangle.h>
#include <Vector.h>
#include <vector>
#include <string>
#include <memory>

namespace penguin {

    class Component;

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

        void RemoveComponent(std::unique_ptr<Component>&);

        Component* GetComponent(std::string);

        private:

        bool isDead;

        std::vector<std::unique_ptr<Component>> components;
    };

}