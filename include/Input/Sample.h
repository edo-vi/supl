//@author: ***REMOVED***
//@Date: July 2020
//@Version: 0.1
//@File: Definition and implementation of Sample, ValidationSample, SlicedSample and SlicedSettedSample; it also contains
//       the implementation of the function sampleFromCsv.
#pragma once

#include "Instance.h"               //LabeledInstance
#include "../../deps/rapidcsv.h"    //Document, labelParams, GetRowCount, GetColumnCount, GetCell

#include <random>       //random_device, mt19337
#include <cstdint>      //int64_t
#include <vector>       //vector
#include <cassert>      //assert
#include <algorithm>    //shuffle

namespace sample {
    using namespace input;

    template <typename T, typename Q>
    struct ValidationSample;

    template<typename T, typename Q>
    class Sample {
    public:
        Sample() = default;
        explicit Sample(const std::vector<LabeledInstance<T, Q>>& s) : _arr(s) {}
        Sample(const Sample<T, Q>& sample) :
                _arr(sample._arr)
                {}
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
        LabeledInstance<T, Q> operator[](int64_t index) const {
            return _arr[index];
        }
        LabeledInstance<T, Q> begin() {
            return _arr.begin();
        }
        LabeledInstance<T, Q> end() {
            return _arr.end();
        }
        ValidationSample<T, Q> split(int64_t k) {
            assert (k < size());

            auto vs = ValidationSample<T, Q>();
            vs.test = Sample<T, Q>(std::vector<LabeledInstance<T, Q>>(_arr.begin(), _arr.begin() + k));
            vs.training = Sample<T, Q>(std::vector<LabeledInstance<T, Q>>(_arr.begin() + k, _arr.begin() + _arr.size() - 1));
            return vs;
        };
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

    template <typename T, typename Q, int k>
    class SlicedSample {
    public:
        SlicedSample() = default;
        explicit SlicedSample(const Sample<T, Q>& sample) :
        _sample(sample)
        {};
        SlicedSettedSample<T, Q, k> set(int s) {
            return SlicedSettedSample<T, Q, k>(_sample, s);
        }

    protected:
        Sample<T, Q> _sample;
        int64_t _num = _sample.size() / k;
    };

    template <typename T, typename Q, int k>
    class SlicedSettedSample : public SlicedSample<T, Q, k> {
    public:
        SlicedSettedSample() = default;
        explicit SlicedSettedSample(const Sample<T, Q>& sample, int s) :
                SlicedSample<T, Q, k>{sample},
                _s(s) {
            assert(_s < k && _s >= 0);
            _startidx = s * this->_num;
            _endidx = s == k - 1 ? this->_sample.size()-1 : _startidx + this->_num - 1; //inclusive
        }

        sample::Sample<T, Q> trainingSet() {
            auto training = std::vector<input::LabeledInstance<T, Q>>();
            for (int64_t i = 0; i < this->_sample.size(); i++) {
                if (i < _startidx || i > _endidx) {
                    training.push_back(this->_sample[i]);
                };
            }
            return Sample<T, Q>(training);
        };

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

    template <typename T, typename Q>
    struct ValidationSample {
        Sample<T, Q> training;
        Sample<T, Q> test;
    };
};