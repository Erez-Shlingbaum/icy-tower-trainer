cmake_minimum_required (VERSION 3.20)
project (GAME_TRAINER)

set(CMAKE_CXX_STANDARD 23)


add_executable(GameTrainer src/main.cpp src/handle.cpp src/os_utils.cpp)
target_include_directories(GameTrainer PUBLIC include/)
