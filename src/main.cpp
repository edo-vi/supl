#include <iostream> //cout
#include <cstdint>


#include "Input/Sample.h" //Sample
#include "Learner/Parameter.h"
#include "Cross-validation/CrossValidation.h"
#include "Learner/Classification/KNearestNeighbors/KNearestNeighbors.h"


int main(int argc, char** argv) {
    using namespace std;

    //iris
    std::string filename = "../data/iris/iris.csv";
    sample::Sample<double, string> sa = sample::sampleFromCsv<double, string>(filename);
    sa.shuffle();
    auto sets = sa.split(30);
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19};
    parameter::ParameterSet<int> pset{array, 10};
    auto le = knearest::KNearestNeighbors<double, string>();
    Parameter<int> s = crossvalidation::crossValidate<double, string, int, 4>(le, pset, sets.training);

    cout << "Parameter chosen: " + to_string(s.value()) + "\n";
    le = knearest::KNearestNeighbors<double, string>(s.value());
    le.train(sets.training);
    cout << "Error on test set (30): " + to_string(le.test(sets.test, true)) + "\n";

    //wine
    filename = "../data/wine/wine.csv";
    sample::Sample<double, int> sa2 = sample::sampleFromCsv<double, int>(filename);
    sa2.shuffle();
    sample::ValidationSample<double, int> sets2 = sa2.split(30);
    int array2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19};
    pset = ParameterSet<int>(array2, 10);
    auto le2 = knearest::KNearestNeighbors<double, int>();
    s = crossvalidation::crossValidate<double, int, int, 4>(le2, pset, sets2.training);

    cout << "Parameter chosen: " + to_string(s.value()) + "\n";
    le2 = knearest::KNearestNeighbors<double, int>(s.value());
    le2.train(sets2.training);
    cout << "Error on test set (30): " + to_string(le2.test(sets2.test)) + "\n";
}