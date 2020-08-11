///@author EZ
///@date August 2020
///@version 0.1
///@file CrossValidation.i.h Implementation of the function crossValidate
#pragma once

namespace crossvalidation {

template <int k>
template <typename T, typename Q, typename P>
Parameter<P> CrossValidation<k>::crossValidate(Learner<T, Q, P> &learner,
                                               const ParameterSet<P> &paramset,
                                               const Sample<T, Q> &sample) {
  double min{+INFINITY};
  Parameter<P> p{};
  for (auto s : paramset.values()) {
    double avgerror{0};
    for (int i = 0; i < k; i++) {
      SlicedSettedSample<T, Q, k> setted = SlicedSample<T, Q, k>(sample).set(i);
      const auto training = setted.trainingSet();
      const auto validation = setted.validationSet();
      learner.train(training, s);
      avgerror += learner.test(validation);
    }
    avgerror /= k;
    if (avgerror < min) {
      min = avgerror;
      p = s;
    }
  }
  return p;
}
} // namespace crossvalidation