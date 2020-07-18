///@file exampleCNN.cpp
///@Author: ***REMOVED***
///@Date: July 2020
///@Version: 0.1
///@File: K-Nearest Neighbors example

#include "supl.h" //Sample

#include <iostream>     //cout

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

    cout << "------------------ IRIS -----------------\nParameter chosen: " + to_string(s.value()) + "\n\n";
    le = knearest::KNearestNeighbors<double, string>(s.value());
    le.train(sets.training);
    cout << "\nError on test set (30): " + to_string(le.test(sets.test, true)) + "\n\n";

    //wine
    filename = "../data/wine/wine.csv";
    sample::Sample<double, int> sa2 = sample::sampleFromCsv<double, int>(filename);
    sa2.shuffle();
    sample::ValidationSample<double, int> sets2 = sa2.split(30);
    pset = ParameterSet<int>(array, 10);
    auto le2 = knearest::KNearestNeighbors<double, int>();
    s = crossvalidation::crossValidate<double, int, int, 4>(le2, pset, sets2.training);

    cout << "---------- WINE ----------\nParameter chosen: " + to_string(s.value()) + "\n\n";
    le2 = knearest::KNearestNeighbors<double, int>(s.value());
    le2.train(sets2.training);
    cout << "\nError on test set (30): " + to_string(le2.test(sets2.test, true)) + "\n\n";

    filename = "../data/ecoli/ecoli.csv";
    sa = sample::sampleFromCsv<double, string>(filename);
    sa.shuffle();
    sets = sa.split(30);
    pset = ParameterSet<int>(array, 10);
    le = knearest::KNearestNeighbors<double, string>();
    s = crossvalidation::crossValidate<double, string, int, 4>(le, pset, sets.training);

    cout << "---------- ECOLI ----------\nParameter chosen: " + to_string(s.value()) + "\n\n";
    le = knearest::KNearestNeighbors<double, string>(s.value());
    le.train(sets.training);
    cout << "\nError on test set (30): " + to_string(le.test(sets.test, true)) + "\n\n";

}
