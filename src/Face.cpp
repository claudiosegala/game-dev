// TODO: delete
#include <Camera.h>
#include <Component.h>
#include <Face.h>
#include <InputManager.h>
#include <Sound.h>

Face::Face(GameObject& go) : Component(go) {
    this->hitpoints = 30; // 30HP

    Logger::Info("Created a face");
}

void Face::Damage(int damage) {
    Logger::Info("Face took " + std::to_string(damage) + " damage");

    this->hitpoints -= damage;        

    if (this->hitpoints < 1) {
        Logger::Info("Face died");
        auto component = this->associated.GetComponent("Sound");

        if (component != nullptr) {
            auto sound = std::static_pointer_cast<Sound>(component);
            sound->Play(1);
        } else {
            Logger::Error("Could not find the sound in Face");
        }

        this->associated.RequestDelete();            
    }
}

void Face::Update (float dt) {
    UNUSED(dt);
    auto& in = InputManager::GetInstance();

    if (!in.MousePress(LEFT_MOUSE_BUTTON)) {
        return;
    }

    auto x = (float) in.GetMouseX() + Camera::pos.x;
    auto y = (float) in.GetMouseY() + Camera::pos.y;

    if (!this->associated.box.IsInside({ x, y })) {
         return;   
    }

    Logger::Info("Face damaged");
    Damage(std::rand() % 10 + 10);
}

void Face::Render() {}

bool Face::Is(std::string type) {
    return (type == "Face");
}