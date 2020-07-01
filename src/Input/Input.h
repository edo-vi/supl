//@author: ***REMOVED***
//@Date: June 2020
//@Version: 0.1
//@File: Definition of the Input class and its children
#pragma once

#include <array>

namespace input {
    template<typename T, int64_t d>
    class Input {
    public:
        explicit Input(const std::array<T, d> &input) : _arr(input) {}

        T getFactor(int64_t index) const {
            return _arr.at(index);
        }

    protected:
        std::array<T, d> _arr;
    };

    template<typename T, typename Q, int64_t d>
    class LabeledInput : public Input<T, d> {
    public:
        LabeledInput(const std::array<T, d> &input, Q label) :
                Input<T, d>(input),
                _label(label) {}
    constexpr Q getLabel() const {
        return _label;
        }
    protected:
        Q _label;
    };

}
