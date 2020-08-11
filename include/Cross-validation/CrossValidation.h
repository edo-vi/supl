///@author EZ
///@date August 2020
///@version 0.1
///@file CrossValidation.h Definition of the function crossValidate
#pragma once

#include "../Input/Sample.h"      //Sample, SlicedSettedSample
#include "../Learner/Learner.h"   //Learner
#include "../Learner/Parameter.h" //Parameter, ParameterSet

///@brief Namespace containing all those definitions/implementations related to
/// cross-validation
namespace crossvalidation {
using namespace parameter;
using namespace learner;
///@param k The number of disjoint subsets in which the sample is divided
///@brief Object containing the necessary functions/variables necessary to
/// crossvalidate models
template <int k> class CrossValidation {
public:
  CrossValidation() = default;
  ///@param T The type of the instances (data vectors)
  ///@param Q The type of the labels
  ///@param P The type of the parameters of the learner
  ///@param learner A Learner that will train and validate on the sample
  ///@param paramset A ParameterSet whose elements are used with the learner to
  /// calculate its error on the validation sample and from which the `best'
  /// parameter is chosen
  ///@param sample The sample used to cross-validate the learner
  ///@return The `best' parameter among those in the ParameterSet, that is, the
  /// one with the lowest average error
  ///@brief Cross-validates the learner on the passed sample by testing all the
  /// parameters in the parameter set
  template <typename T, typename Q, typename P>
  static Parameter<P> crossValidate(Learner<T, Q, P> &learner,
                                    const ParameterSet<P> &paramset,
                                    const Sample<T, Q> &sample);
};

} // namespace crossvalidation

#include "CrossValidation.i.h"