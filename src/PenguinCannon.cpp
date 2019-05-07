#include <PenguinCannon.h>
#include <Game.h>
#include <State.h>
#include <Camera.h>
#include <Sprite.h>
#include <Bullet.h>
#include <Collider.h>
#include <Timer.h>

PenguinCannon::PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody) : Component(associated) {
    // Adding image
    auto image = new Sprite(this->associated, "assets/img/cubngun.png");
    this->associated.AddComponent(image);

    // Adding Collider
    auto collider = new Collider(this->associated);
    this->associated.AddComponent(collider);

    // Initing variables
    this->pbody = penguinBody;
    this->angle = 0.0f;
}

void PenguinCannon::Update(float dt) {
    static Timer *t = nullptr;

    if (t != nullptr) {
        t->Update(dt);
    }

    auto penguinBody = this->pbody.lock();

    if (penguinBody == nullptr) {
        this->associated.RequestDelete();
        return;
    }

    // Set position
    this->associated.box.SetCenter(penguinBody->box.Center());

    // Adjust Cannon
    auto &in = InputManager::GetInstance();
    auto dir = in.GetMouse(Camera::pos) - this->associated.box.Center();

    this->associated.angle = this->angle = dir.GetAngle();

    auto left_click = in.MousePress(LEFT_MOUSE_BUTTON);
    // TODO: make a constant
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

bool PenguinCannon::Is(std::string type) {
    return (type == "PenguinCannon");
}

void PenguinCannon::Shoot() {
    auto game = Game::GetInstance();
    auto state = game->GetState();

    auto gameObject = new GameObject();
    // TODO: should I change to another sprite?
    // TODO: make this constant
    auto bullet = new Bullet(*gameObject, PI + this->angle, 100, 10, 1000.0, "assets/img/minionbullet2.png", 3, 0.2, true);
    // TODO: make this constant
    gameObject->box.SetCenter(Vec2(54, 0).GetRotate(this->angle) + this->associated.box.Center());
    gameObject->angle = this->angle;

    gameObject->AddComponent(bullet);
    state->AddObject(gameObject);
}