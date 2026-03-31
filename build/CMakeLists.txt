cmake_minimum_required(VERSION 3.10)
project(SnakeGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/main.cpp
    src/Game.cpp
    src/Snake.cpp
    src/Food.cpp
    src/Renderer.cpp
    src/Input.cpp
    src/SaveSystem.cpp
)

# Add executable
add_executable(SnakeGame ${SOURCES})

# Link libraries if needed
# target_link_libraries(SnakeGame ...)