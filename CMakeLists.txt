cmake_minimum_required(VERSION 3.17)
project(Backgammon)


set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -pedantic")
add_executable(Backgammon main.cpp Game_board.h Game_board.cpp)