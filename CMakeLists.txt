cmake_minimum_required(VERSION 3.30)
project(GuessTheWordGame)

set(CMAKE_CXX_STANDARD 20)

add_executable(GuessTheWordGame main.cpp
        game.cpp
        game.h)
