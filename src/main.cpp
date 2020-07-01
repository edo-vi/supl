

#include <iostream> //cout

#include "../library.h"
#include "Input/Input.h"
#include "../deps/rapidcsv.h"
#include "Input/Sample.h"
#include <cstdint>

int main() {
    using namespace std;

    const array<double, 3> arr{3.14, 2.718, 0.0023};

    auto input = input::Input<double, 3>(arr);

    auto linput = input::LabeledInput<double, int, 3> (arr, 213);


    std::string filename = "../data/iris/iris.csv";

    const int64_t d = 5;
    const int64_t n = 150;


    auto s = sample::sampleFromCsv<double, string, n, 4>(filename);
    s;
}