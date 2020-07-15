///@file LossFunction.h
///@author: ***REMOVED***
///@Date: July 2020
///@Version: 0.1
///@File: Definition and implementation of the LossFunction interface and concrete implementations
#pragma once

#include "Input/Instance.h" //Instance, LabeledInstance

#include <cmath>            //pow
#include <type_traits>      //is_arithmetic

namespace loss {
    using namespace input;
    template<typename T, typename Q>
    class LossFunction {
    public:
        LossFunction() = default;
        virtual ~LossFunction() = 0;
        [[nodiscard]]
        virtual double loss(const Instance<T>& x, const Q& y, const Q& hx) = 0;
        [[nodiscard]]
        virtual double loss(const LabeledInstance<T, Q>& xy, const Q& hx) {
            loss(xy.instance(), xy.label(), hx);
        };
    };

    template <typename T, typename Q>
    LossFunction<T, Q>::~LossFunction() = default;

    template<typename T, typename Q>
    class ZeroOneLoss : public LossFunction<T, Q> {
    public:
        double loss (const Instance<T>& x, const Q& y, const Q& hx) override {
            return (y == hx) ? 0 : 1;
        };
        ~ZeroOneLoss() override = default;
    };

    template<typename T, typename Q>
    class SquaredLoss : public LossFunction<T, Q> {
    public:
        double loss(const Instance<T>& x, const Q& y, const Q& hx) override {
            static_assert(std::is_arithmetic<Q>());
            return pow((y - hx), 2);
        };
        ~SquaredLoss() override  = default;
    };
}