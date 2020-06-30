

#include "../library.h"
#include "Input/Input.h"

#include <iostream> //cout


int main() {
    using namespace std;

    const array<double, 3> arr{3.14, 2.718, 0.0023};

    auto i = input::Input<double, 3>(arr);

    auto li = input::LabeledInput<double, int, 3> (arr, 213);

    double d = li.getFactor(5); cout << d;

}