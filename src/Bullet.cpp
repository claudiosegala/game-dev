#include <Bullet.h>
#include <GameObject.h>
#include <Vec2.h>
#include <Sprite.h>
#include <Collider.h>
#include <PenguinBody.h>

Bullet::Bullet(GameObject& go, float angle, float speed, int damage, float maxDistance, std::string sprite, int frameCount, float frameTime, bool targetPlayer) : Component(go) {
    auto bg = new Sprite(go, sprite, frameCount, frameTime);
    auto co = new Collider(go);

    go.AddComponent(bg);
    go.AddComponent(co);

    this->targetPlayer = targetPlayer;
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

void Bullet::NotifyCollision(GameObject &other) {
    // TODO: discover why is not hitting
    if (other.GetComponent("PenguinBody") != nullptr || other.GetComponent("Alien") != nullptr) {
        this->associated.RequestDelete();
    }
}

bool Bullet::Is(std::string type) {
    return (type == "Bullet");
}

int Bullet::GetDamage() {
    return this->damage;
}