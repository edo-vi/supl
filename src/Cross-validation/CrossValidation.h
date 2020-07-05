//
// Created by edoardo on 04/07/20.
//
#pragma once

#include "../Learner/Parameter.h"
#include "../Learner/Learner.h"
#include "../Input/Sample.h"

namespace crossvalidation {
    using namespace parameter;
    using namespace learner;

    template<typename T, typename Q, typename P, int k>
    Parameter<T> crossValidate(Learner<T, Q>& learner, const ParameterSet<P>& paramset, const Sample<T, Q>& sample) {
        double min{+INFINITY};
        Parameter<T> p{};
        for (auto s : paramset.values()) {
            double avgerror{0};
            for (int i = 0; i < k; i++) {
                auto setted = SlicedSample<T, Q, k>(sample).set(i);
                const auto training = setted.trainingSet();
                const auto validation = setted.validationSet();
                learner.train(training, s);
                avgerror += learner.test(validation);
            }
            if (avgerror/double{k} < min) {
                min = avgerror;
                p = s;
            }
        }
        return p;
    };
}