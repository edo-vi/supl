cmake_minimum_required(VERSION 3.10)
project(supl)

set(CMAKE_CXX_STANDARD 17)

add_library(supl
        library.cpp library.h
        src/Input/Instance.h
        src/Input/Sample.h
        src/Learner/Parameter.h
        src/Cross-validation/CrossValidation.cpp src/Cross-validation/CrossValidation.h
        deps/rapidcsv.h src/Learner/Learner.cpp src/Learner/Learner.h src/Loss/LossFunction.cpp src/Loss/LossFunction.h)

add_executable(main src/main.cpp library.cpp)