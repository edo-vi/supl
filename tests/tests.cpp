//
// Created by edoardo on 24/07/20.
//
#define CATCH_CONFIG_MAIN

#include "../deps/catch.hpp"
#include "Input/Instance.h"
#include "Input/Sample.h"
#include "Learner/Classification/KNearestNeighbors/KNearestNeighbors.h"

auto s = sample::sampleFromCsv<double, std::string>("../tests/neardouble.csv");

TEST_CASE("Samples are correctly parsed", "[sampleFromCSV]") {

  REQUIRE(s.size() == 2);
  REQUIRE(s[0].instance().factor(1) == -2);
  REQUIRE_THROWS(
      sample::sampleFromCsv<double, std::string>("../tests/missingvalue.csv"));
  REQUIRE_THROWS(
      sample::sampleFromCsv<double, std::string>("../tests/witheader.csv"));
}

TEST_CASE("KNN works correctly", "[KNN]") {
  auto l = knearest::KNearestNeighbors<double, std::string>(1);
  l.train(s);

  int counter = 0;
  auto instance = input::Instance<double>({0, 0, 1});
  for (int i = 0; i < 100000; i++) {
    if (l.predict(instance) == "b")
      counter++;
  }
  // check `<' comparison with double
  REQUIRE(counter == 100000);
}

TEST_CASE("Crossvalidation is correct", "[Crossvalidation]") {

}

TEST_CASE("Correct creation of training and test sample", "[ValidationSample]") {

}