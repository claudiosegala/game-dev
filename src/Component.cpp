#include "Component.h"

namespace penguin {

    Component::Component(GameObject& obj) {
        this->associated = obj;
    }

    Component::~Component() {}

}