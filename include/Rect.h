#pragma once

#include <Logger.h>
#include <Point.h>
#include <Util.h>
#include <Vec2.h>

#include <tuple>

class Rect {
    public:

    Vec2 vector;

    float width;

    float height;

    Rect();

    Rect(Vec2, float, float);

    Rect(float, float, float, float);

    Point Center() const;

    float CenterDistance(const Rect&) const;

    void SetCenter(const Point&);

    bool IsInside(const Point&) const;

    std::tuple<Point, Point> GetPoints() const;

    Rect operator+ (const Vec2&) const;

    void operator+= (const Vec2&);

    Rect operator- (const Vec2&) const;

    void operator-= (const Vec2&);

    Rect operator* (float) const;

    void operator*= (float);

    Rect operator= (const Rect&);

    friend std::ostream& operator<<(std::ostream &os, const  Rect& n);

    friend std::istream& operator>>(std::istream &is, Rect& n);
};