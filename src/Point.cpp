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

Point Point::operator+ (const Point& P) {
    this->x += P.x;
    this->y += P.y;

    return *this; 
}

Point Point::operator-= (const Point& P) {
    this->x -= P.x;
    this->y -= P.y;

    return *this; 
}

Point Point::operator- (const Point& P) {
    this->x -= P.x;
    this->y -= P.y;

    return *this; 
}

Point Point::operator* (float value) {
    this->x *= value;
    this->y *= value;

    return *this;
}

Point Point::operator/ (float value) {
    this->x /= value;
    this->y /= value;

    return *this;
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