cmake_minimum_required(VERSION 3.10)
project(supl)

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(supl
        src/supl.cpp
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

add_custom_target(doc
    COMMAND rm -rf ../doc/html
    COMMAND ../doc/doxygen ../doxyconfig
    COMMAND mv html ../doc
    COMMENT "Generate documentation")

add_custom_target(testing
    COMMAND make tests
    COMMAND ./tests
    COMMENT "Running the tests")

add_executable(exampleKNN examples/exampleKNN.cpp include/supl.h)

add_executable(tests tests/tests.cpp deps/catch.hpp include/supl.h)

