#include <Alien.h>
#include <InputManager.h>
#include <Camera.h>
#include <Sprite.h>

// TODO: verify if it is ok
Alien::Alien(GameObject& go, int qnt_minions) : Component(go), minions(qnt_minions) {
    auto bg = new Sprite(go, "assets/img/alien.png");

    go.AddComponent(bg);

    this->hp = 30;
    this->speed = Vec2(0, 0);
};

Alien::~Alien() {
    // I can do this cause it is the job of the shared_ptr
    // to free the memory
    this->minions.clear();
}

void Alien::Start() {
    // TODO: populate monions
}

void Alien::Update(float dt) {
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
        W(dt);
        Move(task, dt);
    } else {
        Shoot(task);
    }

    if (this->hp <= 0) {
        associated.RequestDelete();
    }
}

void Alien::Move (Action task, float dt) {
    auto pos = this->associated.box.Center();
    auto start = Point(pos.x, pos.y);
    auto destiny = Point(task.pos.x, task.pos.y);
    
    if (this->speed.IsOrigin()) {
        auto k = (float) 200.0; // to adjust speed    
        auto direction = Vec2(start, destiny).GetUnit();

        direction *= (dt * k);

        this->speed = direction;
    }

    auto newPos = start + this->speed;
    
    auto totalWalk = Point::Distance(start, destiny);
    auto walking = Point::Distance(start, newPos);

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
    UNUSED(task);
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