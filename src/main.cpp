#include <iostream> //cout
#include <cstdint>


#include "Input/Sample.h" //Sample
#include "Learner/Parameter.h"


int main(int argc, char** argv) {
    using namespace std;

    std::string filename = "../data/iris/iris.csv";
    auto sa = sample::sampleFromCsv<double, string>(filename);

    std::vector<input::LabeledInstance<double, string>> arr = sa.randomPointsNoReplacement(5);
    sa.size();
    std::array<int, 5> array{{3, 4, 0, -123, 4}};
    parameter::ParameterSet<int, 5> pset{array};

    for (auto e : pset._set) {
        cout << e.value();
        cout << "\n";
    }
}