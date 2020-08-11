///@author ***REMOVED***
///@date August 2020
///@version 0.1
///@file KNearestNeighbors.h
///@brief Declaration of the KNearestNeighbors class that implements the named
///algorithm

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
  void train(const Sample<T, Q> &sample, Parameter<uint> param) override;
  ///@param sample A sample of LabeledInstances whose datapoints are of type T
  /// and their label of type Q
  ///@brief The same as calling the other *train* method with the same sample
  /// and the previously passed parameter *k* (in the constructor)
  void train(const Sample<T, Q> &sample) override;
  ///@return The parameter *k*, the number of instances who votes for the
  /// prediciton
  ///@brief Simply returns the parameter *k*
  [[nodiscard]] Parameter<uint> hyperparameter() const override;
  ///@param input An instance of type T (vector of elements of type T)
  ///@return The label predicted for the passed instance
  Q predict(Instance<T> input) const override;
  ///@return Unique_ptr to the loss function used for the purpose of multiclass
  /// classification for this algorithm
  /// (0-1 loss)
  std::unique_ptr<loss::LossFunction<T, Q>> lossFunction() const override;

private:
  Parameter<uint> _k;
  Sample<T, Q> _sample{};
};
} // namespace knearest

#include "KNearestNeighbors.i.h"