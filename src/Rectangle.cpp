#include <Rectangle.h>
#include <Vector.h>
#include <Point.h>
#include <Logger.h>
#include <Util.h>
#include <tuple>

namespace penguin {

    Rectangle::Rectangle() : vector(), width(0), height(0) {}

    Rectangle::Rectangle(Vector v, float w, float h) : vector(v), width(w), height(h) {}

    Rectangle::Rectangle(float x, float y, float w, float h) : vector(x, y), width(w), height(h) {};

    Point Rectangle::Center() const {
        Point dl, ur;

        std::tie(dl, ur) = GetPoints();

        return (dl + ur) / 2;
    }

    float Rectangle::CenterDistance(const Rectangle& R) const {
        auto c1 = this->Center();
        auto c2 = R.Center();

        return Point::Distance(c1, c2);
    }

    bool Rectangle::IsInside(const Point& P) const {
        return (P.x >= this->vector.x && P.x <= this->vector.x + this->width)
            && (P.y >= this->vector.y && P.y <= this->vector.y + this->height);
    } 

    std::tuple<Point, Point> Rectangle::GetPoints() const {
        auto u = static_cast<Point>(this->vector); // down left
        auto x = (u.x + this->width);
        auto y = (u.y + this->height);
        auto v = Point(x, y); // upper right

        return std::make_tuple(v, u);
    }

    // TODO: fix this
    Rectangle Rectangle::operator+ (const Vector& V) {
        auto P = this->vector + V;
        return Rectangle { Vector(P.x, P.y), this->width, this->height };
    }

    // TODO: fix this
    Rectangle Rectangle::operator- (const Vector& V) {
        auto P = this->vector - V;
        return Rectangle { Vector(P.x, P.y), this->width, this->height };
    }

    Rectangle Rectangle::operator* (int value) {
        auto w = this->width * value;
        auto h = this->height * value;

        return Rectangle { this->vector, w, h};
    }   

    Rectangle Rectangle::operator= (const Rectangle& R) {
        return Rectangle { R.vector, R.width, R.height };
    } 

}