cmake_minimum_required(VERSION 3.10)
project(vector)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
#include_directories(__MACOSX)
#include_directories(__MACOSX/data)
include_directories(data)

add_executable(vector
#        __MACOSX/data/one/._code.cpp
#        __MACOSX/data/one.memcheck/._code.cpp
#        __MACOSX/data/three/._code.cpp
#        __MACOSX/data/three.memcheck/._code.cpp
#        __MACOSX/data/two/._code.cpp
#        __MACOSX/data/two.memcheck/._code.cpp
#        __MACOSX/data/._class-bint.hpp
#        __MACOSX/data/._class-integer.hpp
#        __MACOSX/data/._class-matrix.hpp
#        __MACOSX/._exceptions.hpp
#        __MACOSX/._utility.hpp
#        __MACOSX/._vector.hpp
#        data/one/code.cpp
#        data/one.memcheck/code.cpp
#        data/three/code.cpp
        data/three.memcheck/code.cpp
#        data/two/code.cpp
#        data/two.memcheck/code.cpp
        data/class-bint.hpp
        data/class-integer.hpp
        data/class-matrix.hpp
        exceptions.hpp
        utility.hpp
        vector.hpp
#        data/main.cpp
        )
