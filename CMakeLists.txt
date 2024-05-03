cmake_minimum_required(VERSION 3.17)
project(Timber)

set(CMAKE_CXX_STANDARD 17)

# Find SFML shared libraries
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(Timber main.cpp
        Timber.cpp
        Timber.h
        scratch.cpp
        include/Player.h
        src/Entities/Player.cpp
        include/ResourceManager.h
        src/Game/Game.cpp
        include/Game.h
        src/Managers/ResourceManager.cpp
        src/Managers/ResourceManager.h
        src/Entities/Player.h
        src/Entities/Tree.cpp
        src/Entities/Tree.h
        src/Entities/Cloud.cpp
        src/Entities/Cloud.h
        src/Entities/Branch.cpp
        src/Entities/Branch.h
        src/Entities/Background.cpp
        src/Entities/Background.h
        src/Entities/HUD.cpp
        src/Entities/HUD.h
        src/Game/Game.h
)

# Link your application with SFML libraries
target_link_libraries(Timber sfml-graphics sfml-audio)

