#include <Vector.h>
#include <Point.h>
#include <Logger.h>
#include <Util.h>
#include <cmath>

namespace penguin {

    Vector::Vector(float xv, float yv) : Point(xv, yv) {}

    Vector::Vector(const Point& A, const Point& B) : Point(B.x - A.x, B.y - A.y) {}

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

    Vector Vector::operator* (const Vector& V) {
        return Vector { this->x * V.y, this->y * V.x };
    }

    float Vector::operator^ (const Vector& V) const {
        return this->x * V.x + this->y * V.y;
    }

}