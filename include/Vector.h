#pragma once

#include <Point.h>

// TODO: check corretude
// TODO: check if I should add const operators

namespace penguin {

    class Vector : public Point {
        public:

        Vector(double xv = 0, double yv = 0);

        Vector(const Point&, const Point&);

        // Angle With Vector (0, 0)
        double Angle() const;

        // Angle Between This Vector And Another
        double Angle(const Vector&) const;
        
        // Cross Product
        Vector operator* (const Vector&);
        
        // Dot Product
        double operator^ (const Vector&) const;
                
    };

}