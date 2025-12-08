#include "Collision.h"
#include <cmath>
#include <algorithm>

namespace engine {

void resolveCircleCollision(PointMass &a, PointMass &b) {
    
    Vector2 n = b.position - a.position;
    double dist = n.length();
    double r = a.radius + b.radius;
    //Debug:Prevent division by zero,just move a little
    if (dist == 0.0) {
        
        n = Vector2(1.0, 0.0);
        dist = 1e-6;
    }

    if (dist >= r) return; // no collision

    Vector2 normal = n * (1.0 / dist);//normal vector
    Vector2 rv = b.velocity - a.velocity;//Relative velocity
    double velAlongNormal = rv.dot(normal);// Relative velocity along the normal

    // Do not resolve if velocities are separating
    // allow position correction but skip impulse
    bool separating = velAlongNormal > 0;

    double e = std::min(a.restitution, b.restitution);// Coefficient of restitution

    // Compute impulse scalar
    double invMassA = (a.mass > 0.0) ? 1.0 / a.mass : 0.0;
    double invMassB = (b.mass > 0.0) ? 1.0 / b.mass : 0.0;

    double j = 0.0;//impulse scalar
    if (!separating) {
        j = -(1.0 + e) * velAlongNormal / (invMassA + invMassB);
    }

    // Apply impulse
    Vector2 impulse = normal * j;
    if (invMassA > 0) a.velocity += impulse * (-invMassA);
    if (invMassB > 0) b.velocity += impulse * (invMassB);

    //This part is finished with the help of AI
    //To solve positional correction to avoid sinking (Baumgarte-like)
    //The idea is to push the objects apart based on their penetration depth
    const double percent = 0.2; // usually 20% to 80%
    const double slop = 0.01;   // penetration allowance
    double penetration = r - dist;
    double correctionMag = std::max(penetration - slop, 0.0) / (invMassA + invMassB) * percent;
    Vector2 correction = normal * correctionMag;
    if (invMassA > 0) a.position += correction * (-invMassA);
    if (invMassB > 0) b.position += correction * (invMassB);
}

} 
