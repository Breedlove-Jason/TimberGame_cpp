cmake_minimum_required(VERSION 3.17)
project(Timber)

set(CMAKE_CXX_STANDARD 17)

# Find SFML shared libraries
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(Timber main.cpp
        Player.cpp
        Player.h
        LoadResources.cpp
        LoadResources.h
        MoveableObject.cpp
        MoveableObject.h
)

# Link your application with SFML libraries
target_link_libraries(Timber sfml-graphics sfml-audio)

