#include <Camera.h>
#include <Game.h>
#include <Resources.h>
#include <Sprite.h>

Sprite::Sprite(GameObject& go) : Component(go) {
    this->texture = nullptr;
    this->scale = Vec2(1, 1);

    go.angle = 0.0f;
}

Sprite::Sprite(GameObject& go, const std::string &file)  : Component(go) {
    this->texture = nullptr;
    this->scale = Vec2(1, 1);

    go.angle = 0.0f;

    Open(file);
}

Sprite::~Sprite() {}

void Sprite::Open (const std::string &file) {
    this->texture = Resources::GetImage(file);
    
    std::tie(this->width, this->height) = Resources::QueryImage(this->texture);

    SetClip(0, 0, this->width, this->height);
    
    this->associated.box.width = static_cast<float>(GetWidth());
    this->associated.box.height = static_cast<float>(GetHeight());
}

void Sprite::SetClip (int x, int y, int w, int h) {
    this->clipRect = {x, y, w, h};
}

void Sprite::SetScale (float x, float y) {
    x = EQUAL(x, 0) ? this->scale.x : x;
    y = EQUAL(y, 0) ? this->scale.y : y;

    this->scale = Vec2(x, y);

    SetClip(0, 0, this->width, this->height);

    this->associated.box.width = static_cast<float>(GetWidth());
    this->associated.box.height = static_cast<float>(GetHeight());
}

Vec2 Sprite::GetScale() {
    return this->scale;
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

    SDL_Rect dstRect{ 
        x, 
        y, 
        static_cast<int>(srcRect.w * this->scale.x),
        static_cast<int>(srcRect.h * this->scale.y)
    };

    SDL_RenderCopyEx(g->GetRenderer(), this->texture, &srcRect, &dstRect, (this->associated.angle * 180) / PI, nullptr, SDL_FLIP_NONE);
}

bool Sprite::Is (std::string type) {
    return (type == "Sprite");
}

int Sprite::GetWidth() {
    return this->width * this->scale.x;
}

int Sprite::GetHeight() {
    return this->height * this->scale.y;
}

bool Sprite::IsOpen() {
    return (this->texture != nullptr);
}