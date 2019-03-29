#pragma once

#include "GameObject.h"

namespace penguin {

    class Component {
        public:

        Component(GameObject& associated);

        virtual ~Component();

        virtual void Update(double dt) = 0;

        virtual void Render() = 0;

        virtual bool Is(std::string) = 0;

        protected:
        
        GameObject& associated;

    };

}