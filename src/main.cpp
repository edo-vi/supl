

#include "../library.h"
#include "Input/Input.h"

#include <iostream> //cout
#include <sstream>
#include <fstream>
#include <string>

int main() {
    using namespace std;

    const array<double, 3> arr{3.14, 2.718, 0.0023};

    auto i = input::Input<double, 3>(arr);

    auto li = input::LabeledInput<double, int, 3> (arr, 213);

    double d = li.getFactor(2); cout << d;

    std::ifstream data = std::ifstream("data/iris/iris.data");

    std::string line;
    while(std::getline(data,&line))
    {
        std::stringstream  lineStream(line);
        std::string        cell;
        while(std::getline(lineStream,cell,','))
        {
            // You have a cell!!!!
        }
    }

}