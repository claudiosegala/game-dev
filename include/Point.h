#pragma once

#include <Logger.h>
#include <Util.h>

#include <cmath>

class Point {
    public:

    float x;

    float y;

    Point(float xv = 0.0, float yv = 0.0);

    static float Distance(const Point&, const Point&);

    Point operator+= (const Point&);

    Point operator+ (const Point&);

    Point operator-= (const Point&);

    Point operator- (const Point&);

    Point operator* (float);

    Point operator/ (float);

    Point operator= (const Point&);

    bool operator==(const Point&);

    bool operator<(const Point&);
};