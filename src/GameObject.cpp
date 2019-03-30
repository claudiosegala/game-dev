#include "GameObject.h"
#include "Component.h"
#include "Rectangle.h"

#include <vector>
#include <string>
#include <algorithm>

namespace penguin {

    GameObject::GameObject() {
        // TODO: init rectangle
        this->isDead = false;
    }

    GameObject::~GameObject() {
        // TODO: see if this is OK
        for (auto component : this->components) {
            delete component;
        }

        this->components.clear();
    }

    void GameObject::Update(float dt) {
        for (auto component : this->components) {
            component->Update(dt);
        }
    }

    void GameObject::Render() {
        for (auto component : this->components) {
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
        this->components.push_back(component);
    }

    void GameObject::RemoveComponent(Component* component) {
        auto b = this->components.begin();
        auto e = this->components.end();
        auto it = std::find(b, e, component);
        auto found = (it != e);

        if (found) {
            delete *it;

            this->components.erase(it);
        }
    }

    Component* GameObject::GetComponent(std::string type) {
        for (auto component : this->components) {
            if (component->Is(type)) {
                return component;
            }
        }

        return nullptr;
    }

}