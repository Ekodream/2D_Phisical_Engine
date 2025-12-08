#pragma once
#include "../Math/Vector2.h"

namespace engine {

struct PointMass {
    Vector2 position;
    Vector2 velocity;
    double mass;
    double radius = 6.0;        
    double restitution = 0.8;   

    PointMass(const Vector2& p = Vector2(), const Vector2& v = Vector2(), double m = 1.0, double r = 6.0, double rest = 0.8)
        : position(p), velocity(v), mass(m), radius(r), restitution(rest) {} //initialization with defaults

    void applyForce(const Vector2& force, double dt) {
        Vector2 acc = force * (1.0 / mass);
        velocity += acc * dt;
    }

    void integrate(double dt) {
        position += velocity * dt;
    }
    double kineticEnergy() const { return 0.5 * mass * (velocity.x*velocity.x + velocity.y*velocity.y); }
};

} 
