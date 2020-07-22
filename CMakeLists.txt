cmake_minimum_required(VERSION 3.10)
project(supl)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_library(supl
        include/supl.h
        include/Input/Instance.h
        include/Input/Sample.h
        include/Learner/Parameter.h
        include/Cross-validation/CrossValidation.h
        deps/rapidcsv.h
        include/Learner/Learner.h
        include/Loss/LossFunction.h
        include/Learner/Classification/KNearestNeighbors/KNearestNeighbors.h)

set_target_properties(supl PROPERTIES LINKER_LANGUAGE CXX)

add_compile_options(-Wall -Wextra -Wpedantic -Werror)

add_executable(exampleKNN examples/exampleKNN.cpp)


