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

    int array[] = {3, 4, 8, 1};
    parameter::ParameterSet<int> pset{array, 4};
    auto le = knearest::KNearestNeighbors<double, string>(4);
    crossvalidation::crossValidate<double, string, int, 4>(le, pset, sa);
}