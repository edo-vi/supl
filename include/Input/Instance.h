///@file Instance.h
///@author: ***REMOVED***
///@Date: June 2020
///@Version: 0.1
///@File: Definition of the Instance class and its children
#pragma once

#include <vector> //vector
#include <cassert> //assert
#include <type_traits> //is_arithmetic
#include <cmath> //sqrt

namespace input {

    template<typename T>
    class Instance {
    public:
        Instance() = default;
        explicit Instance(const std::vector<T>& input) : _arr(input) {}
        Instance (T input[], int64_t size) {
            for (int64_t i = 0; i < size; i++) {
                _arr.push_back(input[i]);
            }
        }
        T factor(int64_t index) const {
            return _arr[index];
        }
        int64_t dimensions() const {
            return _arr.size();
        }

        double euclidean (const Instance<T>& other) {
            static_assert(std::is_arithmetic<T>());
            assert(other.dimensions() == dimensions());
            double eu{0};
            for (int i{}; i < other.dimensions(); i++) {
                eu += pow(other.factor(i) - factor(i), 2);
            }
            return sqrt(eu);

        }

    protected:
        std::vector<T> _arr;
    };

    template<typename T, typename Q>
    class LabeledInstance : public Instance<T> {
    public:
        LabeledInstance() = default;

        LabeledInstance(const std::vector<T>& input, Q label) :
                Instance<T>(input),
                _label(label) {}
        LabeledInstance(T input[], int64_t size, Q label) :
                Instance<T>(input, size),
                _label(label){}
        Q label() const {
            return _label;
            }
        Instance<T> instance() const {
            return Instance<T>(this->_arr);
        }

    protected:
        Q _label;
    };

}
