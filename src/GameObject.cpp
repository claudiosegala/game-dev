#include <GameObject.h>
#include <Component.h>
#include <Rectangle.h>
#include <Logger.h>
#include <vector>
#include <string>
#include <algorithm>

namespace penguin {

    GameObject::GameObject() {
        this->isDead = false;
    }

    GameObject::GameObject(Vector& p, int w, int h) : box(p, w, h) {
        this->isDead = false;
    }

    GameObject::~GameObject() {
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

    // TODO: not using... should I have used
    void GameObject::RemoveComponent(std::unique_ptr<Component> component) {
        auto it = std::remove_if(this->components.begin(), this->components.end(), [&] (auto const& c) { 
            return c == component;
        });

        this->components.erase(it, this->components.end());
    }

    std::unique_ptr<Component> GameObject::GetComponent(std::string type) {
        auto it = std::find_if(this->components.begin(), this->components.end(), [&] (Component* c) {
            return c->Is(type);
        });

        return it == this->components.end() ? nullptr : (*it);
    }

}