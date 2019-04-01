#include <State.h>
#include <Sound.h>
#include <Sprite.h>
#include <Music.h>
#include <Rectangle.h>
#include <GameObject.h>
#include <Vector.h>
#include <Face.h>
#include <Util.h>
#include <Logger.h>
#include <vector>
#include <algorithm>
#include <string>
#include <memory>

namespace penguin {

    State::State () {
        auto obj = new GameObject();
        Sprite background(*obj, "assets/img/ocean.jpg");

        obj->AddComponent(&background);

        this->quitRequested = false;
        this->music.Open("assets/audio/stageState.ogg");
        this->music.Play();
        this->objects.emplace_back(obj);
    }

    State::~State () {
        this->music.Stop();
        this->objects.clear();
    }

    void State::LoadAssets () {
        // For now, nothing
    }

    void State::Update (float dt) {
        Input();

        this->quitRequested |= SDL_QuitRequested();

        if (this->quitRequested) {
            Logger::Info("Quitting");
            return;
        }

        Logger::Info("Updating");
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

    void State::Input () {
        Logger::Info("Reading Input");

        SDL_Event event;
        int mouseX, mouseY;

        SDL_GetMouseState(&mouseX, &mouseY);

        while (SDL_PollEvent(&event)) {
            Logger::Info("Got a event");

            if(event.type == SDL_QUIT) {
                this->quitRequested = true;
            }
            
            if(event.type == SDL_MOUSEBUTTONDOWN) {
                Logger::Info("Someone clicked");
                // Get the newer object (the one that is on top of the vector) and deal the damage
                for(auto i = this->objects.size() - 1; i >= 0; --i) {
                    auto obj = this->objects[i].get();

                    if(obj->box.IsInside( {(float)mouseX, (float)mouseY } ) ) {
                        auto component = obj->GetComponent("Face"); // avoid using get
                        
                        if (component != nullptr) {
                            auto face = static_cast<Face*>(component);
                            face->Damage(std::rand() % 10 + 10);
                            break;
                        }
                    }
                }
            }

            if( event.type == SDL_KEYDOWN ) {
                Logger::Info("Someone typed");
                if(event.key.keysym.sym == SDLK_ESCAPE) {
                    this->quitRequested = true;
                } else {
                    Vector pos = Vector(200, 0);
                    
                    pos.Rotate(PI*(rand()/rand()));
                    pos += Vector(mouseX, mouseY);

                    AddObject((int)pos.x, (int)pos.y);
                }
            }
        }
    }

    void State::Prune () {
        Logger::Info("Prunning");
        auto it = std::remove_if(this->objects.begin(), this->objects.end(), [&] (std::unique_ptr<GameObject>& o) { 
            return o->IsDead();
        });

        this->objects.erase(it, this->objects.end());
    }

    // TODO: verify
    void State::AddObject (int mouseX, int mouseY) {
        auto obj = new GameObject();

        obj->box = Rectangle(Vector((float)mouseX, (float)mouseY), 0.0, 0.0);
        obj->box.vector -= obj->box.Center();

        Sound sound(*obj, "assets/audio/boom.wav");
        Sprite sprite(*obj, "assets/img/penguinface.png");
        Face face(*obj);

        obj->AddComponent(&sound);
        obj->AddComponent(&sprite);
        obj->AddComponent(&face);

        this->objects.emplace_back(obj);
    }

}
