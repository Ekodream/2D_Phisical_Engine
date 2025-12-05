#include "Collision.h"
#include <cmath>
#include <algorithm>

namespace engine {

void resolveCircleCollision(PointMass &a, PointMass &b) {
    // Vector from a to b
    Vector2 n = b.position - a.position;
    double dist = n.length();
    double r = a.radius + b.radius;
    if (dist == 0.0) {
        // Prevent division by zero; nudge a little
        n = Vector2(1.0, 0.0);
        dist = 1e-6;
    }

    // Check for penetration
    if (dist >= r) return; // no collision

    // Normalized collision normal
    Vector2 normal = n * (1.0 / dist);

    // Relative velocity
    Vector2 rv = b.velocity - a.velocity;

    // Relative velocity along the normal
    double velAlongNormal = rv.dot(normal);

    // Do not resolve if velocities are separating
    if (velAlongNormal > 0)
        ; // allow position correction but skip impulse

    // Compute restitution (use min of both)
    double e = std::min(a.restitution, b.restitution);

    // Compute impulse scalar
    double invMassA = (a.mass > 0.0) ? 1.0 / a.mass : 0.0;
    double invMassB = (b.mass > 0.0) ? 1.0 / b.mass : 0.0;

    double j = 0.0;
    if (velAlongNormal < 0) {
        j = -(1.0 + e) * velAlongNormal / (invMassA + invMassB);
    }

    // Apply impulse
    Vector2 impulse = normal * j;
    if (invMassA > 0) a.velocity += impulse * (-invMassA);
    if (invMassB > 0) b.velocity += impulse * (invMassB);

    // Positional correction to avoid sinking (Baumgarte-like)
    const double percent = 0.2; // usually 20% to 80%
    const double slop = 0.01;   // penetration allowance
    double penetration = r - dist;
    double correctionMag = std::max(penetration - slop, 0.0) / (invMassA + invMassB) * percent;
    Vector2 correction = normal * correctionMag;
    if (invMassA > 0) a.position += correction * (-invMassA);
    if (invMassB > 0) b.position += correction * (invMassB);
}

} // namespace engine
