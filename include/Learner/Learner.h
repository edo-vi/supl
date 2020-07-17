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

///@brief Namespace containing all the definitions and implementations related to the abstract Learner interface
namespace learner {
    using namespace sample;
    using namespace parameter;
    ///@param T The type of the elements making up the instances of the samples used by the learner
    ///@param Q The type of the labels of the instances
    ///@param P The type of the parameter of the learner
    ///@brief Abstract learner interface, inherited by all classification/regression-based algorithms
    template<typename T, typename Q, typename P>
    class Learner {
    public:
        virtual ~Learner() = 0;
        ///@param sample A sample of LabeledInstances whose datapoints are of type T and their label of type Q
        ///@param param An (hyper)parameter, used in the training and/or labeling phases
        ///@brief Trains the learner on the passed sample based on the hyperparameter, possibily changing its internal state
        virtual void train(const Sample<T, Q>& sample, Parameter<P> param) = 0;
        ///@param sample A sample of LabeledInstances whose datapoints are of type T and their label of type Q
        ///@brief The same as calling the other *train* method with the same sample and the previously passed
        ///parameter (in the constructor)
        virtual void train(const Sample<T, Q> &sample) = 0;
        ///@param sample A sample of LabeledInstances whose datapoints are of type T and their label of type Q
        ///@return A double representing the empirical risk on the sample
        ///@brief Test the learner on the passed sample and returns the empirical error
        double test(const Sample<T, Q>& sample) const {
            auto l = lossFunction();
            double v{};
            for (int64_t i = 0; i < sample.size(); i++) {
                auto samplepoint = sample[i];
                v += l->loss(samplepoint.instance(), samplepoint.label(), predict(samplepoint));
            }
            return v/sample.size();
        };
        ///@param sample A sample of LabeledInstances whose datapoints are of type T and their label of type Q
        ///@return A double representing the empirical risk on the sample
        ///@brief Test the learner on the passed sample and returns the empirical error; same as the other
        ///method but with support for verbose output messages, showing the learner's decisions on the input
        ///test sample and its errors
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
        ///@return The parameter of the learner
        ///@brief Simply returns the parameter of the learner
        virtual Parameter<P> hyperparameter() const = 0;
        ///@param input An instance of type T (vector of elements of type T)
        ///@return The label predicted for the passed instance
        virtual Q predict(Instance<T> input) const = 0;
        ///@return Unique_ptr to the loss function used by the learner
        virtual std::unique_ptr<loss::LossFunction<T, Q>> lossFunction() const = 0;
    };


    template <typename T, typename Q, typename P>
    Learner<T, Q, P>::~Learner() = default;

}