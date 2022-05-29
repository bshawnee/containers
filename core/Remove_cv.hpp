//
// Created by Ilya Rozhnev on 10.03.2022.
//

#ifndef CONTAINERS_REMOVE_CV_HPP
#define CONTAINERS_REMOVE_CV_HPP

namespace ft
{
    template <class T> struct remove_cv{ typedef T type; };
    template <class T> struct remove_cv<T const>{ typedef T type;  };
    template <class T> struct remove_cv<T volatile>{ typedef T type; };
    template <class T> struct remove_cv<T const volatile>{ typedef T type; };
}

#endif //CONTAINERS_REMOVE_CV_HPP
