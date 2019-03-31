#include "Component.h"
#include "GameObject.h"

namespace penguin {

    Component::Component(GameObject& obj) : associated(obj) {}

}