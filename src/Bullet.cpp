#include <Bullet.h>
#include <GameObject.h>
#include <Vec2.h>
#include <Point.h>

void Bullet(GameObject& go, float angle, float speed, int damage, float maxDistance, std::string sprite) : Component(go) {
    auto bg = new Sprite(go, sprite);

    go.AddComponent(bg);

    this->distanceLeft = maxDistance;
    this->damage = damage;
    this->speed = V(1, 0).GetRotate(angle) * speed;
}

void Update(float dt) {
    auto diff = this->speed * dt;

    this->distanceLeft -= diff.GetLength();

    if (this->distanceLeft <= 0) {
        this->associated.RequestDelete();
        return;
    }

    this->associated.box.vector -= diff;
}

void Render() {}

bool Is(std::string type) {
    return (type == "Bullet");
}

int GetDamage() {
    return this->damage;
}