//@author: ***REMOVED***
//@Date: June 2020
//@Version: 0.1
//@File: Definition of the Input class and its children
#pragma once

#include <array>  //array
#include <vector> //vector
#include <cassert>

namespace input {
    template<typename T, int64_t d>
    class Input {
    public:
        Input() = default;
        explicit Input(const std::array<T, d> &input) : _arr(input) {}
        explicit Input(const std::vector<T> &input) {
            assert(input.size() == d);
            _arr = input.data();
        }

        T getFactor(int64_t index) const {
            return _arr.at(index);
        }

    protected:
        std::array<T, d> _arr;
    };

    template<typename T, typename Q, int64_t d>
    class LabeledInput : public Input<T, d> {
    public:
        LabeledInput() = default;

        LabeledInput(const std::array<T, d> &input, Q label) :
                Input<T, d>(input),
                _label(label) {}
    Q getLabel() const {
        return _label;
        }
    protected:
        Q _label;
    };

}
