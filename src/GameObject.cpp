#include <GameObject.h>

GameObject::GameObject() {
    this->started = false;
    this->isDead = false;
}

GameObject::~GameObject() {
    this->box.~Rect();
    this->components.clear();
}

void GameObject::Start () {
    for (auto &component : this->components) {
        component->Start();
    }

    this->started = true;
}

void GameObject::Update(float dt) {
    for (auto &component : this->components) {
        component->Update(dt);
    }
}

void GameObject::Render() {
    for (auto &component : this->components) {
        component->Render();
    }
}

bool GameObject::IsDead() {
    return this->isDead;
}

void GameObject::RequestDelete() {
    this->isDead = true;
}

void GameObject::AddComponent(Component* component) {
    this->components.emplace_back(component);

    if (this->started) {
        component->Start();
    }
}

void GameObject::RemoveComponent(std::shared_ptr<Component>& component) {
    auto it = std::remove_if(this->components.begin(), this->components.end(), [&] (std::shared_ptr<Component>& c) { 
        return c == component;
    });

    this->components.erase(it, this->components.end());
}

std::shared_ptr<Component> GameObject::GetComponent(std::string type) {
    auto it = std::find_if(this->components.begin(), this->components.end(), [&] (std::shared_ptr<Component>& c) {
        return c->Is(type);
    });

    if (it != this->components.end()) {
        return (*it);
    } else {
        return nullptr;
    }
}