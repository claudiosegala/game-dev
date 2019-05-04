#include <Minion.h>
#include <Sprite.h>

Minion::Minion (GameObject& go, std::weak_ptr<GameObject> alienCenter, float arcOffset) : Component(go) {
    this->alienCenter = alienCenter;
    this->arc = arcOffset;

    auto bg = new Sprite(go, "assets/img/minion.png");

    go.AddComponent(bg);

    SetPosition(0);
}
    
void Minion::Update(float dt) {
    SetPosition(dt);
}

void Minion::Render() {}

bool Minion::Is(std::string type) {
    return (type == "Minion");
}

void Minion::SetPosition(float dt) {
    auto alien = alienCenter.lock();

    if (alien == nullptr) {
        this->associated.RequestDelete();
        return;
    }
    
    auto distAlien = Vec2(200, 0);
    auto alienPos = alien->box.Center();

    distAlien.Rotate(this->arc);
    distAlien += alienPos;

    this->associated.box.SetCenter(distAlien);
    this->arc += 0.3 * dt;
}

void Minion::Shoot(Vec2) {
    // TODO: later
}