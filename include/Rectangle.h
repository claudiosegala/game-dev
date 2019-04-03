#pragma once

#include <Vector.h>
#include <Point.h>
#include <tuple>

namespace penguin {

    class Rectangle {
        public:

        Vector vector;

        float width;

        float height;

        Rectangle();

        Rectangle(Vector, float, float);

        Rectangle(float, float, float, float);

        Point Center() const;

        float CenterDistance(const Rectangle&) const;

        bool IsInside(const Point&) const;

        std::tuple<Point, Point> GetPoints() const;

        Rectangle operator+ (const Vector&) const;

        void operator+= (const Vector&);

        Rectangle operator- (const Vector&) const;

        void operator-= (const Vector&);

        Rectangle operator* (float) const;

        void operator*= (float);

        Rectangle operator= (const Rectangle&);
    };

}