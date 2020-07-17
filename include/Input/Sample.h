///@file Sample.h
///@author: ***REMOVED***
///@Date: July 2020
///@Version: 0.1
///@File: Definition and implementation of Sample, ValidationSample, SlicedSample and SlicedSettedSample; it also contains
///the implementation of the function sampleFromCsv.
#pragma once

#include "Instance.h"               //LabeledInstance
#include "../../deps/rapidcsv.h"    //Document, labelParams, GetRowCount, GetColumnCount, GetCell

#include <random>       //random_device, mt19337
#include <cstdint>      //int64_t
#include <vector>       //vector
#include <cassert>      //assert
#include <algorithm>    //shuffle

///@brief Namespace containing all the definitions and implementations of classes representing samples of labeled
///datapoints (Sample), samples with defined disjoint subsets (SlicedSample), samples with defined disjoint subsets
///with one that is the currently ´selected' subset (SlicedSettedSample), union of samples representing a training
///sample and a test sample (ValidationSample)
namespace sample {
    using namespace input;

    template <typename T, typename Q>
    struct ValidationSample;
    ///@brief A sample, i.e. a sequence of labeled data points
    template<typename T, typename Q>
    class Sample {
    public:
        Sample() = default;
        ///@input s Variable-sized array of labeled instances whose datapoints are of type T and its labels of type Q
        explicit Sample(const std::vector<LabeledInstance<T, Q>>& s) : _arr(s) {}
        ///@input sample Another sample of the same type used to construct a copy
        Sample(const Sample<T, Q>& sample) :
                _arr(sample._arr)
                {}
        ///@return The size of the sample, i.e. the number of labeled instances wrapped by the sample instance
        ///@brief Returns the size of the sample
        int64_t size() const {
            return int64_t{_arr.size()};
        };
        /*
        LabeledInstance<T, Q> randomPoint() {
            std::uniform_int_distribution<unsigned long> distr(0, _arr.size());
            return _arr[distr(_gen)];
        };
        std::vector<LabeledInstance<T, Q>> randomPoints(int64_t n) {
            std::vector<LabeledInstance<T, Q>> v{};
            for (int64_t i = 0; i < n; i++) {
                v.push_back(randomPoint());
            }
            return v;
        };
        std::vector<LabeledInstance<T, Q>> randomPointsNoReplacement(int64_t n) {
            std::vector<LabeledInstance<T, Q>> v{};
            std::sample(_arr.begin(), _arr.end(), std::back_inserter(v), n, _gen);
            return v;
        };
        */
        ///@param index An integer representing the index of a LabeledInstance in the sequence wrapped by the Sample instance 
        ///@return The LabeledInstance whose index in the sequence is the same as the passed actual parameter
        ///@brief Get the LabeledInstance of the sample with index equal to the actual parameter
        LabeledInstance<T, Q> operator[](int64_t index) const {
            return _arr[index];
        }
        ///@return A LabeledInstance
        ///@brief Returns the first LabeledInstance in the sample
        LabeledInstance<T, Q> begin() {
            return _arr.begin();
        }
        ///@return A LabeledInstance
        ///@brief Returns the last LabeledInstance in the sample
        LabeledInstance<T, Q> end() {
            return _arr.end();
        }
        ///@param k A 64-bit integer indicating the size of the test sample 
        ///@return A validation sample, i.e. an union of two samples, the training sample and the test sample
        ///@brief Returns a validation sample with test sample of size k and training sample of size size()-k
        ValidationSample<T, Q> split(int64_t k) {
            assert (k < size());

            auto vs = ValidationSample<T, Q>();
            vs.test = Sample<T, Q>(std::vector<LabeledInstance<T, Q>>(_arr.begin(), _arr.begin() + k));
            vs.training = Sample<T, Q>(std::vector<LabeledInstance<T, Q>>(_arr.begin() + k, _arr.begin() + _arr.size() - 1));
            return vs;
        };
        ///@brief Randomly shuffle the sample
        void shuffle() {
            std::random_device rdev{};
            std::mt19937 gen{rdev()};
            std::shuffle(_arr.begin(), _arr.end(), gen);
        }
    protected:
        std::vector<LabeledInstance<T, Q>> _arr;

