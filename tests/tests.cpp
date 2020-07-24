//
// Created by edoardo on 24/07/20.
//
#define CATCH_CONFIG_MAIN

#include "../deps/catch.hpp"
#include "Input/Sample.h"

TEST_CASE( "Samples are correctly parsed", "[sampleFromCSV]" ) {
    using namespace std;
    auto sample = sample::sampleFromCsv<double, string>("../tests/datatest.txt");

    REQUIRE(sample.size() == 3);
}