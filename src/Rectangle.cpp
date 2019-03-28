#include <Rectangle.h>
#include <Vector.h>
#include <Point.h>

namespace penguin {

    Rectangle::Rectangle(Point u, Point v) : dl(u), ur(v) {}

    Point Rectangle::Center() const {
        auto x = (this->ur.x + this->dl.x) / 2;
        auto y = (this->ur.y + this->dl.y) / 2;

        return Point { x, y };
    }

    double Rectangle::CenterDistance(const Rectangle& R) {
        auto c1 = this->Center();
        auto c2 = R.Center();

        return c1.Distance(c2);
    }

    bool Rectangle::IsInside(const Point& P) {
        return (P.x >= this->dl.x && P.x < this->ur.x)
            && (P.y >= this->dl.y && P.y < this->ur.y);
    } 

    Rectangle Rectangle::operator+ (const Vector& V) {
        return Rectangle { this->dl + V, this->ur + V };
    }

    Rectangle Rectangle::operator- (const Vector& V) {
        return Rectangle { this->dl - V, this->ur - V };
    }

    Rectangle Rectangle::operator* (int value) {
        auto w = this->ur.x - this->dl.x;
        auto h = this->ur.y - this->dl.y;

        w *= value;
        h *= value;

        auto P = Point(this->dl.x + w, this->dl.y + h);

        return Rectangle { this->dl, P };
    }   

    Rectangle Rectangle::operator= (const Rectangle& R) {
        return Rectangle { R.dl, R.ur };
    } 

}