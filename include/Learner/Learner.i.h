///@author ***REMOVED***
///@date August 2020
///@version 0.1
///@file Learner.i.h
#pragma once

namespace learner {

template <typename T, typename Q, typename P>
double Learner<T, Q, P>::test(const Sample<T, Q> &sample) const {
  auto l = lossFunction();
  double v{};
  for (uint64_t i = 0; i < sample.size(); i++) {
    auto samplepoint = sample[i];
    v += l->loss(samplepoint.label(), predict(samplepoint));
  }
  return v / sample.size();
};

template <typename T, typename Q, typename P>
double Learner<T, Q, P>::test(const Sample<T, Q> &sample, bool verbose) const {
  if (!verbose)
    return test(sample);
  auto l = lossFunction();
  double v{};
  std::cout << "label\tprediction\n";
  for (uint64_t i = 0; i < sample.size(); i++) {
    auto samplepoint = sample[i];
    auto instance = samplepoint.instance();
    auto label = samplepoint.label();
    auto prediction = predict(samplepoint);
    v += l->loss(label, prediction);
    std::string final = "";
    if constexpr (std::is_same<Q, std::string>::value) {
      final += label + "\t" + prediction;
    } else {
      final += std::to_string(label) + "\t" + std::to_string(prediction);
    }
    if (label == prediction)
      final += "\n";
    else
      final += " <- ERROR\n";
    std::cout << final;
  }
  return v / sample.size();
};
} // namespace learner