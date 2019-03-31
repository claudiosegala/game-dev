#include "Face.h"
#include "Component.h"
#include "GameObject.h"
#include "Sound.h"

namespace penguin {

    Face::Face(GameObject& obj) : Component(obj) {
        this->hitpoints = 30; // 30HP
    }

    void Face::Damage(int damage) {
        this->hitpoints -= damage;

        if (this->hitpoints <= 0) {
            auto associatedSound = this->associated.GetComponent("Sound");

            this->associated.RequestDelete();

            if (associatedSound != nullptr) {
                auto sound = static_cast<Sound*>(associatedSound);

                sound->Play();
            }
        }
    }

    void Face::Update(float) {}

    void Face::Render() {}

    bool Face::Is(std::string type) {
        return (type == "Face");
    } 

}