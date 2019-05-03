#pragma once

#include <Component.h>
#include <GameObject.h>
#include <Logger.h>
#include <SDL_Include.h>
#include <Util.h>

class Sound : public Component {
    public:

    Sound(GameObject&);

    Sound(GameObject&, std::string);

    ~Sound();

    void Play(int times = 1);

    void Stop();

    void Open(std::string);

    bool IsOpen();

    void Update(float);

    void Render();

    bool Is(std::string);
    
    private:

    int channel;

    Mix_Chunk* chunk;

};