//
// Created by edoardo on 05/07/20.
//
#pragma once

#include "../Input/Instance.h"

namespace loss {
    using namespace input;
    template<typename T, typename Q>
    class LossFunction {
        virtual double loss(Instance<T> x, Q y, Q hx) = 0;
        virtual double loss(LabeledInstance<T, Q> xy, Q hx) {
            loss(xy.instance(), xy.label(), hx);
        };
    };
}