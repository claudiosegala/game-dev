#include <TitleState.h>
#include <GameObject.h>
#include <Rect.h>
#include <Sprite.h>
#include <Camera.h>
#include <Text.h>
#include <Game.h>
#include <StageState.h>
#include <InputManager.h>

TitleState::TitleState() : State() {
    auto gameObject = new GameObject();

    auto image = new Sprite(*gameObject, "assets/img/title.jpg");

    gameObject->AddComponent(image);

    AddObject(gameObject);

    Camera::Reset();
}
        
TitleState::~TitleState() {

}

void TitleState::LoadAssets() {

}

void TitleState::Update(float dt) {
    auto& in = InputManager::GetInstance();

    this->timer.Update(dt);

    this->popRequested = in.KeyPress(ESCAPE_KEY);

    if (this->popRequested) return;

    this->quitRequested = in.QuitRequested();

    if (this->quitRequested) return;

    if (this->timer.Get() > 0 && !HasComponent("Text")) {
        auto gameObject = new GameObject();
        auto text = new Text(*gameObject, "assets/font/Call me maybe.ttf", 100, Text::TextStyle::SOLID, "Press Space Bar to Start",  { 255, 0, 0, 1 });

        text->SetFadeOut(1.0f);
        gameObject->AddComponent(text);

        AddObject(gameObject);
        // TODO: center image and make it bigger
        this->timer.SetStart(-1.5f);
    }

    if (in.KeyPress(SPACE_BAR)) {
        auto game = Game::GetInstance();
        auto stageState = new StageState();

        game->Push(stageState);
    }

    UpdateArray(dt);
    PruneArray();
}

void TitleState::Render() {
    RenderArray();
}

void TitleState::Start() {
    LoadAssets();
    StartArray();

    this->started = true;
}

void TitleState::Pause() {

}

void TitleState::Resume() {
    Camera::Reset();
}