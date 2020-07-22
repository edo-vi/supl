///@author ***REMOVED***
///@date June 2020
///@version 0.1
///@file Instance.h
#pragma once

#include <cassert>     //assert
#include <cmath>       //sqrt
#include <type_traits> //is_arithmetic
#include <vector>      //vector

///@brief Namespace including all the definitions and implementations related to
///instances (input points) and labeled instances
namespace input {
///@param T The type of the elements making up the instance
///@brief An instance, i.e. a data point from the instance set. Always a vector
///whose elements are of type T
template <typename T> class Instance {
public:
  Instance() = default;
  ///@param input A variable-length vector of type T used to construct the
  ///Instance class instance
  explicit Instance(const std::vector<T> &input) : _arr(input) {}
  ///@param input A fixed-length array of type T
  ///@param size A 64-bit integer indicating the size of passed array
  ///@brief Construct the Instance from the elements of the array
  Instance(T input[], int64_t size) {
    for (int64_t i = 0; i < size; i++) {
      _arr.push_back(input[i]);
    }
  }
  ///@param index A 64-bit integer indicating the index of a factor of the data
  ///point vector
  ///@return A value of type T
  ///@brief Returns the index-th factor of the instance vector
  T factor(int64_t index) const { return _arr[index]; }
  ///@return A 64-bit integer
  ///@brief Returns the dimension of the instance vector
  int64_t dimensions() const { return _arr.size(); }
  ///@param other An instance of the same type (which must be arithmetic)
  ///@return A double representing the distance between this Instance and the
  ///other Instance
  ///@brief Returns the euclidean distance (2-norm of the difference) between
  ///this Instance and the passed Instance. Both must be of arithmetic type
  double euclidean(const Instance<T> &other) {
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
///@param T The type of the elements making up the instance
///@param Q The type of the label that tags the instance
///@brief An instance tagged with a label. An element used to construct a
///sample.
template <typename T, typename Q> class LabeledInstance : public Instance<T> {
public:
  LabeledInstance() = default;
  ///@param input A variable-length vector of type T used to construct the
  ///LabeledInstance class instance
  ///@param label The label for the to-be-constructed LabeledInstance
  LabeledInstance(const std::vector<T> &input, Q label)
      : Instance<T>(input), _label(label) {}
  ///@param input A fixed-length array of type T
  ///@param size A 64-bit integer indicating the size of passed array
  ///@label The label for the to-be-constructed LabeledInstance
  ///@brief Construct the LabeledInstance from the elements of the array and
  ///tags it with label
  LabeledInstance(T input[], int64_t size, Q label)
      : Instance<T>(input, size), _label(label) {}
  ///@return A value of type Q
  ///@brief Returns the label of the instance
  Q label() const { return _label; }
  ///@return An instance of type T
  ///@brief Returns the underline Instance
  Instance<T> instance() const { return Instance<T>(this->_arr); }

protected:
  Q _label;
};

} // namespace input
