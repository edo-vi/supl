#pragma once

#include <iostream>

constexpr int hello(int& k) {
    return k++;
}
static void f() {std::cout << "ciao";};

