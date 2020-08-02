///@author ***REMOVED***
///@date July 2020
///@version 0.1
///@file KNearestNeighbors.h

#pragma once

#include "Input/Instance.h"    //Instance
#include "Input/Sample.h"      //Sample
#include "Learner/Learner.h"   //Learner
#include "Learner/Parameter.h" //Parameter
#include "Loss/LossFunction.h" //LossFunction, ZeroOneLoss

#include <cassert>     //assert, static_assert
#include <cstdint>     //int64_t, uint64_t
#include <memory>      //unique_ptr
#include <queue>       //priority_queue
#include <type_traits> //is_arithmetic
#include <vector>      //vector

///@brief Namespace containing the K nearest neighbor algorithm
namespace knearest {
using namespace learner;
using namespace std;
///@param T The type of the elements making up the instances of the samples used
/// by the learner
///@param Q The type of the labels of the instances
///@brief K-Nearest Neighbors algorithm implementation
template <typename T, typename Q>
class KNearestNeighbors : public Learner<T, Q, uint> {
public:
  KNearestNeighbors() = default;
  ///@param k The hyperparameter that fixes the number of instances (based on
  /// distances) consulted to predict the class of an input instance
  explicit KNearestNeighbors(uint k) : _k(Parameter<uint>(k)) {
    static_assert(std::is_arithmetic<T>());
  };
  ~KNearestNeighbors() override = default;
  ///@param sample A sample of LabeledInstances whose datapoints are of type T
  /// and their label of type Q
  ///@param param Integer encoding *k*, which is the number of instances (the
  /// closest ones) whose labels are used to classify an input instance
  ///@brief Simply sets up the class' instance, no calculations are done at this
  /// stage
  void train(const Sample<T, Q> &sample, Parameter<uint> param) override {
    this->_sample = sample; // copy the sample
    this->_k = param;
  }
  ///@param sample A sample of LabeledInstances whose datapoints are of type T
  /// and their label of type Q
  ///@brief The same as calling the other *train* method with the same sample
  /// and the previously passed parameter *k* (in the constructor)
  void train(const Sample<T, Q> &sample) override {
    assert(this->_k.value());
    train(sample, this->_k);
  }
  ///@return The parameter *k*, the number of instances who votes for the
  /// prediciton
  ///@brief Simply returns the parameter *k*
  Parameter<uint> hyperparameter() const override { return this->_k; }
  ///@param input An instance of type T (vector of elements of type T)
  ///@return The label predicted for the passed instance
  Q predict(Instance<T> input) const override {
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
        pq.push(pair_dq(input.euclidean(this->_sample[i]),
                        this->_sample[i].label()));
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
      for (uint64_t i = 0; i < arr.size()-1; i++) {
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
  ///@return Unique_ptr to the loss function used for the purpose of multiclass
  /// classification for this algorithm
  /// (0-1 loss)
  std::unique_ptr<loss::LossFunction<T, Q>> lossFunction() const override {
    return std::unique_ptr<loss::LossFunction<T, Q>>(
        new loss::ZeroOneLoss<T, Q>);
  }

private:
  Parameter<uint> _k;
  Sample<T, Q> _sample{};
};
} // namespace knearest