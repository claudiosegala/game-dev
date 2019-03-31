#include <Component.h>
#include <GameObject.h>
#include <Logger.h>

namespace penguin {

    Component::Component(GameObject& obj) : associated(obj) {}

}