#include <Vector.h>
#include <Point.h>
#include <Logger.h>
#include <Util.h>
#include <cmath>

namespace penguin {

    Vector::Vector(float xv, float yv) : Point(xv, yv) {}

     float Vector::GetLength() const {
        return (float) hypot(this->x, this->y);
    }

    float Vector::GetAngle() const {
        return (float) atan(this->y / this->x) + (this->x < 0 ? PI : 0);
    }

    float Vector::GetAngle(const Vector& V) const {
        auto ds = this->GetLength() * V.GetLength();
        auto prod = (*this) ^ V;

        return (float) acos(prod / ds);
    }

    void Vector::Unit () {
        (*this) /= this->GetLength();
    }

    Vector Vector::GetUnit () const {
        return (*this) / this->GetLength();
    }

    void Vector::Rotate(float angle) {
        auto xv = cos(angle) * this->x - sin(angle) * this->y;
        auto yv = sin(angle) * this->x + cos(angle) * this->y;

        this->x = static_cast<float>(xv);
        this->y = static_cast<float>(yv);
    }

    Vector Vector::GetRotate(float angle) const {
        return {
            static_cast<float>(cos(angle) * this->x - sin(angle) * this->y),
            static_cast<float>(sin(angle) * this->x + cos(angle) * this->y)
        };
    }

    Vector Vector::operator= (const Vector& V) {
        this->x = V.x;
        this->y = V.y;

        return *this;
    }

    Vector Vector::operator= (const Point& P) {
        this->x = P.x;
        this->y = P.y;

        return *this;
    }

    Vector Vector::operator* (const Vector& V) {
        this->x *= V.y;
        this->y *= V.x;

        return *this;
    }

    float Vector::operator^ (const Vector& V) const {
        return this->x * V.x + this->y * V.y;
    }

    Vector Vector::operator* (const float v) const {
        return { this->x * v, this->y * v };
    }

    void Vector::operator*= (const float v) {
        this->x *= v;
        this->y *= v;
    }

    Vector Vector::operator/ (const float v) const {
        return { this->x / v, this->y / v };
    }

    void Vector::operator/= (const float v) {
        this->x /= v;
        this->y /= v;
    }

    Vector Vector::operator+(const Vector &V) const {
        return { this->x + V.x, this->y + V.y };
    }

    Vector Vector::operator+= (const Vector &V) {
        this->x += V.x;
        this->y += V.y;

        return (*this);
    }

    Vector Vector::operator-(const Vector &V) const {
        return { this->x - V.x, this->y - V.y };
    }

    Vector Vector::operator-= (const Vector &V) {
        this->x -= V.x;
        this->y -= V.y;

        return (*this);
    }

    std::ostream& operator<<(std::ostream &out, const Vector& V) {
        out << "Vector: { " << V.x << ", " << V.y << " }";
        return out;
    }

    std::istream&  operator>>(std::istream &in, Vector& V) {
        in >> V.x >> V.y;
        return in;

    }

}