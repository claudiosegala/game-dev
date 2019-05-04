#include <PenguinCannon.h>
#include <Game.h>
#include <State.h>
#include <Camera.h>
#include <Sprite.h>
#include <Bullet.h>

PenguinCannon::PenguinCannon(GameObject& go, std::weak_ptr<GameObject> penguinBody) : Component(go) {
    auto bg = new Sprite(go, "assets/img/cubngun.png");

    go.AddComponent(bg);

    this->pbody = penguinBody;
    this->angle = 0.0f;
}

void PenguinCannon::Update(float) {
    auto go = this->pbody.lock();

    if (go == nullptr) {
        this->associated.RequestDelete();
    }

    // Set position
    this->associated.box.SetCenter(go->box.Center());

    // Adjust Cannon
    auto &in = InputManager::GetInstance();
    auto x = static_cast<float>(in.GetMouseX()) + Camera::pos.x;
    auto y = static_cast<float>(in.GetMouseY()) + Camera::pos.y;
    auto dir = Vec2(x, y) - this->associated.box.Center();

    this->associated.angle = this->angle = dir.GetAngle();

    // Verify if it should shoot
    auto left_click = in.MousePress(LEFT_MOUSE_BUTTON);

    if (left_click) {
        Shoot();
    }
}

void PenguinCannon::Render() {}

bool PenguinCannon::Is(std::string type) {
    return (type == "PenguinCannon");
}

void PenguinCannon::Shoot() {
    auto game = Game::GetInstance();
    auto state = game->GetState();

    auto go = new GameObject();
    auto bullet = new Bullet(*go, PI + this->angle, 100, 10, 10000.0, "assets/img/minionbullet2.png", 3, 0.2);
    go->box.SetCenter(Vec2(54, 0).GetRotate(this->angle) + this->associated.box.Center());
    go->angle = this->angle;

    go->AddComponent(bullet);
    state->AddObject(go);
}