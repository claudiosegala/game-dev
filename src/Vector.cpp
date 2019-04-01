#include <Vector.h>
#include <Point.h>
#include <Logger.h>
#include <Util.h>
#include <cmath>

namespace penguin {

    Vector::Vector(float xv, float yv) : Point(xv, yv) {}

    Vector::Vector(const Point& A, const Point& B) : Point(B.x - A.x, B.y - A.y) {}

     float Vector::Length() const {
        return hypot(this->x, this->y);
    }

    float Vector::Angle() const {
        return atan(y / x) + (x < 0 ? PI : 0);
    }

    float Vector::Angle(const Vector& V) const {
        auto lu = this->Length();
        auto lv = V.Length();
        auto ds = lu * lv;
        auto prod = (*this) ^ V;

        return acos(prod / ds);
    }

    void Vector::Normalize () {
        auto len = this->Length();
        
        this->x /= len;
        this-> y /= len;
    }

    void Vector::Rotate(float angle) {
        auto xv = cos(angle) * this->x - sin(angle) * this->y;
        auto yv = sin(angle) * this->x + cos(angle) * this->y;

        this->x = xv;
        this->y = yv;
    }

    void Vector::Rotate(float angle, const Point& C) {
        (*this) -= C;
        (*this).Rotate(angle);
        (*this) += C;
    }

    Vector Vector::operator= (const Point& P) {
        this->x = P.x;
        this->y = P.y;

        return *this;
    }

    // TODO: check this
    Vector Vector::operator* (const Vector& V) {
        this->x *= V.y;
        this->y *= V.x;

        return *this;
    }

    // TODO: check this
    float Vector::operator^ (const Vector& V) const {
        return this->x * V.x + this->y * V.y;
    }

}