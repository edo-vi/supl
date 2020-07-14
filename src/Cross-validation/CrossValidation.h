//@author: ***REMOVED***
//@Date: July 2020
//@Version: 0.1
//@File: Definition and implementation of the function crossValidate
#pragma once

#include "../Learner/Parameter.h" //Parameter, ParameterSet
#include "../Learner/Learner.h"   //Learner
#include "../Input/Sample.h"      //Sample, SlicedSettedSample

namespace crossvalidation {
    using namespace parameter;
    using namespace learner;

    template<typename T, typename Q, typename P, int k>
    Parameter<P> crossValidate(Learner<T, Q, P>& learner, const ParameterSet<P>& paramset, const Sample<T, Q>& sample) {
        double min{+INFINITY};
        Parameter<P> p{};
        for (auto s : paramset.values()) {
            double avgerror{0};
            for (int i = 0; i < k; i++) {
                SlicedSettedSample<T, Q, k> setted = SlicedSample<T, Q, k>(sample).set(i);
                const auto training = setted.trainingSet();
                const auto validation = setted.validationSet();
                learner.train(training, s);
                avgerror += learner.test(validation);
            }
            avgerror /= k;
            if (avgerror < min) {
                min = avgerror;
                p = s;
            }
        }
        return p;
    };
}