#include <Camera.h>
#include <CameraFollower.h>
#include <InputManager.h>
#include <Rect.h>
#include <Sound.h>
#include <Sprite.h>
#include <State.h>
#include <TileMap.h>
#include <TileSet.h>
#include <Vec2.h>
#include <Alien.h>

State::State () {
    CreateField();
    CreateEnemies();
    
    this->started = false;
    this->quitRequested = false;

    this->music.Open("assets/audio/stageState.ogg");
    this->music.Play();
}

State::~State () {
    Logger::Info("Destroying State");
    this->music.Stop();
    this->objects.clear();
}

void State::Start () {
    LoadAssets();

    for (auto &field : this->objects) {
       field->Start();
    }

    this->started = true;
}

void State::LoadAssets () {
    // For now, nothing
}

void State::Update (float dt) {
    auto& in = InputManager::GetInstance();

    this->quitRequested = in.IsKeyDown(ESCAPE_KEY) | in.QuitRequested();

    if (this->quitRequested) {
        Logger::Info("Quitting");
        return;
    }

    Camera::Update(dt);

    for (int i = 0; i < (int) this->objects.size(); i++) {
        this->objects[i]->Update(dt);
    }
    
    Prune();
}

void State::Render () {
    for (auto &field : this->objects) {
        field->Render();
    }
}

bool State::QuitRequested () {
    return this->quitRequested;
}

void State::Prune () {
    auto it = std::remove_if(this->objects.begin(), this->objects.end(), [&] (std::shared_ptr<GameObject>& o) { 
        return o->IsDead();
    });

    this->objects.erase(it, this->objects.end());
}

void State::CreateField () {
    auto field = new GameObject();

    auto bg = new Sprite(*field, "assets/img/ocean.jpg");
    field->AddComponent(bg);

    // TODO: make alien being rendered before clouds
    auto ts = new TileSet(*field, 64, 64, "assets/img/tileset.png");
    auto tm = new TileMap(*field, "assets/map/tileMap.txt", ts);
    field->AddComponent(tm);

    auto cf = new CameraFollower(*field);
    field->AddComponent(cf);

    field->box.vector = Vec2(0, 0);

    this->objects.emplace_back(field);
}

void State::CreateEnemies () {
    auto alien = new GameObject();

    auto al = new Alien(*alien, 5);
    alien->AddComponent(al);

    alien->box.vector = Vec2(512, 300);

    this->objects.emplace_back(alien);
}

std::weak_ptr<GameObject> State::AddObject (GameObject* field) {
    this->objects.emplace_back(field);

    if (this->started) {
        field->Start();
    }

    return this->objects.back();
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* field) {
    auto ptr = std::find_if(this->objects.begin(), this->objects.end(), [&](const std::shared_ptr<GameObject>& _go) {
        return _go.get() == field;
    });

    return ptr != this->objects.end() 
        ? std::weak_ptr<GameObject>(*ptr)
        : std::weak_ptr<GameObject>();
}