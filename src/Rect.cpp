#include <Rect.h>

Rect::Rect() : vector(), width(0), height(0) {}

Rect::Rect(Vec2 v, float w, float h) : vector(v), width(w), height(h) {}

Rect::Rect(float x, float y, float w, float h) : vector(x, y), width(w), height(h) {}

Point Rect::Center() const {
    Point dl, ur;

    std::tie(dl, ur) = GetPoints();

    return (dl + ur) / 2;
}

float Rect::CenterDistance(const Rect& R) const {
    auto c1 = this->Center();
    auto c2 = R.Center();

    return Point::Distance(c1, c2);
}

bool Rect::IsInside(const Point& P) const {
    return (P.x >= this->vector.x && P.x <= this->vector.x + this->width)
        && (P.y >= this->vector.y && P.y <= this->vector.y + this->height);
} 

std::tuple<Point, Point> Rect::GetPoints() const {
    auto u = static_cast<Point>(this->vector); // down left
    auto x = (u.x + this->width);
    auto y = (u.y + this->height);
    auto v = Point(x, y); // upper right

    return std::make_tuple(v, u);
}

Rect Rect::operator+ (const Vec2& V) const {
    return Rect { this->vector + V, this->width, this->height };
}

void Rect::operator+= (const Vec2& V) {
    this->vector.x += V.x;
    this->vector.y += V.y;
}

Rect Rect::operator- (const Vec2& V) const {
    return Rect { this->vector - V, this->width, this->height };
}

void Rect::operator-= (const Vec2& V) {
    this->vector.x -= V.x;
    this->vector.y -= V.y;
}

Rect Rect::operator* (float value) const {
    auto w = this->width * value;
    auto h = this->height * value;

    return Rect { this->vector, w, h};
}   

void Rect::operator*= (float v) {
    this->vector.x *= v;
    this->vector.y *= v;
}

Rect Rect::operator= (const Rect& R) {
    return Rect { R.vector, R.width, R.height };
}