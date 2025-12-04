cmake_minimum_required(VERSION 3.10)
project(2D_Physical_Engine VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(USE_SFML "Enable SFML rendering (if ON, find SFML)" OFF)

add_executable(physics_app
    src/main.cpp
    src/core/Math/Vector2.cpp
)

target_include_directories(physics_app PRIVATE ${CMAKE_SOURCE_DIR}/src)

if(USE_SFML)
    find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
    target_link_libraries(physics_app PRIVATE sfml-graphics sfml-window sfml-system)
endif()
