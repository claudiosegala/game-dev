#include <Vector.h>
#include <Point.h>
#include <Logger.h>
#include <cmath>

namespace penguin {

    #define PI 3.141592653589793

    Vector::Vector(double xv, double yv) : Point(xv, yv) {}

    Vector::Vector(const Point& A, const Point& B) : Point(B.x - A.x, B.y - A.y) {}

    double Vector::Angle() const {
        return atan(y / x) + (x < 0 ? PI : 0);
    }

    double Vector::Angle(const Vector& V) const {
        auto lu = this->Length();
        auto lv = V.Length();
        auto ds = lu * lv;
        auto prod = (*this) ^ V;

        return acos(prod / ds);
    }

    Vector Vector::operator* (const Vector& V) {
        return Vector { this->x * V.y, this->y * V.x };
    }

    double Vector::operator^ (const Vector& V) const {
        return this->x * V.x + this->y * V.y;
    }

}