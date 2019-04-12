#pragma once

#include <Component.h>
#include <Rect.h>
#include <Vec2.h>
#include <vector>
#include <string>
#include <memory>

class Component;

class GameObject {
    public:

    Rect box;

    GameObject();

    ~GameObject();

    void Update(float);

    void Render();

    bool IsDead();

    void RequestDelete();

    void AddComponent(Component*);

    void RemoveComponent(std::shared_ptr<Component>&);

    std::shared_ptr<Component> GetComponent(std::string);

    private:

    bool isDead;

    std::vector<std::shared_ptr<Component>> components;
};