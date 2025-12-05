#pragma once
#include <cmath>

namespace engine {

struct Vector2 {
    double x;
    double y;
    Vector2(double x_ = 0.0, double y_ = 0.0) : x(x_), y(y_) {}
    Vector2 operator+(const Vector2& o) const { return Vector2(x + o.x, y + o.y); }
    Vector2 operator-(const Vector2& o) const { return Vector2(x - o.x, y - o.y); }
    Vector2 operator*(double s) const { return Vector2(x * s, y * s); }
    Vector2& operator+=(const Vector2& o) { x += o.x; y += o.y; return *this; }
    double dot(const Vector2& o) const { return x * o.x + y * o.y; }
    double length() const { return std::sqrt(x * x + y * y); }
};

} 
