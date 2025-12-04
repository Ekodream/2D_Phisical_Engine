# 2D Physical Engine (Phase 1)

A simple 2D physics engine in C++ with optional SFML rendering.

## Features (Phase 1)

- **Vector2** math library
- **PointMass** physics entity (position, velocity, force, mass)
- **SFML rendering** support (optional, can run without GUI)
- **CMake build** system with conditional compilation

## Build Instructions

### Prerequisites

- CMake 3.10+
- C++17 compiler (MSVC, GCC, Clang)
- (Optional) SFML 2.5+ for GUI rendering

### Build without GUI (default)

```powershell
cd D:\Documents\CS\Projects\2D_Phisical_Engine
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

Then run:
```powershell
.\physics_app.exe
```

Output: simple numerical integration test (non-visual).

### Build with SFML GUI

#### 1. Install SFML (Windows)

**Option A: Using vcpkg (recommended)**
```powershell
# First install vcpkg if not present
git clone https://github.com/Microsoft/vcpkg.git C:\vcpkg
cd C:\vcpkg
.\bootstrap-vcpkg.bat

# Install SFML
.\vcpkg install sfml:x64-windows
```

**Option B: Manual download**
- Download SFML from [sfml-dev.org](https://www.sfml-dev.org/)
- Extract to a known directory, e.g., `C:\SFML-2.6.0`

#### 2. Configure CMake with SFML

If using **vcpkg**:
```powershell
cd D:\Documents\CS\Projects\2D_Phisical_Engine\build
cmake -DUSE_SFML=ON -DCMAKE_TOOLCHAIN_FILE=C:\vcpkg\scripts\buildsystems\vcpkg.cmake ..
cmake --build . --config Release
```

If using **manual SFML**:
```powershell
cd D:\Documents\CS\Projects\2D_Phisical_Engine\build
cmake -DUSE_SFML=ON -DSFML_DIR="C:\SFML-2.6.0\lib\cmake\SFML" ..
cmake --build . --config Release
```

#### 3. Run with GUI

```powershell
.\physics_app.exe
```

A window opens showing two objects affected by gravity, bouncing off the floor.  
Press **ESC** to quit.

## Project Structure

```
2D_Physical_Engine/
├── CMakeLists.txt
├── README.md
├── src/
│   ├── main.cpp              (entry point; dual-mode)
│   ├── core/
│   │   ├── Math/
│   │   │   ├── Vector2.h     (2D vector type)
│   │   │   └── Vector2.cpp
│   │   └── Physics/
│   │       └── Body.h        (PointMass class)
│   └── render/
│       ├── Renderer.h        (SFML wrapper)
│       └── Renderer.cpp
└── build/                     (generated)
    └── physics_app.exe
```

## Usage

### Without SFML (console output)
```
./physics_app
```
Prints a numerical integration sequence.

### With SFML (interactive window)
- Two objects fall under gravity
- Bounce off the floor with 80% restitution
- Red/cyan lines show velocity vectors
- Press ESC to close

## Next Steps (Phase 2)

- [ ] Implement circular collision detection
- [ ] Add collision response (impulse-based)
- [ ] Verify energy conservation
- [ ] Add user interaction (click to spawn objects)
- [ ] Rigid body with rotation support

## Notes

- SFML is optional; the engine works without it for headless physics simulation.
- `ENABLE_SFML` macro gates all SFML code; stubs exist when disabled.
- Time step is fixed at 1/60s for stability.

## Building & Running (Quick Recap)

**No GUI:**
```powershell
mkdir build; cd build; cmake ..; cmake --build . --config Release; .\physics_app.exe
```

**With GUI (vcpkg):**
```powershell
mkdir build; cd build; cmake -DUSE_SFML=ON -DCMAKE_TOOLCHAIN_FILE=C:\vcpkg\scripts\buildsystems\vcpkg.cmake ..; cmake --build . --config Release; .\physics_app.exe
```
