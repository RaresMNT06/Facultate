cmake_minimum_required(VERSION 4.1)
project(1Labsda)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(1Labsda
        App.cpp
        Colectie.cpp
        Colectie.h
        IteratorColectie.cpp
        IteratorColectie.h
        TestExtins.cpp
        TestExtins.h
        TestScurt.cpp
        TestScurt.h)
