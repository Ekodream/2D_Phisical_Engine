cmake_minimum_required(VERSION 3.10)
project(2D_Physical_Engine VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ============ SFML Configuration (required) ============
message(STATUS "SFML support is required for this project. Searching for SFML...")
# Components are case-sensitive in SFMLConfig (vcpkg / SFML 3)
find_package(SFML COMPONENTS Graphics Window System REQUIRED)
if(NOT SFML_FOUND)
    message(FATAL_ERROR "SFML not found. Install SFML or configure SFML_DIR, or use vcpkg.")
endif()
message(STATUS "Found SFML: ${SFML_INCLUDE_DIR}")

# ============ Source Files ============
set(SOURCES
    src/main.cpp
    src/core/Math/Vector2.cpp
    src/core/Physics/Collision.cpp
    src/render/Renderer.cpp
)

# ============ Executable ============
add_executable(physics_app ${SOURCES})

target_include_directories(physics_app PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Link SFML (required)
target_link_libraries(physics_app PRIVATE SFML::Graphics SFML::Window SFML::System)
target_compile_definitions(physics_app PRIVATE ENABLE_SFML=1)
