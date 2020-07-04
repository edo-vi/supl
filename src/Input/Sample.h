//@author: ***REMOVED***
//@Date: June 2020
//@Version: 0.1
//@File: Definition of the Sample class and its children
#pragma once

#include "Instance.h" // LabeledInstance
#include "../../deps/rapidcsv.h" //Document, labelParams, GetRowCount, GetColumnCount, GetCell

#include <random> //rand, srand
#include <vector>


namespace sample {
    using namespace input;

    template<typename T, typename Q>
    class Sample {
    public:
        Sample() = default;
        explicit Sample(const std::vector<LabeledInstance<T, Q>>& s) : _arr(s) {}
        explicit Sample(const Sample<T, Q>& sample) :
                _arr(sample._arr)
                {}
        int64_t size() const {
            return int64_t{_arr.size()};
        };
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
        LabeledInstance<T, Q> operator[](int64_t index) const {
            return _arr[index];
        }
        LabeledInstance<T, Q> begin() {
            return _arr.begin();
        }
        LabeledInstance<T, Q> end() {
            return _arr.end();
        }
    protected:
        std::vector<LabeledInstance<T, Q>> _arr;

    private:
        std::random_device _rdev{};
        std::mt19937 _gen{_rdev()};
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
                _s(s)
        {assert(_s < k && _s >= 0);}

        std::pair<std::vector<LabeledInstance<T, Q>>, std::vector<LabeledInstance<T, Q>>> trainingAndValidation() {
            auto training = std::vector<input::LabeledInstance<T, Q>>();
            auto validation = std::vector<input::LabeledInstance<T, Q>>();
            auto start_point = _s * this->_num;
            int64_t end_point = start_point + this->_num;
            if (end_point >= this->_sample.size()) {
                end_point = this->_sample.size()-1;
            }

            for (int64_t i = 0; i < this->_sample.size(); i++) {
                if (i >= start_point && i < end_point) {
                    validation.push_back(this->_sample[i]);
                } else {
                    training.push_back(this->_sample[i]);
                };
            }
            return std::pair<std::vector<LabeledInstance<T, Q>>, std::vector<LabeledInstance<T, Q>>>{training, validation};
        };

    private:
        int _s{};

    };
};