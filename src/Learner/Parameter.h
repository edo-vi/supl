//
// Created by edoardo on 04/07/20.
//
#pragma once

#include <bits/unordered_set.h>
#include <unordered_set>


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
        explicit Parameter(T value) : _value(value) {}
        bool operator==(const Parameter<T>& other) const {
            return _value == other._value;
        }
        T value() const noexcept {
            return _value;
        }
    private:
        T _value;
    };

    template <typename T, int64_t n>
    class ParameterSet {
    public:
        explicit ParameterSet(std::array<T, n> array) {
            for (auto elem : array) {
                _set.insert(Parameter(elem));
            }
        }
        explicit ParameterSet(std::array<Parameter<T>, n> array) {
            for (auto elem : array) {
                _set.insert(elem);
            }
        }
        int64_t size() {
            return _set.size();
        }
    //protected:
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