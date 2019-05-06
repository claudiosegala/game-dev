#include <PenguinCannon.h>
#include <Game.h>
#include <State.h>
#include <Camera.h>
#include <Sprite.h>
#include <Bullet.h>
#include <Collider.h>
#include <Timer.h>

PenguinCannon::PenguinCannon(GameObject& go, std::weak_ptr<GameObject> penguinBody) : Component(go) {
    auto bg = new Sprite(go, "assets/img/cubngun.png");
    auto co = new Collider(go);

    go.AddComponent(bg);
    go.AddComponent(co);

    this->pbody = penguinBody;
    this->angle = 0.0f;
}

void PenguinCannon::Update(float dt) {
    static Timer *t = nullptr;

    if (t != nullptr) {
        t->Update(dt);
    }

    auto go = this->pbody.lock();

    if (go == nullptr) {
        this->associated.RequestDelete();
        return;
    }

    // Set position
    this->associated.box.SetCenter(go->box.Center());

    // Adjust Cannon
    auto &in = InputManager::GetInstance();
    auto x = static_cast<float>(in.GetMouseX()) + Camera::pos.x;
    auto y = static_cast<float>(in.GetMouseY()) + Camera::pos.y;
    auto dir = Vec2(x, y) - this->associated.box.Center();

    this->associated.angle = this->angle = dir.GetAngle();

    auto left_click = in.MousePress(LEFT_MOUSE_BUTTON);
    auto isInCoolDown = t != nullptr && t->Get() < 1.0f;

    if (left_click && !isInCoolDown) {
        if (t == nullptr) {
            t = new Timer();
        } else {
            t->Restart();
        }
        
        Shoot();
    }
}

void PenguinCannon::Render() {}

void PenguinCannon::NotifyCollision(GameObject &other) {
    UNUSED(other);
}

bool PenguinCannon::Is(std::string type) {
    return (type == "PenguinCannon");
}

void PenguinCannon::Shoot() {
    auto game = Game::GetInstance();
    auto state = game->GetState();

    auto go = new GameObject();
    // TODO: should I change to another sprite?
    auto bullet = new Bullet(*go, PI + this->angle, 100, 10, 1000.0, "assets/img/minionbullet2.png", 3, 0.2, true);
    go->box.SetCenter(Vec2(54, 0).GetRotate(this->angle) + this->associated.box.Center());
    go->angle = this->angle;

    go->AddComponent(bullet);
    state->AddObject(go);
}