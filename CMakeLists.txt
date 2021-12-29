cmake_minimum_required(VERSION 3.21)
project(tree)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(tree main.cpp Node.h Tree.h Unit.cpp Unit.h)
