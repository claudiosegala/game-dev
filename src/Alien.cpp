#include <Alien.h>
#include <Game.h>
#include <State.h>
#include <InputManager.h>
#include <Camera.h>
#include <Minion.h>
#include <Sprite.h>

// TODO: verify if it is ok
Alien::Alien(GameObject& go, int qnt_minions) : Component(go), minions(qnt_minions) {
    auto bg = new Sprite(go, "assets/img/alien.png");
    auto co = new Collider(go);

    go.AddComponent(bg);
    go.AddComponent(co);

    this->hp = 30;
    this->speed = Vec2(0, 0);
};

Alien::~Alien() {
    // I can do this cause it is the job of the shared_ptr
    // to free the memory
    this->minions.clear();
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
    this->associated.angle -= 0.01;

    auto &in = InputManager::GetInstance();
    auto right_click = in.MousePress(RIGHT_MOUSE_BUTTON);
    auto left_click = in.MousePress(LEFT_MOUSE_BUTTON);

    auto x = static_cast<float>(in.GetMouseX()) + Camera::pos.x;
    auto y = static_cast<float>(in.GetMouseY()) + Camera::pos.y;

    if (left_click) {
        auto type = Action::ActionType::MOVE;
        auto action = Action(type, x, y);

        this->taskQueue.push(action);
    }

    if (right_click) {
        auto type = Action::ActionType::SHOOT;
        auto action = Action(type, x, y);
        
        this->taskQueue.push(action);
    }

    if (this->taskQueue.empty()) {
        return;
    }

    auto task = taskQueue.front();

    if (task.type == Action::ActionType::MOVE) {
        Move(task, dt);
    } else {
        Shoot(task);
    }

    if (this->hp <= 0) {
        this->associated.RequestDelete();
    }
}

void Alien::Move (Action task, float dt) {
    auto start = this->associated.box.Center();
    auto destiny = task.pos;
    
    if (this->speed.IsOrigin()) {
        auto k = (float) 200.0; // to adjust speed    
        auto direction = Vec2(start, destiny).GetUnit();

        this->speed = direction * dt * k;
    }

    auto newPos = start + this->speed;
    
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

        // Remove completed task
        taskQueue.pop();
    }
}

void Alien::Shoot (Action task) {
    // Choose closest minion
    auto idx = 0;
    auto m = 1e9f;

    for (int i = 0; i < (int) this->minions.size(); i++) {
        auto go = this->minions[i].lock();
        auto dist = Vec2::Distance(go->box.Center(), task.pos);

        if (go != nullptr && m >= dist) {
            m = dist;
            idx = i;    
        }
    }

    auto go = this->minions[idx].lock();

    if (go != nullptr) {
        auto component = go->GetComponent("Minion");
        // TODO: treat empty component

        auto minion = std::static_pointer_cast<Minion>(component);

        // Make it shoot
        minion->Shoot(task.pos);
    }
    
    // Remove completed task
    taskQueue.pop();
}

void Alien::Render() {}

bool Alien::Is(std::string type) {
    return (type == "Alien");
}

Alien::Action::Action (ActionType type, float x, float y) {
    this->pos = Vec2(x, y);
    this->type = type;
}