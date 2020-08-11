///@author ***REMOVED***
///@date July 2020
///@version 0.1
///@file Parameter.h

#pragma once

#include <unordered_set> //unordered_set
#include <vector>        //vector

///@brief Namespace including the definitions and implementations of all classes
/// related to parameters, parameter spaces, parameter sets etc.
namespace parameter {
///@param T The type of the values in the parameter space
///@brief A generic parameter space, set where a certain parameter lives (i.e.
/// can take values)
template <typename T> class ParameterSpace {
public:
  virtual T min() = 0;
  virtual T max() = 0;
  virtual ~ParameterSpace();
};

///@param P The type of the value `wrapped' by the parameter
///@brief A (hyper)parameter, i.e. a parameter that is passed to a learner and
/// that influences its training and prediction phases
template <typename T> class Parameter {
public:
  Parameter() = default;
  ///@param value The value of the parameter
  explicit Parameter(const T &value) : _value(value) {}
  bool operator==(const Parameter<T> &other) const;
  ///@return The value of the parameter
  T value() const noexcept;

private:
  T _value;
};
///@param T The type of the values in the parameter set
///@brief A fixed set of parameters, to be used for iterating on a subset of a
/// certain parameter space
template <typename T> class ParameterSet {
public:
  ///@param array A fix-sized array of values of type T
  ///@param size The size of the passed array
  explicit ParameterSet(const T array[], int64_t size) {
    for (int64_t i = 0; i < size; i++) {
      _set.insert(Parameter(array[i]));
    }
  }
  ///@param array A fix-sized array of Parameters of type T
  ///@param size The size of the passed array
  explicit ParameterSet(const Parameter<T> array[], int64_t size) {
    for (int64_t i = 0; i < size; i++) {
      _set.insert(Parameter(array[i]));
    }
  }
  ///@param array A variable-sized vector of values of type T
  explicit ParameterSet(const std::vector<T> &array) {
    for (auto elem : array) {
      _set.insert(Parameter(elem));
    }
  }
  ///@param array A variable-sized vector of Parameters of type T
  explicit ParameterSet(const std::vector<Parameter<T>> &array) {
    for (auto elem : array) {
      _set.insert(elem);
    }
  }
  ///@return The size of the set
  [[nodiscard]] int64_t size() const noexcept;
  ///@return An unordered set containing all the Parameters included in the set
  ///@brief Can be use to iterate over the Parameters `wrapped' by the set
  std::unordered_set<Parameter<T>> values() const noexcept;

private:
  std::unordered_set<Parameter<T>> _set{};
};

} // namespace parameter

namespace std {
using namespace parameter;
///@param T The type of the value `wrapped' by the parameter
///@brief Implementation of the hash function for a Parameter of type T
///(necessary for having an unordered set of Parameters)
template <typename T> struct hash<Parameter<T>>;
} // namespace std

#include "Parameter.i.h"
