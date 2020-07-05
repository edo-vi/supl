//
// Created by edoardo on 04/07/20.
//
#pragma once

#include "../Input/Sample.h"
#include "Parameter.h"

namespace learner {
    using namespace sample;
    using namespace parameter;

    template<typename T, typename Q>
    class Learner {
    public:
        virtual void train(const Sample<T, Q>& sample, Parameter<T> param) = 0;
        virtual double test(const Sample<T, Q>& sample) = 0;
        virtual Parameter<T> parameter() const = 0;
        virtual Q predict(Instance<T> input) = 0;
    };

    template<typename T, typename Q>
    class ConcreteLearner : public Learner<T, Q> {
        void train(const Sample<T, Q>& sample, Parameter<T> param) override {}
        double test(const Sample<T, Q>& sample) override {}
        virtual Parameter<T> parameter() const override {}
        virtual Q predict(Instance<T> input) override {};
    };
}