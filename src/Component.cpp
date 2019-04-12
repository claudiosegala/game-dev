#include <Component.h>
#include <GameObject.h>
#include <Logger.h>

Component::Component(GameObject& obj) : associated(obj) {}

Component::~Component() {}