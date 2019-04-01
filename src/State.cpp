#include <State.h>
#include <Rectangle.h>
#include <Vector.h>
#include <Util.h>
#include <Logger.h>

namespace penguin {

    State::State () {
        this->quitRequested = false;
        this->bg.Open("assets/img/ocean.jpg");
        this->music.Open("assets/audio/stageState.ogg");
        this->music.Play();

        // TODO: come back when finishing the AddObject function
    }

    State::~State () {
        this->music.Stop();
        this->objects.clear();
    }

    void State::LoadAssets () {
        // For now, nothing
    }

    void State::Update (float dt) {
        Logger::Info("Updating...");

        Input();

        this->quitRequested |= SDL_QuitRequested();

        if (this->quitRequested) {
            return;
        }

        for (auto &obj : this->objects) {
            obj->Update(dt);
        }

        Clean();
    }

    void State::Render () {
        // TODO: discover if this should be removed
        this->bg.Render(0, 0);

        for (auto &obj : this->objects) {
            obj->Render();
        }
    }

    bool State::QuitRequested () {
        return this->quitRequested;
    }

    void State::Input () {
        SDL_Event event;
        int mouseX, mouseY;

        SDL_GetMouseState(&mouseX, &mouseY);

        while (SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                this->quitRequested = true;
            }
            
            if(event.type == SDL_MOUSEBUTTONDOWN) {
                // Get the newer object (the one that is on top of the vector) and deal the damage
                for(int i = this->objects.size() - 1; i >= 0; --i) {
                    auto &obj = this->objects[i].get();

                    if(obj->box.Contains( {(float)mouseX, (float)mouseY } ) ) {
                        auto &component = obj.GetComponent("Face"); // avoid using get
                        
                        if (component != nullptr) {
                            auto face = static_cast<Face*>(obj);
                            face->Damage(std::rand() % 10 + 10);
                            break;
                        }
                    }
                }
            }

            if( event.type == SDL_KEYDOWN ) {
                if(event.key.keysym.sym == SDLK_ESCAPE) {
                    this->quitRequested = true;
                } else {
                    Vector pos = Vector(200, 0).Rotate(-PI + PI*(rand() % 1001)/500.0) + Vector(mouseX, mouseY);
                    AddObject((int)pos.x, (int)pos.y);
                }
            }
        }
    }

    void State::Clean () {
        auto it = std::remove_if(this->objects.begin(), this->objects.end(), f = [&] (GameObject* o) { 
            return o.IsDead();
        });

        this->objects.erase(it, this->objects.end());
    }

    // TODO: verify
    void State::AddObjects (int mouseX, int mouseY) {
        GameObject obj(Point(mouseX, mouseY), 0, 0);
        Sound sound(obj, "assets/audio/boom.wav");
        Sprite sprite(obj, "assets/img/penguinface.png");

        obj.box.vector -= obj.box.Center();
        obj.AddComponent(sound);
        obj.AddComponent(sprite);

        Face face(obj);

        this->objects.emplace_back(face);

        // TODO: continue
    }

}
