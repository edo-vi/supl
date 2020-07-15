///@file Learner.h
///@author: ***REMOVED***
///@Date: July 2020
///@Version: 0.1
///@File: Definition and implementation of the interface Learner
#pragma once

#include "Input/Sample.h"        //Sample
#include "Parameter.h"           //Parameter
#include "Loss/LossFunction.h"   //LossFunction
#include "Input/Instance.h"      //Instance

#include <memory>       //unique_ptr
#include <cstdio>       //cout

namespace learner {
    using namespace sample;
    using namespace parameter;

    template<typename T, typename Q, typename P>
    class Learner {
    public:
        virtual ~Learner() = 0;
        virtual void train(const Sample<T, Q>& sample, Parameter<P> param) = 0;
        virtual void train(const Sample<T, Q> &sample) = 0;
        double test(const Sample<T, Q>& sample) const {
            auto l = lossFunction();
            double v{};
            for (int64_t i = 0; i < sample.size(); i++) {
                auto samplepoint = sample[i];
                v += l->loss(samplepoint.instance(), samplepoint.label(), predict(samplepoint));
            }
            return v/sample.size();
        };

        double test(const Sample<T, Q>& sample, bool verbose) const {
            if (!verbose) return test(sample);
            auto l = lossFunction();
            double v{};
            std::cout << "label\tprediction\n";
            for (int64_t i = 0; i < sample.size(); i++) {
                auto samplepoint = sample[i];
                auto instance = samplepoint.instance();
                auto label = samplepoint.label();
                auto prediction = predict(samplepoint);
                v += l->loss(instance, label, prediction);
                std::string final = "";
                if constexpr(std::is_same<Q, std::string>::value) {
                    final += label + "\t" + prediction;
                }
                else {
                    final += std::to_string(label) + "\t" + std::to_string(prediction);
                }
                if (label == prediction) final += "\n";
                else final +=  " <- ERROR\n";
                std::cout << final;
            }
            return v / sample.size();
        };

        virtual Parameter<P> hyperparameter() const = 0;
        virtual Q predict(Instance<T> input) const = 0;
        virtual std::unique_ptr<loss::LossFunction<T, Q>> lossFunction() const = 0;
    };


    template <typename T, typename Q, typename P>
    Learner<T, Q, P>::~Learner() = default;

}