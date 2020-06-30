//@author: ***REMOVED***
//@Date: June 2020
//@Version: 0.1
//@File: Definition of the Sample class and its children
#pragma once

#include <array>

#include "Input.h"
namespace sample {
    template<typename T, typename Q, int64_t n, int64_t d>
    class Sample {
    public:
        explicit Sample(const std::array<input::LabeledInput<T, Q, d>, n>& s) : _sample(s) {}

    protected:
        std::array<input::LabeledInput<T, Q, d>, n> _sample;
    };
}