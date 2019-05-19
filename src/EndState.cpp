#include <Util.h>
#include <EndState.h>
#include <Game.h>
#include <GameData.h>
#include <Sprite.h>
#include <Music.h>
#include <Text.h>
#include <InputManager.h>
#include <TitleState.h>

EndState::EndState () {
    auto gameObject = new GameObject();

    if (GameData::playerVictory) {
        auto bg = new Sprite(*gameObject, "assets/img/win.jpg");
        gameObject->AddComponent(bg);

        this->backgroundMusic.Open("assets/audio/endStateWin.ogg");
    } else {
        auto bg = new Sprite(*gameObject, "assets/img/lose.jpg");
        gameObject->AddComponent(bg);

        this->backgroundMusic.Open("assets/audio/endStateLose.ogg");        
    }

    this->backgroundMusic.Play();

    auto msg = "Pressione SPACE BAR para jogar novamente e ESC para sair";
    auto text = new Text(*gameObject, "assets/font/Call me maybe.ttf", 100, Text::TextStyle::SOLID, msg,  { 255, 0, 0, 1 });

    gameObject->AddComponent(text);

    AddObject(gameObject);
}

EndState::~EndState () {}

void EndState::LoadAssets () {
    // TODO: fill?
}

void EndState::Update (float dt) {
    UNUSED(dt);

    auto& in = InputManager::GetInstance();

    this->quitRequested = this->popRequested = in.KeyPress(ESCAPE_KEY);

    if (this->popRequested) return;

    this->quitRequested = in.QuitRequested();

    if (this->quitRequested) return;

    if (in.KeyPress(SPACE_BAR)) {
        this->popRequested = true;
        
        auto game = Game::GetInstance();
        // TODO: isn't already a title state? why push another?
        game->Push(new TitleState());
    }
}

void EndState::Render () {}

void EndState::Start () {}

void EndState::Pause () {}

void EndState::Resume () {}