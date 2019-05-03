#include <Point.h>

Point::Point(float xv, float yv) : x(xv), y(yv) {}

float Point::Distance(const Point& P, const Point& Q) {
    return (float) hypot(P.x - Q.x, P.y - Q.y);
}

Point Point::operator+= (const Point& P) {
    this->x += P.x;
    this->y += P.y;

    return *this; 
}

Point Point::operator+(const Point &P) const {
    return { this->x + P.x, this->y + P.y };
}

Point Point::operator-= (const Point& P) {
    this->x -= P.x;
    this->y -= P.y;

    return *this; 
}

Point Point::operator-(const Point &P) const {
    return { this->x - P.x, this->y - P.y };
}

Point Point::operator*= (const float value) {
    this->x *= value;
    this->y *= value;

    return *this; 
}

Point Point::operator*(const float value) const {
    return { this->x * value, this->y * value };
}

Point Point::operator/= (const float value) {
    this->x /= value;
    this->y /= value;

    return *this;
}

Point Point::operator/(const float value) const {
    return { this->x / value, this->y / value };
}

Point Point::operator= (const Point& P) {
    this->x = P.x;
    this->y = P.y;

    return (*this);
}

bool Point::operator==(const Point& P) {
    return EQUAL(this->x, P.x) && EQUAL(this->y, P.y);
}

bool Point::operator<(const Point& P) {
    return EQUAL(this->x, P.x) ? this->y < P.y : this->x < P.x;
}

std::ostream& operator<<(std::ostream &out, const Point& P) {
    out << "point: { x:" << P.x << ", y:" << P.y << " }";
    return out;
}

std::istream&  operator>>(std::istream &in, Point& P) {
    in >> P.x >> P.y;
    return in;
}