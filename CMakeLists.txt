cmake_minimum_required(VERSION 3.10)
project(2D_Physical_Engine VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ============ SFML Configuration ============
option(USE_SFML "Enable SFML rendering" OFF)

if(USE_SFML)
    # Try to find SFML in system paths (accept any installed SFML version)
    # Components are case-sensitive in the SFMLConfig provided by vcpkg
    find_package(SFML COMPONENTS Graphics Window System)
    if(NOT SFML_FOUND)
        message(STATUS "SFML not found in system paths.")
        message(STATUS "Please install SFML via vcpkg or set SFML_DIR to your SFML installation's CMake directory.")
        message(FATAL_ERROR "SFML requested but not found. Install SFML or disable USE_SFML.")
    endif()
    message(STATUS "SFML found: ${SFML_INCLUDE_DIR}")
endif()

# ============ Source Files ============
set(SOURCES
    src/main.cpp
    src/core/Math/Vector2.cpp
)

if(USE_SFML)
    list(APPEND SOURCES src/render/Renderer.cpp)
endif()

# ============ Executable ============
add_executable(physics_app ${SOURCES})

target_include_directories(physics_app PRIVATE ${CMAKE_SOURCE_DIR}/src)

if(USE_SFML)
    # Prefer the imported SFML:: targets provided by the SFMLConfig.cmake
    target_link_libraries(physics_app PRIVATE SFML::Graphics SFML::Window SFML::System)
    target_compile_definitions(physics_app PRIVATE ENABLE_SFML=1)
endif()
