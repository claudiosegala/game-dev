#include <PenguinBody.h>
#include <Sprite.h>
#include <Sound.h>
#include <PenguinCannon.h>
#include <Game.h>
#include <State.h>
#include <Collider.h>
#include <Bullet.h>
#include <Camera.h>

int const PenguinBody::life = 50;

float const PenguinBody::spinPace = 2.5f;

float const PenguinBody::pace = 1.5f;

float const PenguinBody::maxSpeed = 6.0f;

PenguinBody* PenguinBody::player;

PenguinBody::PenguinBody (GameObject& associated) : Component(associated), pcannon() {
    // Adding image
    auto image = new Sprite(this->associated, "assets/img/penguin.png");
    this->associated.AddComponent(image);

    // Adding collider
    auto collider = new Collider(this->associated);
    this->associated.AddComponent(collider);

    // Initing variables
    this->hp = PenguinBody::life;
    this->angle = 0.0f;
    this->linearSpeed = 0.0f;
    this->speed = Vec2(0, 0);

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
    auto& in  = InputManager::GetInstance();

    auto keyA = in.IsKeyDown(A_KEY);
    auto keyD = in.IsKeyDown(D_KEY);
    auto keyW = in.IsKeyDown(W_KEY);
    auto keyS = in.IsKeyDown(S_KEY);

    if (keyW || keyS) {
        this->linearSpeed += (keyW ? 1 : -1) * PenguinBody::pace * dt;
        this->linearSpeed = this->linearSpeed > 0 ? fmin(this->linearSpeed, PenguinBody::maxSpeed) : fmax(this->linearSpeed, -PenguinBody::maxSpeed);
    }

    if (keyA || keyD) {
        this->angle += (keyA ? 1 : -1) * PenguinBody::spinPace * dt;
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
                this->associated.RequestDelete();
                
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

Vec2 PenguinBody::GetPosition() {
    return this->associated.box.Center();
}