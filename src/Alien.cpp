#include <Alien.h>
#include <InputManager.h>
#include <Camera.h>
#include <Sprite.h>

// TODO: verify if it is ok
Alien::Alien(GameObject& go, int qnt_minions) : Component(go) {
    auto sp = new Sprite(go, "TODO");

    go.AddComponent(sp);

    this->hp = 30;
    this->speed = Vec2(0, 0);
};

// TODO: verify if I can do this
Alien::~Alien() {
    this->minions.clear();
}

void Alien::Start() {
    // TODO: populate monions
}

void Alien::Update(float dt) {
    auto &in = InputManager::GetInstance();
    auto right_click = in.MousePress(RIGHT_MOUSE_BUTTON);
    auto left_click = in.MousePress(LEFT_MOUSE_BUTTON);

    auto x = static_cast<float>(in.GetMouseX()) + Camera::pos.x;
    auto y = static_cast<float>(in.GetMouseY()) + Camera::pos.y;

    if (left_click) {
        auto type = Action::ActionType::MOVE;
        auto action = Action(type, x, y);

        this->taskQueue.push(action);
    }

    if (right_click) {
        auto type = Action::ActionType::SHOOT;
        auto action = Action(type, x, y);
        
        this->taskQueue.push(action);
    }

    if (this->taskQueue.empty()) {
        return;
    }
}

void Alien::Render() {

}

bool Alien::Is(std::string type) {
    return (type == "Alien");
}

Alien::Action::Action (ActionType type, float x, float y) {
    this->pos = Vec2(x, y);
    this->type = type;
}