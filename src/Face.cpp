#include <Face.h>
#include <Component.h>
#include <GameObject.h>
#include <Sound.h>
#include <Util.h>
#include <Logger.h>

namespace penguin {

    Face::Face(GameObject& obj) : Component(obj) {
        this->hitpoints = 30; // 30HP

        Logger::Info("Created a face");
    }

    void Face::Damage(int damage) {
        Logger::Info("Face took " + std::to_string(damage) + " damage");

        this->hitpoints -= damage;        

        if (this->hitpoints <= 0) {
            Logger::Info("Face died");
            auto component = this->associated.GetComponent("Sound");

            if (component != nullptr) {
                auto sound = static_cast<Sound*>(component);
                sound->Play();
            } else {
                Logger::Error("Could not find the sound in Face");
            }

            this->associated.RequestDelete();            
        }
    }

    void Face::Update (float dt) {
        UNUSED(dt);
    }

    void Face::Render() {}

    bool Face::Is(std::string type) {
        return (type == "Face");
    } 

}