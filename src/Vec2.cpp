#include <Vec2.h>

Vec2::Vec2(float xv, float yv) : Point(xv, yv) {}

Vec2::Vec2(Point start, Point destiny)  {
    (*this) = destiny - start;
}

bool Vec2::IsOrigin() const {
    return this->x == 0 && this->y == 0;
}

void Vec2::Reset() {
    this->x = this->y = 0;
}

float Vec2::GetLength() const {
    return (float) hypot(this->x, this->y);
}

float Vec2::GetAngle() const {
    return (float) atan(this->y / this->x) + (this->x < 0 ? PI : 0);
}

float Vec2::GetAngle(const Vec2& V) const {
    auto ds = this->GetLength() * V.GetLength();
    auto prod = (*this) ^ V;

    return (float) acos(prod / ds);
}

void Vec2::Unit () {
    (*this) /= this->GetLength();
}

Vec2 Vec2::GetUnit () const {
    return (*this) / this->GetLength();
}

void Vec2::Rotate(float angle) {
    auto xv = cos(angle) * this->x - sin(angle) * this->y;
    auto yv = sin(angle) * this->x + cos(angle) * this->y;

    this->x = static_cast<float>(xv);
    this->y = static_cast<float>(yv);
}

Vec2 Vec2::GetRotate(float angle) const {
    return {
        static_cast<float>(cos(angle) * this->x - sin(angle) * this->y),
        static_cast<float>(sin(angle) * this->x + cos(angle) * this->y)
    };
}

Vec2 Vec2::operator= (const Vec2& V) {
    this->x = V.x;
    this->y = V.y;

    return *this;
}

Vec2 Vec2::operator= (const Point& P) {
    this->x = P.x;
    this->y = P.y;

    return *this;
}

Vec2 Vec2::operator* (const Vec2& V) {
    this->x *= V.y;
    this->y *= V.x;

    return *this;
}

float Vec2::operator^ (const Vec2& V) const {
    return this->x * V.x + this->y * V.y;
}

Vec2 Vec2::operator* (const float v) const {
    return { this->x * v, this->y * v };
}

void Vec2::operator*= (const float v) {
    this->x *= v;
    this->y *= v;
}

Vec2 Vec2::operator/ (const float v) const {
    return { this->x / v, this->y / v };
}

void Vec2::operator/= (const float v) {
    this->x /= v;
    this->y /= v;
}

Vec2 Vec2::operator+(const Vec2 &V) const {
    return { this->x + V.x, this->y + V.y };
}

Vec2 Vec2::operator+= (const Vec2 &V) {
    this->x += V.x;
    this->y += V.y;

    return (*this);
}

Vec2 Vec2::operator-(const Vec2 &V) const {
    return { this->x - V.x, this->y - V.y };
}

Vec2 Vec2::operator-= (const Vec2 &V) {
    this->x -= V.x;
    this->y -= V.y;

    return (*this);
}

std::ostream& operator<<(std::ostream &out, const Vec2& V) {
    out << "vector: { x:" << V.x << ", y:" << V.y << " }";
    return out;
}

std::istream&  operator>>(std::istream &in, Vec2& V) {
    in >> V.x >> V.y;
    return in;
}