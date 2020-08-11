///@author ***REMOVED***
///@date August 2020
///@version 0.1
///@file Learner.h
#pragma once

#include "Input/Instance.h"    //Instance
#include "Input/Sample.h"      //Sample
#include "Loss/LossFunction.h" //LossFunction
#include "Parameter.h"         //Parameter

#include <cstdint> //uint64_t
#include <cstdio>  //cout
#include <memory>  //unique_ptr

///@brief Namespace containing all the definitions and implementations related
/// to the abstract Learner interface
namespace learner {
using namespace sample;
using namespace parameter;
///@param T The type of the elements making up the instances of the samples used
/// by the learner
///@param Q The type of the labels of the instances
///@param P The type of the parameter of the learner
///@brief Abstract learner interface, inherited by all
/// classification/regression-based algorithms
template <typename T, typename Q, typename P> class Learner {
public:
  virtual ~Learner() = 0;
  ///@param sample A sample of LabeledInstances whose datapoints are of type T
  /// and their label of type Q
  ///@param param An (hyper)parameter, used in the training and/or labeling
  /// phases
  ///@brief Trains the learner on the passed sample based on the hyperparameter,
  /// possibily changing its internal state
  virtual void train(const Sample<T, Q> &sample, Parameter<P> param) = 0;
  ///@param sample A sample of LabeledInstances whose datapoints are of type T
  /// and their label of type Q
  ///@brief The same as calling the other *train* method with the same sample
  /// and the previously passed parameter (in the constructor)
  virtual void train(const Sample<T, Q> &sample) = 0;
  ///@param sample A sample of LabeledInstances whose datapoints are of type T
  /// and their label of type Q
  ///@return A double representing the empirical risk on the sample
  ///@brief Test the learner on the passed sample and returns the empirical
  /// error
  double test(const Sample<T, Q> &sample) const;
  ///@param sample A sample of LabeledInstances whose datapoints are of type T
  /// and their label of type Q
  ///@return A double representing the empirical risk on the sample
  ///@brief Test the learner on the passed sample and returns the empirical
  /// error; same as the other method but with support for verbose output
  /// messages, showing the learner's decisions on the input test sample and its
  /// errors
  double test(const Sample<T, Q> &sample, bool verbose) const;
  ///@return The parameter of the learner
  ///@brief Simply returns the parameter of the learner
  virtual Parameter<P> hyperparameter() const = 0;
  ///@param input An instance of type T (vector of elements of type T)
  ///@return The label predicted for the passed instance
  virtual Q predict(Instance<T> input) const = 0;
  ///@return Unique_ptr to the loss function used by the learner
  virtual std::unique_ptr<loss::LossFunction<T, Q>> lossFunction() const = 0;
};

template <typename T, typename Q, typename P>
Learner<T, Q, P>::~Learner() = default;

} // namespace learner

#include "Learner.i.h"