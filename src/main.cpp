#include <iostream> //cout
#include <cstdint>


#include "Input/Sample.h" //Sample
#include "Learner/Parameter.h"
#include "Cross-validation/CrossValidation.h"


int main(int argc, char** argv) {
    using namespace std;

    std::string filename = "../data/iris/iris.csv";
    sample::Sample<double, string> sa = sample::sampleFromCsv<double, string>(filename);

    double array[] = {3, 4, 0, -123};
    parameter::ParameterSet<double> pset{array, 4};
    auto l = learner::ConcreteLearner<double, string>{};
    crossvalidation::crossValidate<double, string, double, 4>(l, pset, sa);
}