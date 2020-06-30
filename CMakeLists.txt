cmake_minimum_required(VERSION 3.10)
project(supl)

set(CMAKE_CXX_STANDARD 17)

add_library(supl
        library.cpp library.h
        src/Input/Input.cpp src/Input/Input.h
        src/Input/Sample.cpp src/Input/Sample.h
        )

add_executable(main src/main.cpp library.cpp)