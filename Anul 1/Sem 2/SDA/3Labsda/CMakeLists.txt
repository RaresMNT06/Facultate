cmake_minimum_required(VERSION 4.1)
project(3Labsda)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(3Labsda
        App.cpp
        IteratorMD.cpp
        IteratorMD.h
        MD.cpp
        MD.h
        TestExtins.cpp
        TestExtins.h
        TestScurt.cpp
        TestScurt.h
        IteratorValori.h
        IteratorValori.cpp)
