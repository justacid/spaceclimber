cmake_minimum_required( VERSION 2.8 )
project(SpaceClimber)

include_directories(${CMAKE_SOURCE_DIR}/src)

set(HEADER src/Engine.h
        src/Platform.h
        src/MapGenerator.h
        src/ResourceManager.h
        src/FpsCounter.h
        src/Player.h
        src/Utility/DebugDraw.h
        src/Utility/b2Helper.hpp
        src/JumpContactListener.h
        src/Physics.h
        src/Camera.h
        src/Scenes/Scene.h
        src/Scenes/SceneManager.h
        src/Scenes/Title.h
        src/Scenes/TitleTransition.h
        src/Scenes/Game.h
        src/Scenes/GameOver.h
        src/SoundManager.h
        src/Scenes/Options.h
        src/Scenes/Pause.h
        src/Animation.h
        src/PowerUps/PowerUp.h
        src/PowerUps/SpeedDown.h
        src/PowerUps/SpeedUp.h
        src/PowerUps/TimeStop.h
        src/PowerUps/DoubleJump.h
        src/PowerUps/SafetyNet.h
)

set(SOURCE src/main.cpp
        src/Engine.cpp
        src/Platform.cpp
        src/MapGenerator.cpp
        src/ResourceManager.cpp
        src/FpsCounter.cpp
        src/Player.cpp
        src/Utility/DebugDraw.cpp
        src/JumpContactListener.cpp
        src/Physics.cpp
        src/Camera.cpp
        src/Scenes/Scene.cpp
        src/Scenes/SceneManager.cpp
        src/Scenes/Title.cpp
        src/Scenes/TitleTransition.cpp
        src/Scenes/Game.cpp
        src/Scenes/GameOver.cpp
        src/SoundManager.cpp
        src/Scenes/Options.cpp
        src/Scenes/Pause.cpp
        src/Animation.cpp
        src/PowerUps/SpeedDown.cpp
        src/PowerUps/SpeedUp.cpp
        src/PowerUps/TimeStop.cpp
        src/PowerUps/DoubleJump.cpp
        src/PowerUps/SafetyNet.cpp
)

set(EXECUTABLE "SpaceClimber")
add_executable(${EXECUTABLE} ${HEADER} ${SOURCE})

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/modules")

add_definitions(-std=c++14 -Wall -Wextra -O2)
find_package(SFML 2 REQUIRED system window graphics network audio)
find_package(Box2D REQUIRED)
find_package(PhysFS REQUIRED)
target_link_libraries(${EXECUTABLE} ${SFML_LIBRARIES} Box2D physfs)
