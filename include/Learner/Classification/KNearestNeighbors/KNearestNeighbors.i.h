///@author ***REMOVED***
///@date August 2020
///@version 0.1
///@file KNearestNeighbors.i.h
///@brief Declaration of the KNearestNeighbors class

#pragma once

namespace knearest {

template <typename T, typename Q>
void KNearestNeighbors<T, Q>::train(const Sample<T, Q> &sample,
                                    Parameter<uint> param) {
  this->_sample = sample; // copy the sample
  this->_k = param;
}

template <typename T, typename Q>
void KNearestNeighbors<T, Q>::train(const Sample<T, Q> &sample) {
  assert(this->_k.value());
  train(sample, this->_k);
}

template <typename T, typename Q>
Parameter<uint> KNearestNeighbors<T, Q>::hyperparameter() const {
  return this->_k;
}

template <typename T, typename Q>
Q KNearestNeighbors<T, Q>::predict(Instance<T> input) const {
  using pair_dq = pair<double, Q>;

  // not a great problem the comparison between floats here, because
  // even if there are rounding errors that influence the result
  // they are basically the same, so it doesn't matter a lot which one is
  // included
  auto compare = [](pair_dq lhs, pair_dq rhs) -> bool {
    return lhs.first < rhs.first;
  };
  std::priority_queue<pair_dq, std::vector<pair_dq>, decltype(compare)> pq(
      compare);

  for (uint64_t i = 0; i < this->_sample.size(); i++) {
    if (i < this->_k.value())
      pq.push(
          pair_dq(input.euclidean(this->_sample[i]), this->_sample[i].label()));
    else {
      auto d = input.euclidean(this->_sample[i]);
      if (d < pq.top().first) {
        pq.pop();
        pq.push(pair_dq(d, this->_sample[i].label()));
      }
    }
  }

  std::vector<Q> arr{};
  while (!pq.empty()) {
    arr.push_back(pq.top().second);
    pq.pop();
  }
  std::sort(arr.begin(), arr.end());

  Q lab{arr[0]};
  float max{-INFINITY};
  int count{1};
  if (arr.size() > 1) {
    for (uint64_t i = 0; i < arr.size() - 1; i++) {
      if (arr[i] == arr[i + 1]) {
        count++;
      } else {
        if (count > max) {
          lab = arr[i];
          max = count;
        }
        count = 1;
      }
    }
  }
  return lab;
}

template <typename T, typename Q>
std::unique_ptr<loss::LossFunction<T, Q>>
KNearestNeighbors<T, Q>::lossFunction() const {
  return std::unique_ptr<loss::LossFunction<T, Q>>(new loss::ZeroOneLoss<T, Q>);
}
}; // namespace knearest
