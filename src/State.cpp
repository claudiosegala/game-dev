#include <Camera.h>
#include <CameraFollower.h>
#include <Face.h>
#include <InputManager.h>
#include <Logger.h>
#include <Music.h>
#include <Rect.h>
#include <Sound.h>
#include <Sprite.h>
#include <State.h>
#include <TileMap.h>
#include <TileSet.h>
#include <Vec2.h>
#include <Util.h>

#include <algorithm>
#include <string>

State::State () {
    auto go = new GameObject();
    auto ts = new TileSet(*go, 64, 64, "assets/img/tileset.png");
    auto tm = new TileMap(*go, "assets/map/tileMap.txt", ts);
    auto bg = new Sprite(*go, "assets/img/ocean.jpg");
    auto cf = new CameraFollower(*go);

    go->AddComponent(cf);
    go->AddComponent(bg);
    go->AddComponent(tm);
    go->box.vector = Vec2(0, 0);

    this->quitRequested = false;
    this->music.Open("assets/audio/stageState.ogg");
    this->music.Play();
    this->objects.emplace_back(go);
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
        auto x = (float) in.GetMouseX() + Camera::pos.x;
        auto y = (float) in.GetMouseY() + Camera::pos.y;
        auto pos = Vec2(x, y);
        
        pos += Vec2(200.0, 0.0).GetRotate(TAO * RAND);

        AddObject((int)pos.x, (int)pos.y);
    }

    for (auto &go : this->objects) {
        go->Update(dt);
    }
    
    Prune();
}

void State::Render () {
    for (auto &go : this->objects) {
        go->Render();
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

void State::AddObject (int mouseX, int mouseY) {
    auto go = new GameObject();
    auto sound = new Sound(*go, "assets/audio/boom.wav");
    auto sprite = new Sprite(*go, "assets/img/penguinface.png");
    auto face = new Face(*go);

    // Add components to the object
    go->AddComponent(sound);
    go->AddComponent(sprite);
    go->AddComponent(face);

    // Adjust position for the sprite
    auto x = static_cast<float>(mouseX);
    auto y = static_cast<float>(mouseY);
    go->box.vector = Vec2(x, y) - Vec2(go->box.width/2, go->box.height/2);

    // Insert
    this->objects.emplace_back(go);
}