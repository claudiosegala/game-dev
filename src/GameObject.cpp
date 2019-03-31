#include "GameObject.h"
#include "Component.h"
#include "Rectangle.h"

#include <vector>
#include <string>
#include <algorithm>

namespace penguin {

    GameObject::GameObject() {
        this->isDead = false;
    }

    GameObject::~GameObject() {
        for (auto &component : this->components) {
            delete component;
        }

        this->components.clear();
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
    }

    void GameObject::RemoveComponent(Component* component) {
        auto it = std::remove_if(this->components.begin(), this->components.end(), f = [&] (Component* c) { 
            return c == component;
        });

        this->components.erase(it, this->components.end());
    }

    Component* GameObject::GetComponent(std::string type) {
        auto it = std::find_if(this->components.begin(), this->components.end(), [&] (Component* c) {
            return c->Is(type);
        });

        return it == this->components.end() ? nullptr : (*it);
    }

}