#include <Camera.h>
#include <CameraFollower.h>
#include <InputManager.h>
#include <Rect.h>
#include <Sound.h>
#include <Sprite.h>
#include <StageState.h>
#include <TileMap.h>
#include <TileSet.h>
#include <Vec2.h>
#include <Alien.h>
#include <PenguinBody.h>
#include <PenguinCannon.h>
#include <Collider.h>
#include <Collision.h>

StageState::StageState () : State() {
    CreateField();
    CreateMainCharacter();
    CreateEnemies();
    
    this->started = false;
    this->quitRequested = false;

    this->music.Open("assets/audio/stageState.ogg");
    this->music.Play();
}

StageState::~StageState () {
    // TODO: verify
    //Logger::Info("Destroying StageState TileSet");
    //delete this->tileSet;

    Camera::Unfollow();

    Logger::Info("Destroying StageState Music");
    this->music.Stop();
}

void StageState::Start () {
    LoadAssets();
    StartArray();

    this->started = true;
}

void StageState::Pause () {

}

void StageState::Resume () {
    
}

void StageState::LoadAssets () {
    // For now, nothing
}

void StageState::Update (float dt) {
    auto& in = InputManager::GetInstance();

    this->popRequested = in.KeyPress(ESCAPE_KEY);

    if (this->popRequested) return;

    this->quitRequested = in.QuitRequested();

    if (this->quitRequested) return;

    Camera::Update(dt);

    UpdateArray(dt);
    CheckCollision();
    PruneArray();
}

void StageState::Render () {
    RenderArray();

    for (auto &field : this->objectArray) {
        auto component = field->GetComponent("TileMap");

        if (component == nullptr) continue;

        auto tileMap = std::static_pointer_cast<TileMap>(component);

        tileMap->RenderLayer(1, (int) Camera::pos.x, (int) Camera::pos.y);
    }
}

void StageState::CheckCollision () {
    std::vector<int> objs;

    for (int i = 0; i < (int) this->objectArray.size(); i++) {
        if (this->objectArray[i]->GetComponent("Collider") != nullptr) {
            objs.push_back(i);
        }
    }


    for (int i = 0; i < (int) objs.size(); i++) {
        for (int j = i+1; j < (int) objs.size(); j++) {
            auto obj1 = this->objectArray[objs[i]];
            auto obj2 = this->objectArray[objs[j]];

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

void StageState::CreateField () {
    auto field = new GameObject();

    auto bg = new Sprite(*field, "assets/img/ocean.jpg");
    field->AddComponent(bg);

    auto ts = new TileSet(*field, 64, 64, "assets/img/tileset.png");
    auto tm = new TileMap(*field, "assets/map/tileMap.txt", ts);
    field->AddComponent(tm);

    auto cf = new CameraFollower(*field);
    field->AddComponent(cf);

    field->box.vector = Vec2(0, 0);

    AddObject(field);
}

void StageState::CreateMainCharacter () {
    auto mainChar = new GameObject();

    auto pd = new PenguinBody(*mainChar);
    mainChar->AddComponent(pd);

    mainChar->box.vector = Vec2(704, 640);
    Camera::Follow(mainChar);

    AddObject(mainChar);
}

void StageState::CreateEnemies () {
    auto alien = new GameObject();

    auto al = new Alien(*alien, 5);
    alien->AddComponent(al);

    alien->box.vector = Vec2(512, 300);

    AddObject(alien);
}