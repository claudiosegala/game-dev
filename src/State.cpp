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
#include <PenguinBody.h>
#include <PenguinCannon.h>
#include <Collider.h>
#include <Collision.h>

State::State () {
    CreateField();
    CreateMainCharacter();
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
    Init();

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

    MakeUpdate(dt);
    CheckCollision();
    Prune();
}

void State::Init () {
    for (auto &field : this->objects) {
       field->Start();
    }
}

void State::Render () {
    for (auto &field : this->objects) {
        field->Render();
    }

    for (auto &field : this->objects) {
        auto component = field->GetComponent("TileMap");

        if (component == nullptr) continue;

        auto tileMap = std::static_pointer_cast<TileMap>(component);

        tileMap->RenderLayer(1, (int) Camera::pos.x, (int) Camera::pos.y);
    }
}

bool State::QuitRequested () {
    return this->quitRequested;
}

void State::MakeUpdate(float dt) {
    for (int i = 0; i < (int) this->objects.size(); i++) {
        this->objects[i]->Update(dt);
    }
}

void State::CheckCollision () {
    std::vector<int> objs;

    for (int i = 0; i < (int) this->objects.size(); i++) {
        if (this->objects[i]->GetComponent("Collider") != nullptr) {
            objs.push_back(i);
        }
    }


    for (int i = 0; i < (int) objs.size(); i++) {
        for (int j = i+1; j < (int) objs.size(); j++) {
            auto obj1 = this->objects[objs[i]];
            auto obj2 = this->objects[objs[j]];

            if (Collision::IsColliding(obj1->box, obj2->box, obj1->angle, obj2->angle)) {
                auto obj1_ptr = obj1.get();
                auto obj2_ptr = obj2.get();

                if (obj1_ptr) {
                    obj2->NotifyCollision(*obj1_ptr);
                }

                if (obj2_ptr) {
                    obj1->NotifyCollision(*obj2_ptr);
                }
            }
        }
    }
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

    auto ts = new TileSet(*field, 64, 64, "assets/img/tileset.png");
    auto tm = new TileMap(*field, "assets/map/tileMap.txt", ts);
    field->AddComponent(tm);

    auto cf = new CameraFollower(*field);
    field->AddComponent(cf);

    field->box.vector = Vec2(0, 0);

    this->objects.emplace_back(field);
}

void State::CreateMainCharacter () {
    auto mainChar = new GameObject();

    auto pd = new PenguinBody(*mainChar);
    mainChar->AddComponent(pd);

    mainChar->box.vector = Vec2(704, 640);

    this->objects.emplace_back(mainChar);

    Camera::Follow(mainChar);
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