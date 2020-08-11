///@author ***REMOVED***
///@date July 2020
///@version 0.1
///@file Parameter.i.h

#pragma once

namespace parameter {

template <typename T>
bool Parameter<T>::operator==(const Parameter<T> &other) const {
  return _value == other._value;
}

template <typename T> T Parameter<T>::value() const noexcept { return _value; }

template <typename T> int64_t ParameterSet<T>::size() const noexcept {
  return _set.size();
}

template <typename T>
std::unordered_set<Parameter<T>> ParameterSet<T>::values() const noexcept {
  return _set;
}
} // namespace parameter

namespace std {

template <typename T> struct hash<Parameter<T>> {
  std::size_t operator()(Parameter<T> const &s) const noexcept {
    return std::hash<T>()(s.value());
  }
};
} // namespace std