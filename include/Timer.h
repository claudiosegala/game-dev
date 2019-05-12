#pragma once

#include <Util.h>

class Timer {
    public:

        Timer();

        void Update(float);

        void Restart();

        float Get();

    private:

        float time;
};