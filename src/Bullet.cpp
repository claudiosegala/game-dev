#include <Bullet.h>
#include <GameObject.h>
#include <Vec2.h>
#include <Sprite.h>
#include <Point.h>

Bullet::Bullet(GameObject& go, float angle, float speed, int damage, float maxDistance, std::string sprite) : Component(go) {
    auto bg = new Sprite(go, sprite);

    go.AddComponent(bg);

    this->distanceLeft = maxDistance;
    this->damage = damage;
    this->speed = Vec2(1, 0).GetRotate(angle) * speed;
}

void Bullet::Update(float dt) {
    auto diff = this->speed * dt;

    this->distanceLeft -= diff.GetLength();

    if (this->distanceLeft <= 0) {
        this->associated.RequestDelete();
        return;
    }

    this->associated.box.vector -= diff;
}

void Bullet::Render() {}

bool Bullet::Is(std::string type) {
    return (type == "Bullet");
}

int Bullet::GetDamage() {
    return this->damage;
}