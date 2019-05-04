#pragma once

#include <Logger.h>
#include <Util.h>

#include <cmath>

class Point {
    public:

    float x;

    float y;

    Point(float xv = 0.0, float yv = 0.0);

    Point operator+= (const Point&);

    Point operator+ (const Point&) const;

    Point operator-= (const Point&);

    Point operator- (const Point&) const;

    Point operator*= (const float);

    Point operator* (const float) const;

    Point operator/= (const float);

    Point operator/ (const float) const;

    Point operator= (const Point&);

    bool operator==(const Point&);

    bool operator<(const Point&);

    friend std::ostream& operator<<(std::ostream &os, const  Point& n);

    friend std::istream& operator>>(std::istream &is, Point& n);
};