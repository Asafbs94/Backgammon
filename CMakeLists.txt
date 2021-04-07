cmake_minimum_required(VERSION 3.17)
project(Backgammon)

set(CMAKE_CXX_STANDARD 98)

add_executable(Backgammon main.cpp Board.h Board.cpp Player.h Player.cpp)