#pragma once

#include <Component.h>
#include <GameObject.h>
#include <Logger.h>
#include <SDL_Include.h>
#include <Util.h>

#include <string>
#include <iostream>

class Sprite : public Component {
    public:

    Sprite(GameObject&);

    Sprite(GameObject&, const std::string&);

    ~Sprite();

    void Open (const std::string&);

    void SetClip (int, int, int, int);

    void SetScaleX (float, float);

    Vec2 GetScale();

    void Update(float);

    void Render();

    void Render(int, int);

    void Render(float, float);

    bool Is(std::string);

    int GetWidth();

    int GetHeight();

    bool IsOpen();

    private:

    int width;

    int height;

    Vec2 scale;

    SDL_Texture* texture;

    SDL_Rect clipRect;

};