#include <Rectangle.h>
#include <Vector.h>
#include <Point.h>
#include <tuple>

namespace penguin {

    Rectangle::Rectangle() : vector(), width(0), height(0) {}

    Rectangle::Rectangle(Vector v, int w, int h) : vector(v), width(w), height(h) {}

    Point Rectangle::Center() const {
        Point dl, ur;

        std::tie(dl, ur) = GetPoints();

        return (dl + ur) / 2;
    }

    double Rectangle::CenterDistance(const Rectangle& R) const {
        auto c1 = this->Center();
        auto c2 = R.Center();

        return c1.Distance(c2);
    }

    bool Rectangle::IsInside(const Point& P) const {
        Point dl, ur;

        std::tie(dl, ur) = GetPoints();

        return (P.x >= dl.x && P.x < ur.x)
            && (P.y >= dl.y && P.y < ur.y);
    } 

    std::tuple<Point, Point> Rectangle::GetPoints() const {
        auto u = static_cast<Point>(this->vector); // down left
        auto x = (u.x + this->width);
        auto y = (u.y + this->height);
        auto v = Point(x, y); // upper right

        return std::make_tuple(v, u);
    }

    Rectangle Rectangle::operator+ (const Vector& V) {
        auto P = static_cast<Point>(this->vector + V);
        return Rectangle { P, this->width, this->height };
    }

    Rectangle Rectangle::operator- (const Vector& V) {
        auto P = static_cast<Point>(this->vector - V);
        return Rectangle { P, this->width, this->height };
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