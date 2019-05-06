#include <Minion.h>
#include <Sprite.h>
#include <Bullet.h>
#include <Collider.h>
#include <Game.h>
#include <State.h>

Minion::Minion (GameObject& go, std::weak_ptr<GameObject> alienCenter, float arcOffset) : Component(go) {
    this->alienCenter = alienCenter;
    this->arc = arcOffset;

    auto k = 1 + RAND/2;
    auto bg = new Sprite(this->associated, "assets/img/minion.png");

    bg->SetScale(k, k);

    auto co = new Collider(go);

    go.AddComponent(bg);
    go.AddComponent(co);


    SetPosition(0);
}
    
void Minion::Update(float dt) {
    SetPosition(dt);
}

void Minion::Render() {}

void Minion::NotifyCollision(GameObject &other) {
    UNUSED(other);
}

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
    this->associated.angle = this->arc;
    this->arc += 0.3 * dt;
}

void Minion::Shoot(Vec2 pos) {
    auto center = this->associated.box.Center();
    auto dir = (pos - center) * -1;
    auto ang = dir.GetAngle();

    auto game = Game::GetInstance();
    auto state = game->GetState();

    auto go = new GameObject();
    auto bullet = new Bullet(*go, ang, 100, 10, 10000.0, "assets/img/minionbullet2.png", 3, 0.2, false);

    go->box.SetCenter(center);
    go->angle = PI + ang;

    go->AddComponent(bullet);
    state->AddObject(go);
}