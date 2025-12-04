#pragma once
#include "../Math/Vector2.h"

namespace engine {

struct PointMass {
    Vector2 position;
    Vector2 velocity;
    double mass;
    PointMass(const Vector2& p = Vector2(), const Vector2& v = Vector2(), double m = 1.0)
        : position(p), velocity(v), mass(m) {}

    void applyForce(const Vector2& force, double dt) {
        Vector2 acc = force * (1.0 / mass);
        velocity += acc * dt;
    }

    void integrate(double dt) {
        position += velocity * dt;
    }
};

} // namespace engine
