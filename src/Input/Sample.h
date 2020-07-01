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

    template <typename T, typename Q, int64_t n, int64_t d>
    Sample<T, Q, n, d> sampleFromCsv(const std::string& filename) {
        using namespace input;

        std::array<LabeledInput<T, Q, d>, n> inputs{};

        rapidcsv::Document doc(filename, rapidcsv::LabelParams(-1, -1));

        auto rows = doc.GetRowCount();
        assert(rows == n);
        for (int64_t i = 0; i < n; i++) {
            std::array<T, d> arr2{};
            int64_t j = 0;
            for (; j < d; j++) {
                arr2[j] = doc.GetCell<T>(j,i);
            }
            Q label = doc.GetCell<Q>(j,i);
            inputs[i] = LabeledInput<T, Q, d>(arr2, label);
        }
        return Sample<T, Q, n, d>(inputs);
    };

}