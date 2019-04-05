#include <GameObject.h>
#include <Component.h>
#include <Rectangle.h>
#include <Logger.h>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>

namespace penguin {

    GameObject::GameObject() {
        this->isDead = false;
    }

    GameObject::~GameObject() {
        this->box.~Rectangle();
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

    void GameObject::RemoveComponent(std::unique_ptr<Component>& component) {
        auto it = std::remove_if(this->components.begin(), this->components.end(), [&] (std::unique_ptr<Component>& c) { 
            return c == component;
        });

        this->components.erase(it, this->components.end());
    }

    Component* GameObject::GetComponent(std::string type) {
        auto it = std::find_if(this->components.begin(), this->components.end(), [&] (std::unique_ptr<Component>& c) {
            return c->Is(type);
        });

        if (it != this->components.end()) {
            return (*it).get();
        } else {
            return nullptr;
        }
    }

}