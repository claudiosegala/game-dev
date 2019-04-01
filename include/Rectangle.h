#pragma once

#include <Vector.h>
#include <Point.h>
#include <tuple>

// TODO: check corretude
// TODO: check if I should add const operators

namespace penguin {

    class Rectangle {
        public:

        Vector vector;

        int width;

        int height;

        Rectangle();

        Rectangle(Vector, int, int);

        Point Center() const;

        float CenterDistance(const Rectangle&) const;

        bool IsInside(const Point&) const;

        std::tuple<Point, Point> GetPoints() const;

        Rectangle operator+ (const Vector&);

        Rectangle operator- (const Vector&);

        Rectangle operator* (int);

        Rectangle operator= (const Rectangle&);
    };

}