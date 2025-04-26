cmake_minimum_required(VERSION 3.10)

project(simulator)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
    src/main.cpp
)

set(HEADERS
    src/verlet_solver.hpp
    src/renderer.hpp
)

# Tell CMake where to find SFML
# May depend based on where you install sfml
set(SFML_DIR /opt/homebrew/Cellar/sfml/2.6.1)

include_directories(${SFML_DIR}/include)

link_directories(${SFML_DIR}/lib)

add_executable(simulator ${SOURCES} ${HEADERS})

target_link_libraries(simulator
    sfml-graphics
    sfml-system
    sfml-window
)