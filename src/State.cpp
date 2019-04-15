#include <State.h>
#include <Camera.h>
#include <Sound.h>
#include <Sprite.h>
#include <Music.h>
#include <Rect.h>
#include <Vec2.h>
#include <Face.h>
#include <TileSet.h>
#include <TileMap.h>
#include <InputManager.h>
#include <Util.h>
#include <Logger.h>
#include <algorithm>
#include <string>

State::State () {
    auto obj = new GameObject();
    auto ts = new TileSet(*obj, 64, 64, "assets/img/tileset.png");
    auto tm = new TileMap(*obj, "assets/map/tileMap.txt", ts);
    auto bg = new Sprite(*obj, "assets/img/ocean.jpg");

    obj->AddComponent(bg);
    obj->AddComponent(tm);
    obj->box.vector = Vec2(0, 0);

    this->quitRequested = false;
    this->music.Open("assets/audio/stageState.ogg");
    this->music.Play();
    this->objects.emplace_back(obj);
}

State::~State () {
    Logger::Info("Destroying State");
    this->music.Stop();
    this->objects.clear();
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

    if (in.KeyPress(SPACE_BAR)) {
        auto x = in.GetMouseX() + Camera::pos.x;
        auto y = in.GetMouseY() + Camera::pos.y;
        auto pos = Vec2(x, y);
        
        pos += Vec2(200.0, 0.0).GetRotate(TAO * RAND);

        AddObject((int)pos.x, (int)pos.y);
    }

    for (auto &obj : this->objects) {
        obj->Update(dt);
    }
    
    Prune();
}

void State::Render () {
    for (auto &obj : this->objects) {
        obj->Render();
    }
}

bool State::QuitRequested () {
    return this->quitRequested;
}

void State::Prune () {
    // Logger::Info("Prunning");
    auto it = std::remove_if(this->objects.begin(), this->objects.end(), [&] (std::shared_ptr<GameObject>& o) { 
        return o->IsDead();
    });

    this->objects.erase(it, this->objects.end());
}

void State::AddObject (int mouseX, int mouseY) {
    auto obj = new GameObject();
    auto sound = new Sound(*obj, "assets/audio/boom.wav");
    auto sprite = new Sprite(*obj, "assets/img/penguinface.png");
    auto face = new Face(*obj);

    // Add components to the object
    obj->AddComponent(sound);
    obj->AddComponent(sprite);
    obj->AddComponent(face);

    // Adjust position for the sprite
    auto x = static_cast<float>(mouseX);
    auto y = static_cast<float>(mouseY);
    obj->box.vector = Vec2(x, y) - Vec2(obj->box.width/2, obj->box.height/2);

    // Insert
    this->objects.emplace_back(obj);
}