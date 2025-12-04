cmake_minimum_required(VERSION 3.10)
project(2D_Physical_Engine VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ============ SFML Configuration ============
option(USE_SFML "Enable SFML rendering" OFF)

if(USE_SFML)
    # Try to find SFML in system paths
    find_package(SFML 2.5 COMPONENTS graphics window system)
    if(NOT SFML_FOUND)
        message(STATUS "SFML not found in system paths.")
        message(STATUS "Please install SFML or set SFML_DIR to your SFML build directory.")
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
    target_link_libraries(physics_app PRIVATE sfml-graphics sfml-window sfml-system)
    target_compile_definitions(physics_app PRIVATE ENABLE_SFML=1)
endif()
