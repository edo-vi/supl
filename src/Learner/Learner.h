//
// Created by edoardo on 04/07/20.
//
#pragma once

#include "../Input/Sample.h"

namespace learner {
    using namespace sample;

    template<typename T, typename Q>
    class Learner {
    public:
        virtual void train(const Sample<T, Q>& sample) = 0;
    };

    template<typename T, typename Q>
    class ConcreteLearner : public Learner<T, Q> {
        void train(const Sample<T, Q>& sample) override {}
    };
}