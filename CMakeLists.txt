cmake_minimum_required(VERSION 4.1)

project(CodBot VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(CodBot
        src/main.cpp
        src/TUI.cpp
        src/Utils.cpp
        src/Movement.cpp
        src/Script.cpp
        src/Presets.cpp
        src/State.cpp
        src/Logger.cpp
        src/resources.rc
)

target_include_directories(CodBot PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(CodBot PRIVATE user32)
