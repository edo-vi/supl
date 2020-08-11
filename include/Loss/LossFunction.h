///@author ***REMOVED***
///@date August 2020
///@version 0.1
///@file LossFunction.h
#pragma once

#include "Input/Instance.h" //Instance, LabeledInstance

#include <cmath>       //pow
#include <type_traits> //is_arithmetic

///@brief Namespace containing all the definitions and implementations of loss
/// functions to be used in the training/testing phases
namespace loss {
using namespace input;
///@param T The type of the instances
///@param Q The type of the labels of the instances
///@brief Abstract interface representing a loss function
template <typename T, typename Q> class LossFunction {
public:
  LossFunction() = default;
  virtual ~LossFunction() = 0;
  /*
  ///@param x An instance
  ///@param y The label of the instance
  ///@param hx The prediction of a learner on the instance x
  ///@return A double representing the error made by the learner, predicting hx,
  on x which has label y
  [[nodiscard]]
  virtual double loss(const Instance<T>& x, const Q& y, const Q& hx) = 0;
  */

  ///@param y The label of the instance
  ///@param hx The prediction of a learner on the instance x
  ///@return A double representing the error made by the learner, predicting hx,
  /// on x which has label y
  [[nodiscard]] virtual double loss(const Q &y, const Q &hx) = 0;

  /*
  ///@param xy A LabeledInstance representing an instance with its `correct'
  label
  ///@param hx The prediction of a learner on the instance x
  ///@return A double representing the error made by the learner, predicting hx,
  on xy which is `correctly' labeled
  [[nodiscard]]
  virtual double loss(const LabeledInstance<T, Q>& xy, const Q& hx) {
      return loss(xy.instance(), xy.label(), hx);
  };
  */

  ///@param xy A LabeledInstance representing an instance with its `correct'
  /// label
  ///@param hx The prediction of a learner on the instance x
  ///@return A double representing the error made by the learner, predicting hx,
  /// on xy which is `correctly' labeled
  [[nodiscard]] virtual double loss(const LabeledInstance<T, Q> &xy,
                                    const Q &hx);
};

///@param T The type of the instances
///@param Q The type of the labels of the instances
///@brief The 0-1 loss, a concrete implementation of the abstract Loss function
/// interface
template <typename T, typename Q>
class ZeroOneLoss : public LossFunction<T, Q> {
public:
  ~ZeroOneLoss() override = default;
  ///@param y The label of the instance
  ///@param hx The prediction of a learner on the instance x
  ///@return Zero if the label y is the same as the prediction hx, one otherwise
  double loss(const Q &y, const Q &hx) override;
};

///@param T The type of the instances
///@param Q The type of the labels of the instances
///@brief The squared loss, a concrete implementation of the abstract Loss
/// function interface
template <typename T, typename Q>
class SquaredLoss : public LossFunction<T, Q> {
public:
  ///@param y The label of the instance
  ///@param hx The prediction of a learner on the instance x
  ///@return The squared difference between the label y and the prediction hx
  double loss(const Q &y, const Q &hx) override;
  ~SquaredLoss() override = default;
};
} // namespace loss

#include "LossFunction.i.h"