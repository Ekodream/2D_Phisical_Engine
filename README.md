# 2D_Physical_Engine

A simple 2D physics engine in C++ with an SFML-based interactive viewer.

This repository contains a minimal physics core (point masses), a simple collision resolver
for circle-circle contacts, and an SFML renderer + input to experiment interactively.

IMPORTANT: This build requires SFML. The project is configured to find and link
SFML at configure time (via vcpkg or a local SFML installation).

## Features

- Vector2 math helper
- PointMass physics (position, velocity, mass, radius, restitution)
- Pairwise circle-circle collision detection & impulse response
- SFML-based renderer with interactive controls (spawn, drag-to-throw, select, adjust)

## Controls (when running with GUI)

- Left-click: spawn a new point mass at the cursor (uses current radius/restitution)
- Drag (left-button): spawn with initial velocity proportional to drag vector
- Right-click: select nearest object (within ~30 px)
- R / F : increase / decrease spawn radius (and apply to selected object)
- T / G : increase / decrease restitution (and apply to selected object)
- Space : pause / resume simulation
- ESC   : quit

Selected object is highlighted in yellow and an outline shows its collision radius.

## Build (Windows example)

Prerequisites:
- CMake 3.10+
- A C++17-capable compiler (MSVC recommended on Windows)
- SFML (via vcpkg or manual install)

Example using vcpkg (adjust the vcpkg path to your installation):

```powershell
cd D:\Documents\CS\Projects\2D_Phisical_Engine
mkdir build; cd build
cmake -DCMAKE_TOOLCHAIN_FILE=D:\Programs\vcpkg-master\scripts\buildsystems\vcpkg.cmake ..
cmake --build . --config Release
```

Or if you installed SFML manually:

```powershell
cd D:\Documents\CS\Projects\2D_Phisical_Engine\build
cmake -DSFML_DIR="C:\Path\To\SFML\lib\cmake\SFML" ..
cmake --build . --config Release
```

Run:

```powershell
.\Release\physics_app.exe
```

## Project layout

```
2D_Physical_Engine/
├── CMakeLists.txt
├── README.md
├── README.zh.md          # Chinese README
├── src/
│   ├── main.cpp          # entry point and interactive loop
│   ├── core/
│   │   ├── Math/
│   │   │   ├── Vector2.h
│   │   │   └── Vector2.cpp
│   │   └── Physics/
│   │       ├── Body.h
│   │       ├── Collision.h
│   │       └── Collision.cpp
│   └── render/
│       ├── Renderer.h
│       └── Renderer.cpp
└── build/                 # out-of-tree build directory
```

## Notes

- The renderer currently targets SFML 3 (vcpkg's current package). The code adapts to
  the SFML 3 API (VideoMode, Event, Text signatures). If you must use SFML 2.5, additional
  conditional compatibility work will be needed.
- Physics uses a fixed timestep (1/60). For better stability with many fast objects, consider
  sub-stepping or a more stable integrator (semi-implicit Euler or Verlet).
- Next work items: performance tuning, friction, rigid-body rotation, polygon collisions.
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
cmake -DCMAKE_TOOLCHAIN_FILE=C:\vcpkg\scripts\buildsystems\vcpkg.cmake ..
cmake --build . --config Release
```

If using **manual SFML**:
```powershell
cd D:\Documents\CS\Projects\2D_Phisical_Engine\build
cmake -DSFML_DIR="C:\SFML-2.6.0\lib\cmake\SFML" ..
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

 - SFML is required; the project is built and tested with SFML 3 via vcpkg or a local SFML installation.
- Time step is fixed at 1/60s for stability.

## Building & Running (Quick Recap)

**Build & Run (example using vcpkg):**

```powershell
mkdir build; cd build
cmake -DCMAKE_TOOLCHAIN_FILE=D:\Programs\vcpkg-master\scripts\buildsystems\vcpkg.cmake ..
cmake --build . --config Release
.\Release\physics_app.exe
```
