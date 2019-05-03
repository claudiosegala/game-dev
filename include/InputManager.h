#pragma once

#include <Logger.h>
#include <SDL_Include.h>
#include <Util.h>

#include <unordered_map>
#include <tuple>

class InputManager {
    public:

    static InputManager& GetInstance();

    void Update();

    void Setup();

    void GetMouse();

    void TreatEvent(SDL_Event& event);

    bool KeyPress(int);

    bool KeyRelease(int);

    bool IsKeyDown(int);

    bool MousePress(int);

    bool MouseRelease(int);

    bool IsMouseDown(int);

    int GetMouseX();

    int GetMouseY();

    bool QuitRequested ();

    private:

    InputManager();

    ~InputManager();

    bool mouseState[6];

    int mouseUpdate[6];

    std::unordered_map<int, bool> keyState;

    std::unordered_map<int, int> keyUpdate;

    bool quitRequested;

    int updateCounter;

    int mouseX;

    int mouseY;

};