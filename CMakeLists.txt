cmake_minimum_required(VERSION 3.16)

project(Chip8Emulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)

add_executable(chip8Emu 
    src/main.cpp
    src/core/Chip8.cpp
    src/frontend/Input.cpp
    src/frontend/Renderer.cpp
)

target_include_directories(chip8Emu PRIVATE src)

target_link_libraries(chip8Emu PRIVATE SDL2::SDL2)