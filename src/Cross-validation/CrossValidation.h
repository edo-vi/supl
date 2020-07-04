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

    template<typename T, typename Q, typename P, int p, int k>
    Parameter<T> crossValidate(const Learner<T, Q>& learner, const ParameterSet<P, p>& paramset, const Sample<T, Q>& sample) {
        for (auto s : paramset.values()) {
            for (int i = 0; i < k; i++) {
                auto setted = SlicedSample<T, Q, k>(sample).set(i);
                auto pair = setted.trainingAndValidation();
                auto tot = pair.first.size() + pair.second.size();

            }
        }

    };
}