    //private:
        //std::random_device _rdev{};
        //std::mt19937 _gen{_rdev()};
    };
    ///@param filename String encoding the path of the CSV file that must be parsed
    ///@return A sample
    ///@brief Parse the CSV file with the given path and generates a sample from it. The file must have the
    ///following structure: there must be no header and no row header, values must be separated by a comma and 
    ///the label must be the last value of each row
    template <typename T, typename Q>
    Sample<T, Q> sampleFromCsv(const std::string& filename) {

        std::vector<LabeledInstance<T, Q>> inputs{};

        rapidcsv::Document doc(filename, rapidcsv::LabelParams(-1, -1));

        auto rows = doc.GetRowCount();
        auto columns = doc.GetColumnCount();

        for (int64_t i = 0; i < rows; i++) {
            T data[columns-1]{};

            int64_t j = 0;
            for (; j < columns-1; j++) {
                data[j] = doc.GetCell<T>(j,i);
            }

            Q label = doc.GetCell<Q>(j,i);
            inputs.push_back(LabeledInstance<T, Q>(data, columns-1, label));
        }
        return Sample<T, Q>(inputs);
    };

    template <typename T, typename Q, int k>
    class SlicedSettedSample;
    ///@brief A sample that has been `sliced' into k disjoint subsets
    template <typename T, typename Q, int k>
    class SlicedSample {
    public:
        SlicedSample() = default;
        ///@param sample The sample used to construct the SlicedSample
        explicit SlicedSample(const Sample<T, Q>& sample) :
        _sample(sample)
        {};
        ///@param s An integer indicating the index of the `set' subset
        ///@return A SlicedSettedSample whose `set' subset is the s-th one
        SlicedSettedSample<T, Q, k> set(int s) {
            return SlicedSettedSample<T, Q, k>(_sample, s);
        }

    protected:
        Sample<T, Q> _sample;
        int64_t _num = _sample.size() / k;
    };
    ///@brief A SlicedSample with a `set' subset. This is used for Cross-Validation
    template <typename T, typename Q, int k>
    class SlicedSettedSample : public SlicedSample<T, Q, k> {
    public:
        SlicedSettedSample() = default;
        ///@param sample The sample used to construct the SlicedSettedSample
        ///@param s An integer representing the index of the `set' subsets
        explicit SlicedSettedSample(const Sample<T, Q>& sample, int s) :
                SlicedSample<T, Q, k>{sample},
                _s(s) {
            assert(_s < k && _s >= 0);
            _startidx = s * this->_num;
            _endidx = s == k - 1 ? this->_sample.size()-1 : _startidx + this->_num - 1; //inclusive
        }
        ///@return A sample representing the training set
        ///@brief Returns the training set which is constructed by the union of all disjoint subsets that are not the `set' one
        sample::Sample<T, Q> trainingSet() {
            auto training = std::vector<input::LabeledInstance<T, Q>>();
            for (int64_t i = 0; i < this->_sample.size(); i++) {
                if (i < _startidx || i > _endidx) {
                    training.push_back(this->_sample[i]);
                };
            }
            return Sample<T, Q>(training);
        };
        ///@return A sample representing the validation set
        ///@brief Returns the validation set which is constructed as the `set' sample
        sample::Sample<T, Q> validationSet() {
            auto validation = std::vector<input::LabeledInstance<T, Q>>();

            for (int64_t i = 0; i < this->_sample.size(); i++) {
                if (i >= _startidx && i <= _endidx) {
                    validation.push_back(this->_sample[i]);
                }
            }
            return Sample<T, Q>(validation);
        };

    private:
        int _s{};
        int64_t _startidx{};
        int64_t _endidx{};

    };
    ///@brief Object aggregating a training set and a test set 
    template <typename T, typename Q>
    struct ValidationSample {
        Sample<T, Q> training;
        Sample<T, Q> test;
    };
};
