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
        auto bg  = new Sprite(*obj, "assets/img/ocean.jpg");

        obj->AddComponent(bg);

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
        SDL_Event event;
        int mouseX, mouseY;

        SDL_GetMouseState(&mouseX, &mouseY);

        while (SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                this->quitRequested = true;
            }
            
            if(event.type == SDL_MOUSEBUTTONDOWN) {
                Logger::Info("Someone clicked");
                // Get the newer object (the one that is on top of the vector) and deal the damage
                for(int i = (int)this->objects.size() - 1; i >= 0; --i) {
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
                    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX); // 0.0 to 1.0
                    float angle = TAO * r;
                    Vector pos(200, 0);
                    Vector center(mouseX, mouseY);

                    pos.Rotate(angle);
                    pos += center;

                    AddObject((int)pos.x, (int)pos.y);
                }
            }
        }
    }

    void State::Prune () {
        // Logger::Info("Prunning");
        auto it = std::remove_if(this->objects.begin(), this->objects.end(), [&] (std::unique_ptr<GameObject>& o) { 
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
        obj->box.vector = Point(mouseX, mouseY);
        obj->box.vector -= Vector(obj->box.width/2, obj->box.height/2);

        // Insert
        this->objects.emplace_back(obj);
    }

}
