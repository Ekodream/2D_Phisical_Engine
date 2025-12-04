#include <iostream>
#include "core/Math/Vector2.h"
#include "core/Physics/Body.h"

int main() {
    std::cout << "2D Physical Engine - skeleton\n";
    engine::PointMass p({0.0, 0.0}, {1.0, 0.0}, 1.0);
    p.integrate(1.0);
    std::cout << "Position: " << p.position.x << ", " << p.position.y << "\n";
    return 0;
}
