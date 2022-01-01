cmake_minimum_required(VERSION 3.21)
project(tree)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_VERBOSE_MAKEFILE ON)

# Define header and source files
set(HEADER_FILES
        models/unit.h
        models/Facility.h
        models/FailureModes.h
        models/IProbability.h
        probabilities/WeibullProbability.h)
set(SOURCE_FILES
        models/unit.cpp
        models/Facility.cpp
        models/FailureModes.cpp
        probabilities/WeibullProbability.cpp)

add_library(models STATIC ${SOURCE_FILES} ${HEADER_FILES})

add_subdirectory(Google_tests)
add_executable(tree main.cpp ${SOURCE_FILES})

