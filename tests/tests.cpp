//
// Created by edoardo on 24/07/20.
//
#define CATCH_CONFIG_MAIN

#include "../deps/catch.hpp"
#include "Input/Instance.h"
#include "Input/Sample.h"
#include "Learner/Classification/KNearestNeighbors/KNearestNeighbors.h"
#include "Loss/LossFunction.h"

using namespace std; //for ease of use

auto s = sample::sampleFromCsv<double, string>("../tests/neardouble.csv");

TEST_CASE("Samples are correctly parsed", "[sampleFromCSV]") {
  REQUIRE(s.size() == 2);
  REQUIRE(s[0].instance().factor(1) == -2);
  //check the fact that a double can be parsed as a string and that a parsed string label doesn't contain
  //leading whitespaces
  REQUIRE(sample::sampleFromCsv<double, string>("../tests/integerlabel.csv")[0].label() == "0.9982");
  REQUIRE_THROWS(
      sample::sampleFromCsv<double, string>("../tests/missingvalue.csv"));
  REQUIRE_THROWS(
      sample::sampleFromCsv<double, string>("../tests/witheader.csv"));
  //REQUIRE_THROWS(
  //     sample::sampleFromCsv<string, string>("../tests/emptylabel.csv"));
}

TEST_CASE("KNN works correctly", "[KNN]") {
  auto l = knearest::KNearestNeighbors<double, string>(1);
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

TEST_CASE("The loss functions are correct", "[LossFunction]") {
  auto zeroone = loss::ZeroOneLoss<double, string>();
  REQUIRE(zeroone.loss("a", s[0].label()) == 0);
  REQUIRE(zeroone.loss("a", s[1].label()) == 1);

  auto squared = loss::SquaredLoss<double, double>();
  REQUIRE(squared.loss(1.0, 0.0) == squared.loss(-1.0, 0));
  REQUIRE(squared.loss(-1, -3) <= 4 + 1e-8); //double comparison
}