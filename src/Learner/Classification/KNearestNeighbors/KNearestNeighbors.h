//@author: ***REMOVED***
//@Date: July 2020
//@Version: 0.1
//@File: Definition and implementation of the K Nearest Neighbors learner, concrete implementation of Learner
#pragma once

#include "../../Learner.h"              //Learner
#include "../../../Loss/LossFunction.h" //LossFunction
#include "../../../Input/Sample.h"      //Sample
#include "../../../Input/Instance.h"    //Parameter

#include <queue>       //priority_queue
#include <type_traits> //is_arithmetic
#include <cassert>     //assert


namespace knearest {
    using namespace learner;
    using namespace std;

    template <typename T, typename Q>
    class KNearestNeighbors : public Learner<T, Q, int> {
    public:
        KNearestNeighbors() = default;
        explicit KNearestNeighbors(int k) : _k(Parameter<int>(k)) {
            static_assert(std::is_arithmetic<T>());
        };
        ~KNearestNeighbors() override = default;

        void train(const Sample<T, Q> &sample, Parameter<int> param) override {
            this->_sample = sample; //copy the sample
            this->_k = param;
        }
        void train(const Sample<T, Q> &sample) override {
            assert(this->_k.value());
            train(sample, this->_k);
        }

        Parameter<int> hyperparameter() const override {
            return this->_k;
        }

        Q predict(Instance<T> input) const override {
            using pair_dq = pair<double, Q>;
            auto compare = [](pair_dq lhs, pair_dq rhs) -> bool {
                return lhs.first < rhs.first;
            };
            std::priority_queue<pair_dq, std::vector<pair_dq>, decltype(compare)> pq(compare);

            for (int64_t i = 0; i < this->_sample.size(); i++) {
                if (i < this->_k.value()) pq.push(pair_dq(input.euclidean(this->_sample[i]), this->_sample[i].label()));
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
            for (auto i = 0; i < arr.size(); i++) {
                if (arr[i] == arr[i+1]) {
                    count++;
                }
                else {
                    if (count > max) {
                        lab = arr[i];
                        max = count;
                    }
                    count = 1;
                }
            }
            return lab;
        }

        std::unique_ptr<loss::LossFunction<T, Q>> lossFunction() const override {
            return std::unique_ptr<loss::LossFunction<T, Q>>(new loss::ZeroOneLoss<T, Q>);
        }
    private:
        Parameter<int> _k;
        Sample<T, Q> _sample{};
    };
}