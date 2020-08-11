///@author ***REMOVED***
///@date August 2020
///@version 0.1
///@file Instance.i.h
///@brief Implementation of the Instance and LabeledInstance classes
#pragma once

namespace input {
template <typename T> T Instance<T>::factor(int64_t index) const {
  return _arr[index];
}

template <typename T> int64_t Instance<T>::dimensions() const {
  return _arr.size();
}

template <typename T> double Instance<T>::euclidean(const Instance<T> &other) {
  static_assert(std::is_arithmetic<T>());
  assert(other.dimensions() == dimensions());
  double eu{0};
  for (int i{}; i < other.dimensions(); i++) {
    eu += pow(other.factor(i) - factor(i), 2);
  }
  return sqrt(eu);
}

template <typename T, typename Q> Q LabeledInstance<T, Q>::label() const {
  return _label;
}

template <typename T, typename Q>
Instance<T> LabeledInstance<T, Q>::instance() const {
  return Instance<T>(this->_arr);
}
} // namespace input