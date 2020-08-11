///@author EZ
///@date August 2020
///@version 0.1
///@file LossFunction.i.h
#pragma once

namespace loss {

template <typename T, typename Q>
double LossFunction<T, Q>::loss(const LabeledInstance<T, Q> &xy, const Q &hx) {
  return loss(xy.label(), hx);
};

template <typename T, typename Q> LossFunction<T, Q>::~LossFunction() = default;

template <typename T, typename Q>
double ZeroOneLoss<T, Q>::loss(const Q &y, const Q &hx) {
  return (y == hx) ? 0 : 1;
};

template <typename T, typename Q>
double SquaredLoss<T, Q>::loss(const Q &y, const Q &hx) {
  static_assert(std::is_arithmetic<Q>());
  return pow((y - hx), 2);
};
} // namespace loss