#include <iostream> //cout
#include <cstdint>

#include "Input/Sample.h" //Sample



int main(int argc, char** argv) {
    using namespace std;

    std::string filename = "../data/iris/iris.csv";
    auto sa = sample::sampleFromCsv<double, string>(filename);

    std::vector<input::LabeledInstance<double, string>> arr = sa.randomPointsNoReplacement(5);
    sa.size();
}