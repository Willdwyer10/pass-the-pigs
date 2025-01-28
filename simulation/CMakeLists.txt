# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(PassThePigsSimulation)

# Set C++ standard (e.g., C++17)
set(CMAKE_CXX_STANDARD 17)

# Add the headers directory to the include path
include_directories(headers)

# Add source files
set(SOURCES
    sources/main.cpp
    sources/GameCoordinator.cpp
    sources/Pig.cpp
    sources/PigRoller.cpp
    sources/Player.cpp
    sources/Simulator.cpp
)

# Create the executable
add_executable(PassThePigsSimulation ${SOURCES})
