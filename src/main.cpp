#include <iostream> //cout
#include <cstdint>


#include "Input/Sample.h" //Sample
#include "Learner/Parameter.h"
#include "Cross-validation/CrossValidation.h"
#include "Learner/Classification/KNearestNeighbors/KNearestNeighbors.h"


int main(int argc, char** argv) {
    using namespace std;

    std::string filename = "../data/iris/iris.csv";
    sample::Sample<double, string> sa = sample::sampleFromCsv<double, string>(filename);
    sa.shuffle();
    auto sets = sa.split(30);
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    parameter::ParameterSet<int> pset{array, 10};
    auto le = knearest::KNearestNeighbors<double, string>();
    Parameter<int> s = crossvalidation::crossValidate<double, string, int, 4>(le, pset, sets.training);

    cout << "Parameter chosen: " + to_string(s.value()) + "\n";
    le = knearest::KNearestNeighbors<double, string>(s.value());
    le.train(sets.training);
    cout << "Error on test set (30): " + to_string(le.test(sets.test, true));
}