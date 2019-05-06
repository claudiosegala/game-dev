#include <PenguinBody.h>
#include <Sprite.h>
#include <PenguinCannon.h>
#include <Game.h>
#include <State.h>
#include <Collider.h>
#include <Bullet.h>
#include <Camera.h>

PenguinBody* PenguinBody::player;

PenguinBody::PenguinBody (GameObject& go) : Component(go) {
    auto bg = new Sprite(go, "assets/img/penguin.png");
    auto co = new Collider(go);

    go.AddComponent(bg);
    go.AddComponent(co);

    this->hp = 50;
    this->angle = 0.0f;
    this->linearSpeed = 0.0f;
    this->speed = Vec2(0, 0);
    // TODO: should I initialize?
    // this->pcannon = std::weak_ptr<PenguinCannon>();

    PenguinBody::player = this;
}

PenguinBody::~PenguinBody() {
    PenguinBody::player = nullptr;
}

void PenguinBody::Start() {
    auto game = Game::GetInstance();
    auto state = game->GetState();
    auto ownGo = state->GetObjectPtr(&this->associated);

    auto go = new GameObject();
    auto pc = new PenguinCannon(*go, ownGo);

    go->AddComponent(pc);

    this->pcannon = state->AddObject(go);
}

void PenguinBody::Update(float dt) {
    if (this->hp <= 0) {
        this->associated.RequestDelete();
        return;
    }

    auto& in  = InputManager::GetInstance();

    auto a = in.IsKeyDown(A_KEY);
    auto d = in.IsKeyDown(D_KEY);
    auto w = in.IsKeyDown(W_KEY);
    auto s = in.IsKeyDown(S_KEY);

    if (w || s) {
        auto k = 5;
        auto ls = this->linearSpeed + (w ? 1 : -1) * k * dt;
        auto maxVelocity = 10;

        this->linearSpeed = ls > 0 ? fmin(ls, maxVelocity) : fmax(ls, -maxVelocity);
    }

    if (a || d) {
        auto k = 5;
        this->angle += (a ? 1 : -1) * k * dt;
    }

    this->speed = Vec2(1, 0).GetRotate(this->angle) * linearSpeed;
    this->associated.angle = this->angle;
    this->associated.box.vector += this->speed;
}

void PenguinBody::Render() {}

void PenguinBody::NotifyCollision(GameObject &other) {
    auto component = other.GetComponent("Bullet");
    
    if (component != nullptr) {
        auto bullet = std::static_pointer_cast<Bullet>(component);

        if (!bullet->targetPlayer) {
            this->hp -= bullet->GetDamage();

            Camera::Unfollow();

            if (this->hp <= 0) {
                auto gm = Game::GetInstance();
                auto st = gm->GetState();

                auto go = new GameObject();
                auto bg = new Sprite(*go, "assets/img/penguindeath.png", 5, 0.05, 0.25);
                auto sd = new Sound(*go, "assets/img/penguindeath.png");

                go->box = this->associated.box;
                go->AddComponent(bg);
                go->AddComponent(sd);
                st->AddObject(go);
                // TODO: should I play it here?
                sd->Play();
            }
        }
    }
}

bool PenguinBody::Is(std::string type) {
    return (type == "PenguinBody");
}