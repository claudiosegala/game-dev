#pragma once

#include <Util.h>
#include <GameObject.h>
#include <Component.h>
#include <Vec2.h>

class PenguinBody : public Component{
    public:

        static int const life;

        static float const spinPace;

        static float const pace;

        static float const maxSpeed;

        static PenguinBody* player;

        PenguinBody (GameObject&);

        ~PenguinBody();

        void Start();

        void Update(float);

        void Render();
        
        void NotifyCollision(GameObject&);

        bool Is(std::string);

        Vec2 GetPosition();

    private:

        int hp;

        float angle;
        
        float linearSpeed;
        
        Vec2 speed;

        std::weak_ptr<GameObject> pcannon;
};