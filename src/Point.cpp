#include <cmath>
#include <Point.h>

namespace penguin {

    #define EPS 0.00001

    Point::Point() : x(0.0), y(0.0) {}

    Point::Point(double xv, double yv) : x(xv), y(yv) {}

    double Point::Length() const {
        return hypot(this->x, this->y);
    }

    double Point::Distance(const Point& P) const {
        return hypot(P.x - this->x, P.y - this->y);
    }

    double Point::Distance(const Point& P, const Point& Q) {
        return hypot(P.x - Q.x, P.y - Q.y);
    }

    void Point::Rotate(double angle) {
        auto xv = cos(angle) * this->x - sin(angle) * this->y;
        auto yv = sin(angle) * this->x + cos(angle) * this->y;

        this->x = xv;
        this->y = yv;
    }

    void Point::Rotate(double angle, const Point& C) {
        (*this) -= C;
        (*this).Rotate(angle);
        (*this) += C;
    }

    void Point::Normalize () {
        auto len = this->Length();
        
        this->x /= len;
        this-> y /= len;
    }

    bool Point::Equal (double u, double v) const {
        return fabs(u - v) < EPS;
    }

    Point Point::operator+= (const Point& P) {
        return Point { this->x + P.x, this->y + P.y }; 
    }

    Point Point::operator+ (const Point& P) {
        return Point { this->x + P.x, this->y + P.y }; 
    }

    Point Point::operator-= (const Point& P) {
        return Point { this->x - P.x, this->y - P.y }; 
    }

    Point Point::operator- (const Point& P) {
        return Point { this->x - P.x, this->y - P.y }; 
    }

    Point Point::operator* (int value) {
        return Point { this->x * value, this->y * value };
    }

    Point Point::operator* (double value) {
        return Point { this->x * value, this->y * value };
    }

    Point Point::operator/ (int value) {
        return Point { this->x / value, this->y / value };
    }

    Point Point::operator/ (double value) {
        return Point { this->x / value, this->y / value };
    }

    Point Point::operator= (const Point& V) {
        return Point { V.x, V.y };
    }

    bool Point::operator==(const Point& P) {
        return Equal(this->x, P.x) && Equal(this->y, P.y);
    }

    bool Point::operator<(const Point& P) {
        return Equal(this->x, P.x) ? this->y < P.y : this->x < P.x;
    }

}