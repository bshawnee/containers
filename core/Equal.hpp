//
// Created by Ilya Rozhnev on 15.05.2022.
//

#ifndef CONTAINERS_EQUAL_HPP
#define CONTAINERS_EQUAL_HPP
#include "less.hpp"

namespace ft
{
    template <class T>
    struct Equal : binary_function<T, T,  bool>
    {
        bool operator() (const T& f, const T& s) const { return f == s; }
    };


    template <class T>
    struct EqualMap : binary_function<T, T,  bool>
    {
        bool operator() (const T& f, const T& s) const { return f.first == s.first; }
    };
}

#endif //CONTAINERS_EQUAL_HPP
