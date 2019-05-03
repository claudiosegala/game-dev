#include <Alien.h>
#include <InputManager.h>
#include <Camera.h>

// TODO: verify if it is ok
Alien(GameObject& go, int qnt_minions) : Component(go) {
    auto sp = new Sprite(go, "TODO");

    go.AddComponent(sp);

    this->hp = 30;
    this->speed = { 0, 0 };
};

// TODO: verify if I can do this
~Alien() {
    this->minions.clear();
}

void Start() {
    // TODO: populate monions
}

void Update(float dt) {
    auto in = InputManager::GetInstance();
    auto right_click = in.IsMousePress(RIGHT_MOUSE_BUTTON);
    auto left_click = in.IsMousePress(LEFT_MOUSE_BUTTON);

    auto x = static_cast<float>(in.GetMouseX()) + Camera::pos::x;
    auto y = static_cast<float>(in.GetMouseY()) + Camera::pos::y;

    if (left_click) {
        auto type = Alien::ActionType.MOVE;
        auto action = Alien::Action(type, x, y);

        this->taskQueue.push(action);
    }

    if (right_click) {
        auto type = Alien::ActionType.SHOOT;
        auto action = Alien::Action(type, x, y);
        
        this->taskQueue.push(action);
    }

    if (this->taskQueue.empty()) {
        return;
    }
}

void Render() {

}

bool Is(std::string) {

}