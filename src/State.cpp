#include <State.h>
#include <Logger.h>

namespace penguin {

    State::State () {
        this->quitRequested = false;
        
        LoadAssets();
        
        this->music.Play();
    }

    State::~State () {
        this->music.Stop();

        // TODO: verify if this is enough, since the unique_ptr
        this->objects.clear();
    }

    void State::LoadAssets () {
        this->bg.Open("assets/img/ocean.jpg");
        this->music.Open("assets/audio/stageState.ogg");
    }

    void State::Update (float dt) {
        Logger::Info("Updating...");

        auto quit = SDL_QuitRequested();

        if (quit) {
            this->quitRequested = quit;
            return;
        }

        Input();

        for (auto &obj : this->objects) {
            obj->Update(dt);
        }

        Clean();
    }

    void State::Render () {
        this->bg.Render(0, 0);

        for (auto &obj : this->objects) {
            obj->Render();
        }
    }

    bool State::QuitRequested () {
        return this->quitRequested;
    }

    void State::Input () {
        // O corpo dessa função está disponível no Moodle. Podem ser
        // necessários alguns ajustes nele para se adequar aos nomes de variáveis ou funções do seu código. Além disso, você pode tirar a chamada à SDL_QuitRequested em Update(), já que Input cuida de eventos de SDL_QUIT para nós.
        // ATENÇÃO: O dano só é aplicado se o GameObject tiver um componente do tipo face, caso contrário, continue procurando.
    }

    void State::Clean () {
        auto it = std::remove_if(this->objects.begin(), this->objects.end(), f = [&] (GameObject* o) { 
            return o.IsDead();
        });

        this->objects.erase(it, this->objects.end());
    }

    void State::AddObjects (int mouseX, int mouseY) {
        // TODO: fix this
        Point corner(0, 0), pos(mouseX, mouseY);
        Reactangle rect(corner, pos);
        GameObject obj(rect);
        Sprite face(obj, "assets/img/penguinface.png");

        obj.AddComponent();

        // TODO: continue
    }

}
