#include <TitleState.h>
#include <GameObject.h>
#include <Rect.h>
#include <Sprite.h>
#include <Camera.h>
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
    UNUSED(dt);

    auto& in = InputManager::GetInstance();

    this->popRequested = in.KeyPress(ESCAPE_KEY);

    if (this->popRequested) return;

    this->quitRequested = in.QuitRequested();

    if (this->quitRequested) return;

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