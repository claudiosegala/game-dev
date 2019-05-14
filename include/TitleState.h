#pragma once

#include <Util.h>
#include <State.h>

class TitleState : public State {
    public:

        TitleState();
        
        ~TitleState();
        
        void LoadAssets();
        
        void Update(float);
        
        void Render();
        
        void Start();
        
        void Pause();
        
        void Resume();
};