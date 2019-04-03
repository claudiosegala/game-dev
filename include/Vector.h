#pragma once

#include <Point.h>
#include <iostream>

namespace penguin {

    class Vector : public Point {
        public:

        Vector(float xv = 0, float yv = 0);

        ///> Find magnitude of vector
        float GetLength() const;

        ///> Find angle with point (0, 0)
        float GetAngle() const;

        ///> Find angle between this vector and another
        float GetAngle(const Vector&) const;

        ///> Transform vector, on unit
        void Unit();

        ///> Get unit vector
        Vector GetUnit() const;

        ///> Transform vector, rotating
        void Rotate(float);

        ///> Get rotated vector
        Vector GetRotate(float) const;
        
        ///> Cross product
        Vector operator* (const Vector&);
        
        ///> Dot product
        float operator^ (const Vector&) const;

        Vector operator* (const float) const;

        void operator*= (const float);

        Vector operator/ (const float) const;

        void operator/= (const float);

        Vector operator+(const Vector&) const;

        Vector operator+= (const Vector&);

        Vector operator-(const Vector&) const;

        Vector operator-= (const Vector&);

        Vector operator= (const Point&);

        Vector operator= (const Vector&);

        friend std::ostream& operator<<(std::ostream &os, const  Vector& n);

        friend std::istream& operator>>(std::istream &is, Vector& n);
                
    };

}