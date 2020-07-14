cmake_minimum_required(VERSION 3.10)
project(supl)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_library(supl
        library.cpp include/library.h
        include/Input/Instance.h
        include/Input/Sample.h
        include/Learner/Parameter.h
        include/Cross-validation/CrossValidation.cpp include/Cross-validation/CrossValidation.h
        deps/rapidcsv.h
        include/Learner/Learner.h
        include/Loss/LossFunction.h
        include/Learner/Classification/KNearestNeighbors/KNearestNeighbors.h)

add_executable(main src/main.cpp library.cpp)