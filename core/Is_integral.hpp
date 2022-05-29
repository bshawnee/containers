//
// Created by Ilya Rozhnev on 10.03.2022.
//

#ifndef CONTAINERS_IS_INTEGRAL_HPP
#define CONTAINERS_IS_INTEGRAL_HPP
#include "Integral_const.hpp"
#include "Remove_cv.hpp"

namespace ft
{
    template <typename> struct Is_integral_base : false_type {};

    template <> struct Is_integral_base<bool> : true_type {};
    template <> struct Is_integral_base<char> : true_type {};
    template <> struct Is_integral_base<unsigned char> : true_type {};
    template <> struct Is_integral_base<short> : true_type {};
    template <> struct Is_integral_base<unsigned short> : true_type {};
    template <> struct Is_integral_base<int> : true_type {};
    template <> struct Is_integral_base<unsigned int> : true_type {};
    template <> struct Is_integral_base<long> : true_type {};
    template <> struct Is_integral_base<unsigned long> : true_type {};
    template <> struct Is_integral_base<long long> : true_type {};
    template <> struct Is_integral_base<unsigned long long> : true_type {};
    template <> struct Is_integral_base<wchar_t> : true_type {};

    template <typename T> struct Is_integral : Is_integral_base<typename remove_cv<T>::type> {};
}

#endif //CONTAINERS_IS_INTEGRAL_HPP
