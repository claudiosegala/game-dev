#pragma once

#include <Vector.h>
#include <Point.h>

namespace penguin {

    class Rectangle {
        public:

        // Down Left
        Point dl;

        // Up Right
        Point ur;

        Rectangle(Point u, Point v);

        Point Center() const;

        double CenterDistance(const Rectangle&);

        bool IsInside(const Point&); 

        Rectangle operator+ (const Vector&);

        Rectangle operator- (const Vector&);

        Rectangle operator* (int);

        Rectangle operator= (const Rectangle&);
    };

}