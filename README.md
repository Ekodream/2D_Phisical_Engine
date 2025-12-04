# 2D_Physical_Engine (skeleton)

This is the Phase 1 skeleton for a simple 2D physics engine in C++.

Files added:
- `CMakeLists.txt` - minimal CMake with optional `USE_SFML` flag
- `src/main.cpp` - minimal runner that exercises `PointMass`
- `src/core/Math/Vector2.*` - 2D vector type
- `src/core/Physics/Body.h` - `PointMass` placeholder

Build (PowerShell):

```powershell
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

If you want GUI rendering with SFML, re-run CMake with:

```powershell
cmake -DUSE_SFML=ON ..
cmake --build . --config Release
```

Notes:
- `USE_SFML` is OFF by default — enable it when you have SFML installed and available to CMake.
- Next steps: implement collision primitives, collision detection/response, and a renderer.
