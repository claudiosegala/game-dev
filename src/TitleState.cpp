#include <TitleState.h>
#include <GameObject.h>
#include <Sprite.h>
#include <Game.h>
#include <StageState.h>
#include <InputManager.h>

TitleState::TitleState() : State() {
    auto gameObject = new GameObject();

    auto image = new Sprite(*gameObject, "assets/img/ocean.jpg");

    gameObject->AddComponent(image);

    AddObject(gameObject);
}
        
TitleState::~TitleState() {

}

void TitleState::LoadAssets() {

}

void TitleState::Update(float dt) {
    UNUSED(dt);

    auto& in = InputManager::GetInstance();

    this->popRequested = in.IsKeyDown(ESCAPE_KEY);

    if (this->popRequested) return;

    this->quitRequested = in.QuitRequested();

    if (this->quitRequested) return;

    if (in.KeyPress(SPACE_BAR)) {
        auto game = Game::GetInstance();
        auto stageState = new StageState();

        game->Push(stageState);
    }
}

void TitleState::Render() {

}

void TitleState::Start() {

}

void TitleState::Pause() {

}

void TitleState::Resume() {

}