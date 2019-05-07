#include <Alien.h>
#include <Game.h>
#include <State.h>
#include <InputManager.h>
#include <PenguinBody.h>
#include <Camera.h>
#include <Bullet.h>
#include <Minion.h>
#include <Sound.h>
#include <Sprite.h>
#include <Collider.h>

int Alien::alienCount = 0;

// TODO: verify if it is ok
Alien::Alien(GameObject& go, int qnt_minions) : Component(go), minions(qnt_minions), restTimer(), destination(0, 0) {
    auto bg = new Sprite(go, "assets/img/alien.png");
    auto co = new Collider(go);

    go.AddComponent(bg);
    go.AddComponent(co);

    this->hp = 30;
    this->speed = Vec2(0, 0);
    this->state = AlienState::RESTING;

    Alien::alienCount++;
};

Alien::~Alien() {
    // I can do this cause it is the job of the shared_ptr
    // to free the memory
    this->minions.clear();

    Alien::alienCount--;
}

void Alien::Start() {
    auto game = Game::GetInstance();
    auto state = game->GetState();
    auto ownGo = state->GetObjectPtr(&this->associated);

    auto n = (int) this->minions.size();
    auto arc = 2 * PI / n;

    for (int i = 0; i < n; i++) {
        auto go = new GameObject();

        go->AddComponent(new Minion(*go, ownGo, arc * i));

        minions[i] = state->AddObject(go);
    }
}

void Alien::Update(float dt) {
    auto &in = InputManager::GetInstance();
    auto x = static_cast<float>(in.GetMouseX()) + Camera::pos.x;
    auto y = static_cast<float>(in.GetMouseY()) + Camera::pos.y;

    if (this->state == AlienState::RESTING) {
        auto coolDown = 5;
        this->restTimer.Update(dt);

        if (this->restTimer.Get() > coolDown) {
            this->destination = Vec2(x, y);

            auto k = (float) 200.0; // to adjust speed    
            auto direction = Vec2(this->associated.box.Center(), this->destination).GetUnit();

            this->speed = direction * dt * k;

            this->state = AlienState::MOVING;
        }
    } else if (this->state == AlienState::MOVING) {
        auto start = this->associated.box.Center();
        auto destiny = this->destination;
        auto newPos = this->associated.box.Center() + this->speed;
        auto totalWalk = Vec2::Distance(start, destiny);
        auto walking = Vec2::Distance(start, newPos);

        if (totalWalk > walking) {
            // Walk the distance
            this->associated.box.SetCenter(newPos);
        } else {
            // Stop on the point
            this->associated.box.SetCenter(destiny);

            // Set speed to (0, 0)
            this->speed.Reset();

            // Change state
            this->state = AlienState::RESTING;

            // Init again the Timer
            this->restTimer.Restart();

            auto pg = PenguinBody::player;

            if (pg != nullptr) {
                Shoot(pg->GetPosition());
            } else {
                this->state = AlienState::NOP;
            }
        }
    }

    this->associated.angle -= 0.001;
}

void Alien::Shoot (Vec2 pos) {
    // Choose closest minion
    auto idx = 0;
    auto m = 1e9f;

    for (int i = 0; i < (int) this->minions.size(); i++) {
        auto go = this->minions[i].lock();
        auto dist = Vec2::Distance(go->box.Center(), pos);

        if (go != nullptr && m >= dist) {
            m = dist;
            idx = i;    
        }
    }

    auto go = this->minions[idx].lock();

    if (go != nullptr) {
        auto component = go->GetComponent("Minion");

        if (component != nullptr) {
            auto minion = std::static_pointer_cast<Minion>(component);

            // Make it shoot
            minion->Shoot(pos);
        }
    }
}

void Alien::Render() {}

// TODO: verify if I should do on the others
void Alien::NotifyCollision(GameObject &other) {
    auto component = other.GetComponent("Bullet");
    
    if (component != nullptr) {
        auto bullet = std::static_pointer_cast<Bullet>(component);

        if (bullet->targetPlayer) {
            this->hp -= bullet->GetDamage();

            if (this->hp <= 0) {
                this->associated.RequestDelete();
                
                auto gm = Game::GetInstance();
                auto st = gm->GetState();

                auto go = new GameObject();
                auto bg = new Sprite(*go, "assets/img/aliendeath.png", 4, 0.05, 0.2);
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

bool Alien::Is(std::string type) {
    return (type == "Alien");
}