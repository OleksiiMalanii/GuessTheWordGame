cmake_minimum_required(VERSION 3.30)
project(GuessTheWordGame)

set(CMAKE_CXX_STANDARD 20)


set(pybind11_DIR "C:/Users/Oleksii Malanii/PycharmProjects/UI/.venv/Lib/site-packages/pybind11/share/cmake/pybind11")
find_package(pybind11 REQUIRED)
add_executable(GuessTheWordGame main.cpp
        game.cpp
        game.h
        GameModule.cpp)

# Додавання Pybind11 в якості залежності
target_link_libraries(GuessTheWordGame PRIVATE pybind11::module)

# Налаштування Python
find_package(Python3 REQUIRED COMPONENTS Development)
include_directories(${Python3_INCLUDE_DIRS})
link_directories(${Python3_LIBRARY_DIRS})
