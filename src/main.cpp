#include <iostream> //cout
#include <cstdint>


#include "Input/Sample.h" //Sample
#include "Learner/Parameter.h"
#include "Cross-validation/CrossValidation.h"


int main(int argc, char** argv) {
    using namespace std;

    std::string filename = "../data/iris/iris.csv";
    sample::Sample<double, string> sa = sample::sampleFromCsv<double, string>(filename);

    std::array<double, 4> array{{3, 4, 0, -123}};
    parameter::ParameterSet<double, 4> pset{array};

    crossvalidation::crossValidate<double, string, double, 4, 4>(learner::ConcreteLearner<double, string>{}, pset, sa);
}