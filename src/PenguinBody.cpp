#include <PenguinBody.h>
#include <Sprite.h>
#include <Sound.h>
#include <PenguinCannon.h>
#include <Game.h>
#include <StageState.h>
#include <Collider.h>
#include <Bullet.h>
#include <Camera.h>

int const PenguinBody::life = 50;

float const PenguinBody::spinPace = 1.5f;

float const PenguinBody::pace = 0.5f;

float const PenguinBody::maxSpeed = 1.0f;

PenguinBody* PenguinBody::player;

PenguinBody::PenguinBody (GameObject& associated) : Component(associated), pcannon() {
    Logger::Info("Creating Penguin Body");

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
    Logger::Info("Destroying Penguin Body");

    PenguinBody::player = nullptr;
}

void PenguinBody::Start() {
    Logger::Info("Starting Penguin Body");

    auto game = Game::GetInstance();
    auto state = game->GetCurrentState();
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
        this->angle += (keyA ? -1 : 1) * PenguinBody::spinPace * dt;
    }

    this->speed = Vec2(1, 0).GetRotate(this->angle) * linearSpeed;
    this->associated.angle = this->angle;

    if (ValidatePosition(this->associated.box, this->speed)) {
        this->associated.box.vector += this->speed;
    }
}

void PenguinBody::Render() {}

void PenguinBody::NotifyCollision(GameObject &other) {
    auto component = other.GetComponent("Bullet");

    if (component == nullptr) return;    
    
    auto bullet = std::static_pointer_cast<Bullet>(component);

    // Check if bullet was launch by me
    if (bullet->targetPlayer) return;

    // Alien loses life
    this->hp -= bullet->GetDamage();

    // Check if has died
    if (this->hp > 0) return;

    // Unfollow to avoid erros
    Camera::Unfollow();

    // 'Dies'
    this->associated.RequestDelete();

    // Start adding Animation of death
    auto gameObject = new GameObject();
    
    // Adding explosion image
    auto image = new Sprite(*gameObject, "assets/img/penguindeath.png", 5, 0.05, 0.25);
    gameObject->box = this->associated.box;
    gameObject->AddComponent(image);

    // Adding sound of explosion
    auto sound = new Sound(*gameObject, "assets/audio/boom.wav");
    gameObject->AddComponent(sound);
    sound->Play();

    // Adding to state
    auto game = Game::GetInstance();
    auto state = game->GetCurrentState();
    state->AddObject(gameObject);
}

bool PenguinBody::Is(std::string type) {
    return (type == "PenguinBody");
}

Vec2 PenguinBody::GetPosition() {
    return this->associated.box.Center();
}

// TODO: improve
bool PenguinBody::ValidatePosition (Rect curr, Vec2 movement) {
    auto nxt = curr.vector + movement;
    
    std::vector<Vec2> P { 
        Vec2(nxt.x, nxt.y + curr.height),
        Vec2(nxt.x + curr.width, nxt.y + curr.height),
        Vec2(nxt.x + curr.width, nxt.y),
        Vec2(nxt.x, nxt.y)
    };

    for (auto p : P) {
        if (p.x < 0 || p.x > 1408 || p.y < 0 || p.y > 1280) {
            return false;
        }
    }

    return true;
}