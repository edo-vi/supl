cmake_minimum_required(VERSION 3.10)
project(supl)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_library(supl
        library.cpp library.h
        src/Input/Instance.h
        src/Input/Sample.h
        src/Learner/Parameter.h
        src/Cross-validation/CrossValidation.cpp src/Cross-validation/CrossValidation.h
        deps/rapidcsv.h
        src/Learner/Learner.h
        src/Loss/LossFunction.h
        src/Learner/Classification/KNearestNeighbors/KNearestNeighbors.h)

add_executable(main src/main.cpp library.cpp)