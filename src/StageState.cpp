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
#include <EndState.h>
#include <Game.h>
#include <GameData.h>

const int StageState::aliens_count = 3;

StageState::StageState () : State() {
    Logger::Info("Initing Stage State");   
    this->started = false;
    this->quitRequested = false;

    this->music.Open("assets/audio/stageState.ogg");
    this->music.Play();

    CreateField();
    CreateMainCharacter();
    CreateEnemies();
}

StageState::~StageState () {
    Logger::Info("Destroying Stage State");

    if (this->tileSet != nullptr) {
        Logger::Info("Destroying Stage State TileSet");
        delete this->tileSet;
    }

    Logger::Info("Destroying Stage State Music");
    this->music.Stop();
}

void StageState::Start () {
    Logger::Info("Starting Stage State");
    LoadAssets();
    StartArray();

    this->started = true;
}

void StageState::Pause () {
    Logger::Info("Pausing Stage State");
}

void StageState::Resume () {
    Logger::Info("Resuming Stage State");
}

void StageState::LoadAssets () {
    Logger::Info("Loading Assets of Stage State");
    // TODO: fill?
}

void StageState::Update (float dt) {
    // TODO: check
    if (Alien::alienCount == 0) {
        EndMatch(true);
        return;
    }

    if (PenguinBody::player == nullptr) {
        EndMatch(false);
        return;
    }

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
    Logger::Info("Creating field for Stage State");
    auto field = new GameObject();

    this->tileSet = new TileSet(*field, 64, 64, "assets/img/tileset.png");

    auto bg = new Sprite(*field, "assets/img/ocean.jpg");
    field->AddComponent(bg);

    auto tm = new TileMap(*field, "assets/map/tileMap.txt", this->tileSet);
    field->AddComponent(tm);

    auto cf = new CameraFollower(*field);
    field->AddComponent(cf);

    field->box.vector = Vec2(0, 0);

    AddObject(field);
}

void StageState::CreateMainCharacter () {
    Logger::Info("Creating Main Character for Stage State");
    auto gameObject = new GameObject();

    auto mainChar = new PenguinBody(*gameObject);
    gameObject->AddComponent(mainChar);

    gameObject->box.vector = Vec2(704, 640);
    Camera::Follow(gameObject);

    AddObject(gameObject);
}

void StageState::CreateEnemies () {
    Logger::Info("Creating Enemies for Stage State");
    for (int i = 0; i < StageState::aliens_count; i++) {
        auto gameObject = new GameObject();
        auto alien = new Alien(*gameObject, 5);

        gameObject->AddComponent(alien);
        gameObject->box.vector = Vec2(
            512 + (rand() % 1000), 
            300 + (rand() % 1000)
        );

        AddObject(gameObject);
    }
}

void StageState::EndMatch (bool victory) {
    Logger::Info("Ending Match in Stage State");

    GameData::playerVictory = victory;

    this->popRequested = true;

    auto game = Game::GetInstance();

    game->Push(new EndState());
}