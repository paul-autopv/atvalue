cmake_minimum_required(VERSION 3.21)
project(tree)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_VERBOSE_MAKEFILE ON)

# Define header and source files
set(HEADER_FILES
        models/unit.h
        models/Facility.h
        models/FailureMode.h
        models/IProbability.h
        probabilities/WeibullProbability.h
        utilities/CsvReader.h
        models/CsvMap.h
        probabilities/TriangularProbability.h
        controllers/Simulator.h
        controllers/Register.h)

set(SOURCE_FILES
        main.cpp
        models/unit.cpp
        models/Facility.cpp
        models/FailureMode.cpp
        utilities/CsvReader.cpp
        models/CsvMap.cpp
        controllers/Simulator.cpp
        )

add_library(models STATIC ${SOURCE_FILES} ${HEADER_FILES})

add_subdirectory(Google_tests)
add_executable(tree ${SOURCE_FILES})

