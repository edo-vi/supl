///@author Edoardo Zorzi
///@date July 2020
///@version 0.1
///@file tests.cpp
#define CATCH_CONFIG_MAIN

#include "../deps/catch.hpp"
#include "Input/Instance.h"
#include "Input/Sample.h"
#include "Learner/Classification/KNearestNeighbors/KNearestNeighbors.h"
#include "Loss/LossFunction.h"
#include <Cross-validation/CrossValidation.h>

auto s = sample::sampleFromCsv<double, std::string>("../tests/neardouble.csv");

TEST_CASE("Samples are correctly parsed", "[sampleFromCSV]") {
  using namespace std;

  REQUIRE(s.size() == 2);
  REQUIRE(s[0].instance().factor(1) == -2);
  // check the fact that a double can be parsed as a string and that a parsed
  // string label doesn't contain leading whitespaces
  REQUIRE(sample::sampleFromCsv<double, string>("../tests/integerlabel.csv")[0]
              .label() == "0.9982");

  auto stringsample =
      sample::sampleFromCsv<string, double>("../tests/strings.csv");
  REQUIRE(stringsample[1].label() == 6.8);
  REQUIRE(stringsample[1].factor(1) == "3.1415*100");

  REQUIRE_THROWS(
      sample::sampleFromCsv<double, string>("../tests/missingvalue.csv"));
  REQUIRE_THROWS(
      sample::sampleFromCsv<double, string>("../tests/witheader.csv"));
  // REQUIRE_THROWS(
  //     sample::sampleFromCsv<string, string>("../tests/emptylabel.csv"));
}

TEST_CASE("KNN works correctly", "[KNN]") {
  using namespace std;

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

TEST_CASE("Correct slicing of samples", "[Slicing]") {
  using namespace std;

  auto sk = sample::sampleFromCsv<int, string>("../tests/crosstest.csv");
  auto sliced = sample::SlicedSample<int, string, 3>(sk);
  auto setted = sliced.set(1);
  auto training = setted.trainingSet();
  auto validation = setted.validationSet();
  REQUIRE(validation.size() == 3);
  REQUIRE(training.size() == 7);
  for (uint i = 0; i < validation.size(); i++) {
    REQUIRE(validation[i].label() == "b");
  }
}

TEST_CASE("The loss functions are correct", "[LossFunction]") {
  using namespace std;

  auto zeroone = loss::ZeroOneLoss<double, string>();
  REQUIRE(zeroone.loss("a", s[0].label()) == 0);
  REQUIRE(zeroone.loss("a", s[1].label()) == 1);

  auto squared = loss::SquaredLoss<double, double>();
  REQUIRE(squared.loss(1.0, 0.0) == squared.loss(-1.0, 0));
  REQUIRE(squared.loss(-1, -3) <= 4 + 1e-8); // double comparison
}