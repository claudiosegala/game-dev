#include <Text.h>
#include <Component.h>
#include <Game.h>
#include <Camera.h>
#include <Resources.h>

Text::Text (GameObject& associated, std::string file, int size, TextStyle style, std::string text, SDL_Color color) 
: Component(associated), text(text), style(style), fontFile(file), fontSize(size), color(color) {
    this->font = Resources::GetText(GetName());
    this->texture = nullptr;

    RemakeTexture();
}

Text::~Text() {
    if (this->texture != nullptr) {
        SDL_DestroyTexture(this->texture);
    }
}

std::string Text::GetName () {
    return std::string() + "pt-" + this->fontFile;
}

void Text::Update(float dt) {
    UNUSED(dt);
}

// TODO: verify if this is correct
void Text::Render() {
    if (this->texture == nullptr) return;

    auto game = Game::GetInstance();

    SDL_Rect srcRect { 
        static_cast<int>(0), 
        static_cast<int>(0), 
        static_cast<int>(this->associated.box.width), 
        static_cast<int>(this->associated.box.height)
    };

    SDL_Rect dstRect { 
        static_cast<int>(this->associated.box.vector.x - Camera::pos.x),
        static_cast<int>(this->associated.box.vector.x - Camera::pos.y),
        static_cast<int>(this->associated.box.width),
        static_cast<int>(this->associated.box.height)
    };

    SDL_RenderCopyEx(game->GetRenderer(), this->texture, &srcRect, &dstRect, (this->associated.angle * 180) / PI, nullptr, SDL_FLIP_NONE);
}

bool Text::Is(std::string type) {
    return (type == "Text");
}

void Text::SetText(std::string text) {
    this->text = text;

    Text::RemakeTexture();
}

void Text::SetColor(SDL_Color color) {
    this->color = color;
    RemakeTexture();
}

void Text::SetStyle(TextStyle style) {
    this->style = style;
    RemakeTexture();
}

void Text::SetFontFile(std::string file) {
    this->fontFile = file;
    RemakeTexture();
}

void Text::SetFontSize(int size) {
    this->fontSize = size;
    RemakeTexture();
}

void Text::RemakeTexture() {
    if (this->texture != nullptr) {
        SDL_DestroyTexture(this->texture);
    }

    this->font = Resources::GetText(GetName());

    SDL_Surface *aux;

    switch (this->style) {
        case TextStyle::SOLID:
            aux = TTF_RenderText_Solid(this->font.get(), this->text.c_str(), this->color);
            break;
        case TextStyle::SHADED:
            aux = TTF_RenderText_Shaded(this->font.get(), this->text.c_str(), this->color, SDL_Color { 0, 0, 0, 0 });
            break;
        case TextStyle::BLENDED:
            aux = TTF_RenderText_Blended(this->font.get(), this->text.c_str(), this->color);
            break;
    }

    auto game = Game::GetInstance();
    auto renderer = game->GetRenderer();

    this->texture = SDL_CreateTextureFromSurface(renderer, aux);

    SDL_FreeSurface(aux);
}