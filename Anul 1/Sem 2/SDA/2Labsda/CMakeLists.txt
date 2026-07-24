cmake_minimum_required(VERSION 4.1)
project(2Labsda)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(2Labsda
        App.cpp
        IteratorMultime.cpp
        IteratorMultime.h
        Multime.cpp
        Multime.h
        TestExtins.cpp
        TestExtins.h
        TestScurt.cpp
        TestScurt.h)
