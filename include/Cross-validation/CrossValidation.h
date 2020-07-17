///@file CrossValidation.h
///@author: ***REMOVED***
///@Date: July 2020
///@Version: 0.1
///@File: Definition and implementation of the function crossValidate
#pragma once

#include "../Learner/Parameter.h" //Parameter, ParameterSet
#include "../Learner/Learner.h"   //Learner
#include "../Input/Sample.h"      //Sample, SlicedSettedSample

///@brief Namespace containing all those definitions/implementations related to cross-validation
namespace crossvalidation {
    using namespace parameter;
    using namespace learner;

    ///@param T The type of the instances (data vectors)
    ///@param Q The type of the labels
    ///@param P The type of the parameters of the learner
    ///@param k The number of disjoint subsets in which the sample is divided
    ///@param learner A Learner that will train and validate on the sample
    ///@param paramset A ParameterSet whose elements are used with the learner to calculate its error on the validation
    ///sample and from which the `best' parameter is chosen
    ///@param sample The sample used to cross-validate the learner
    ///@return The `best' parameter among those in the ParameterSet, that is, the one with the lowest average error
    ///@brief Cross-validates the learner on the passed sample by testing all the parameters in the parameter set
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