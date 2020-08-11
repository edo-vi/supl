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
        include/Learner/Classification/KNearestNeighbors/KNearestNeighbors.h include/Cross-validation/CrossValidation.i.h include/Input/Instance.i.h include/Input/Sample.i.h include/Learner/Learner.i.h include/Learner/Parameter.i.h include/Learner/Classification/KNearestNeighbors/KNearestNeighbors.i.h include/Loss/LossFunction.i.h)

set_target_properties(supl PROPERTIES LINKER_LANGUAGE CXX)


add_executable(exampleKNN examples/exampleKNN.cpp include/supl.h)

add_executable(tests tests/tests.cpp deps/catch.hpp include/supl.h)

add_compile_options(-Wall -Wextra -Wpedantic -Werror)

add_custom_target(doc
        COMMAND rm -rf ../doc/html
        COMMAND doxygen ../doxyconfig
        COMMAND mv html ../doc
        COMMENT "Generate documentation")

install(TARGETS exampleKNN DESTINATION ${PROJECT_SOURCE_DIR}/bin)


enable_testing()

add_test(NAME parse
        COMMAND tests [parseFromCSV])

add_test(NAME KNN
        COMMAND tests [KNN])

add_test(NAME slicing
        COMMAND tests [Slicing])

add_test(NAME loss
        COMMAND tests [LossFunction])

add_test(NAME valgrind
        COMMAND valgrind ./exampleKNN)
