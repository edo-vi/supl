/** \file Parameter.h
@author: ***REMOVED***
@Date: July 2020
@Version: 0.1
@File: Definition and implementation of the Parameter class and related objects
*/
#pragma once

#include <unordered_set>       //unordered_set
#include <vector>              //vector


namespace parameter {

    template <typename T>
    class ParameterSpace {
    public:
        virtual T min() = 0;
        virtual T max() = 0;
        virtual ~ParameterSpace();
    };

    template<typename T>
    class Parameter {
    public:
        Parameter() = default;
        explicit Parameter(const T& value) : _value(value) {}
        bool operator==(const Parameter<T>& other) const {
            return _value == other._value;
        }
        T value() const noexcept {
            return _value;
        }
    private:
        T _value;
    };

    template <typename T>
    class ParameterSet {
    public:
        explicit ParameterSet(const T array[], int64_t size) {
            for (int64_t i = 0; i < size; i ++) {
                _set.insert(Parameter(array[i]));
            }
        }
        explicit ParameterSet(const Parameter<T> array[], int64_t size) {
            for (int64_t i = 0; i < size; i ++) {
                _set.insert(Parameter(array[i]));
            }
        }
        explicit ParameterSet(const std::vector<T>& array) {
            for (auto elem : array) {
                _set.insert(Parameter(elem));
            }
        }
        explicit ParameterSet(const std::vector<Parameter<T>>& array) {
            for (auto elem : array) {
                _set.insert(elem);
            }
        }
        int64_t size() const noexcept {
            return _set.size();
        }
        std::unordered_set<Parameter<T>> values() const noexcept {
            return _set;
        }

    private:
        std::unordered_set<Parameter<T>> _set{};
    };

}

namespace std {
    using namespace parameter;
    template<typename T> struct hash<Parameter<T>> {
        std::size_t operator()(Parameter<T> const& s) const noexcept {
            return std::hash<T>()(s.value());
        }
    };
}