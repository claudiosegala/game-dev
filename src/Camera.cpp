#include <Camera.h>
#include <Game.h>
#include <InputManager.h>
#include <Util.h>

Vec2 Camera::pos;

Vec2 Camera::speed;

GameObject* Camera::focus;

void Camera::Follow(GameObject* newFocus) {
    // TODO: discover if I should delete
    // if (Camera::focus != nullptr) {
    //     delete Camera::focus;
    // }

    Camera::focus = newFocus;
}

void Camera::Unfollow() {
    Camera::Follow(nullptr);
}

void Camera::Update(float dt) {
    if (focus != nullptr) {
        Camera::pos = Camera::focus->box.Center();
        return;
    }

    auto k = (float) 1500.0; // to adjust speed

    Camera::speed = Camera::GetMovement();
    Camera::speed *= dt * k;
    Camera::pos += Camera::speed;
}

Vec2 Camera::GetMovement() {
    auto& in  = InputManager::GetInstance();
    
    auto r = in.IsKeyDown(RIGHT_ARROW_KEY);
    auto l = in.IsKeyDown(LEFT_ARROW_KEY);
    auto u = in.IsKeyDown(UP_ARROW_KEY);
    auto d = in.IsKeyDown(DOWN_ARROW_KEY);

    auto x = r ? 1 : (l ? -1 : 0);
    auto y = d ? 1 : (u ? -1 : 0);

    return Vec2(x, y);
}
