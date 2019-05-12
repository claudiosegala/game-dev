#include <Timer.h>

Timer::Timer() {
    this->time = 0.0f;
}

void Timer::Update (float dt) {
    this->time += dt;
}

void Timer::Restart () {
    this->time = 0.0f;
}

float Timer::Get() {
    return this->time;
}