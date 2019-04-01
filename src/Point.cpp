#include <Point.h>
#include <Logger.h>
#include <cmath>

namespace penguin {

    #define EPS 0.00001

    Point::Point() : x(0.0), y(0.0) {}

    Point::Point(float xv, float yv) : x(xv), y(yv) {}

    float Point::Length() const {
        return hypot(this->x, this->y);
    }

    float Point::Distance(const Point& P) const {
        return hypot(P.x - this->x, P.y - this->y);
    }

    float Point::Distance(const Point& P, const Point& Q) {
        return hypot(P.x - Q.x, P.y - Q.y);
    }

    void Point::Rotate(float angle) {
        auto xv = cos(angle) * this->x - sin(angle) * this->y;
        auto yv = sin(angle) * this->x + cos(angle) * this->y;

        this->x = xv;
        this->y = yv;
    }

    void Point::Rotate(float angle, const Point& C) {
        (*this) -= C;
        (*this).Rotate(angle);
        (*this) += C;
    }

    void Point::Normalize () {
        auto len = this->Length();
        
        this->x /= len;
        this-> y /= len;
    }

    bool Point::Equal (float u, float v) const {
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

    Point Point::operator* (float value) {
        return Point { this->x * value, this->y * value };
    }

    Point Point::operator/ (int value) {
        return Point { this->x / value, this->y / value };
    }

    Point Point::operator/ (float value) {
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