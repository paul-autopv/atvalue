cmake_minimum_required(VERSION 3.21)
project(tree)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_VERBOSE_MAKEFILE ON)

# Define header and source files
set(HEADER_FILES
        models/tree.h
        models/node.h
        models/unit.h
        )
set(SOURCE_FILES
        models/unit.cpp
        )

add_library(models STATIC ${SOURCE_FILES} ${HEADER_FILES})

add_subdirectory(Google_tests)
add_executable(tree ${SOURCE_FILES})
