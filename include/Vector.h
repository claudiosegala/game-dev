#pragma once

#include <Point.h>

// TODO: check corretude
// TODO: check if I should add const operators

namespace penguin {

    class Vector : public Point {
        public:

        Vector(float xv = 0, float yv = 0);

        Vector(const Point&, const Point&);

        // Angle With Vector (0, 0)
        float Angle() const;

        // Angle Between This Vector And Another
        float Angle(const Vector&) const;
        
        // Cross Product
        Vector operator* (const Vector&);
        
        // Dot Product
        float operator^ (const Vector&) const;
                
    };

}