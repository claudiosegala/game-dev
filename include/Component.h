#pragma once

#include <GameObject.h>
#include <string>

namespace penguin {

    class GameObject;

    class Component {
        public:

        Component(GameObject& associated);

        virtual ~Component();

        virtual void Update(float dt) = 0;

        virtual void Render() = 0;

        virtual bool Is(std::string) = 0;

        protected:
        
        GameObject& associated;

    };

}