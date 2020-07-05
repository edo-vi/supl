//
// Created by edoardo on 04/07/20.
//
#pragma once

#include "../Input/Sample.h"
#include "Parameter.h"
#include "../Loss/LossFunction.h"

#include <memory> //unique_ptr

namespace learner {
    using namespace sample;
    using namespace parameter;

    template<typename T, typename Q>
    class Learner {
    public:
        virtual ~Learner() = 0;
        virtual void train(const Sample<T, Q>& sample, Parameter<T> param) = 0;
        virtual double test(const Sample<T, Q>& sample) const {
            auto l = lossFunction();
            double v{};
            for (int64_t i = 0; i < sample.size(); i++) {
                v += l->loss(sample[i].instance(), sample[i].label(), predict(sample[i]));
            }
            return v;

        };
        virtual Parameter<T> parameter() const = 0;
        virtual Q predict(Instance<T> input) const = 0;
        virtual std::unique_ptr<loss::LossFunction<T, Q>> lossFunction() const = 0;
    };

    template <typename T, typename Q>
    Learner<T, Q>::~Learner() {}

    template<typename T, typename Q>
    class ConcreteLearner : public Learner<T, Q> {
    public:
        ~ConcreteLearner<T, Q>() override = default;
        void train(const Sample<T, Q>& sample, Parameter<T> param) override {}
        [[nodiscard]]

        Parameter<T> parameter() const override {}
        Q predict(Instance<T> input) const override {
            return "ciao";
        };
        std::unique_ptr<loss::LossFunction<T, Q>> lossFunction() const {
            return std::unique_ptr<loss::LossFunction<T, Q>>(new loss::ZeroOneLoss<T, Q>);
        }
    };
}