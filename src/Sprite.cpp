#include <Camera.h>
#include <Game.h>
#include <Resources.h>
#include <Sprite.h>

Sprite::Sprite(GameObject& go) : Component(go) {
    this->texture = nullptr;
}

Sprite::Sprite(GameObject& go, const std::string &file)  : Component(go) {
    this->texture = nullptr;

    Open(file);
}

Sprite::~Sprite() {}

void Sprite::Open (const std::string &file) {
    this->texture = Resources::GetImage(file);
    
    std::tie(this->width, this->height) = Resources::QueryImage(this->texture);

    SetClip(0, 0, this->width, this->height);
    
    this->associated.box.width = static_cast<float>(this->width);
    this->associated.box.height = static_cast<float>(this->height);
}

void Sprite::SetClip (int x, int y, int w, int h) {
    this->clipRect = {x, y, w, h};
}

void Sprite::Update (float dt) {
    UNUSED(dt);
}

void Sprite::Render () {
    auto x = static_cast<int>(this->associated.box.vector.x - Camera::pos.x);
    auto y = static_cast<int>(this->associated.box.vector.y - Camera::pos.y);    

    Render(x, y);
}

void Sprite::Render (float _x, float _y) {
    auto x = static_cast<int>(_x);
    auto y = static_cast<int>(_y);    

    Render(x, y);
}

void Sprite::Render (int x, int y) {
    auto g = Game::GetInstance();
    auto srcRect = this->clipRect;

    SDL_Rect dstRect{ x, y, this->clipRect.w, this->clipRect.h };

    SDL_RenderCopy(g->GetRenderer(), this->texture, &srcRect, &dstRect);
}

bool Sprite::Is (std::string type) {
    return (type == "Sprite");
}

int Sprite::GetWidth() {
    return this->width;
}

int Sprite::GetHeight() {
    return this->height;
}

bool Sprite::IsOpen() {
    return (this->texture != nullptr);
}