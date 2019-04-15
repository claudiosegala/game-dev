#include <Component.h>
#include <GameObject.h>
#include <Logger.h>

Component::Component(GameObject& go) : associated(go) {}

Component::~Component() {}