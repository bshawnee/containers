//
// Created by Ilya Rozhnev on 10.03.2022.
//

#ifndef CONTAINERS_INTEGRAL_CONST_HPP
#define CONTAINERS_INTEGRAL_CONST_HPP

namespace ft
{
    template <typename T, T Value>
    struct Integral_const
    {
        typedef T value_type;
        operator value_type() const { return Value; }
        static const bool value = Value;
    };



    typedef Integral_const<bool, false> false_type;
    typedef Integral_const<bool, true> true_type;
}

#endif //CONTAINERS_INTEGRAL_CONST_HPP
