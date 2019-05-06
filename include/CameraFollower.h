#pragma once

#include <Component.h>
#include <GameObject.h>
#include <Logger.h>
#include <Util.h>

#include <string>

class CameraFollower : public Component {
    public:
    
    CameraFollower (GameObject&);

    void Update(float);

    void Render();

    void NotifyCollision(GameObject&);
    
    bool Is(std::string);
};