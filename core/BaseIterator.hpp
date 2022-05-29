//
// Created by Ilya Rozhnev on 03.04.2022.
//

#ifndef CONTAINERS_BASEITERATOR_HPP
#define CONTAINERS_BASEITERATOR_HPP
#include "Iterator_traits.hpp"


namespace ft
{
    template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
    struct iterator
    {
        typedef T value_type;
        typedef Distance difference_type;
        typedef Pointer pointer;
        typedef Reference reference;
        typedef Category iterator_category;

        iterator() : ptr_(NULL) {}
        iterator(const iterator& ref) { *this = ref; }
        iterator(pointer ptr) : ptr_(ptr) {}
        iterator& operator = (const iterator& ref)
        {
            if (this != &ref) {
                ptr_ = ref.ptr_;
            }
            return *this;
        }

        virtual reference operator * () { return *ptr_; }
        virtual pointer operator -> () { return &operator*(); }

        virtual ~iterator() {}


    protected:
        pointer ptr_;
    };
}

#endif //CONTAINERS_BASEITERATOR_HPP
