#include <Component.h>

Component::Component(GameObject& go) : associated(go) {}

Component::~Component() {}