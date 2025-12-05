#pragma once
#include "Body.h"

namespace engine {

// Resolve circle-circle collision between two PointMass objects (in-place).
// Applies impulse-based velocity change and positional correction to avoid sinking.
void resolveCircleCollision(PointMass &a, PointMass &b);

} // namespace engine
