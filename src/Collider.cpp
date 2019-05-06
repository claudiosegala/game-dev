#include <Collider.h>
#include <Vec2.h>

Collider::Collider (GameObject& go, Vec2 scale, Vec2 offset ) : Component(go) {
    this->scale = scale;
    this->offset = offset;
}

void Collider::Update(float dt) {
    UNUSED(dt);
    
    this->box = this->associated.box;
    this->box.width *= this->scale.x;
    this->box.height *= this->scale.y;
    this->box.SetCenter(this->associated.box.Center() + this->offset.GetRotate(this->associated.angle));
}

void Collider::Render() {}

void Collider::NotifyCollision(GameObject &other) {
    // TODO: implemente
}

bool Collider::Is(std::string type) {
    return (type == "Collider");
}

void Collider::SetScale(Vec2 scale) {
    this->scale = scale;
}

void Collider::SetOffset(Vec2 offset) {
    this->offset = offset;
}
