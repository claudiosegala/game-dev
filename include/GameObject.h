#pragma once

#include <Component.h>
#include <Logger.h>
#include <Rect.h>
#include <Vec2.h>
#include <Util.h>

#include <vector>
#include <string>
#include <memory>
#include <algorithm>

class Component;

class GameObject {
    public:

    Rect box;

    GameObject();

    ~GameObject();

    void Start();

    void Update(float);

    void Render();

    bool IsDead();

    void RequestDelete();

    void AddComponent(Component*);

    void RemoveComponent(std::shared_ptr<Component>&);

    std::shared_ptr<Component> GetComponent(std::string);

    private:

    bool started;

    bool isDead;

    std::vector<std::shared_ptr<Component>> components;
};