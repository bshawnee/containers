//
// Created by Ilya Rozhnev on 23.03.2022.
//

#ifndef CONTAINERS_RANDOM_ACCESS_ITERATOR_HPP
#define CONTAINERS_RANDOM_ACCESS_ITERATOR_HPP
#include "../core/BaseIterator.hpp"

namespace ft
{
    // random_access_iterator <vector spec>
    // ===================================================================
    template <typename Type>
    struct random_access_iterator : iterator<random_access_iterator_tag, Type>
    {
        typedef typename iterator<random_access_iterator_tag, Type>::iterator_category iterator_category;
        typedef typename iterator<random_access_iterator_tag, Type>::reference reference;
        typedef typename iterator<random_access_iterator_tag, Type>::pointer pointer;
        typedef typename iterator<random_access_iterator_tag, Type>::difference_type difference_type;
        typedef typename iterator<random_access_iterator_tag, Type>::value_type value_type;

        random_access_iterator() : iterator<random_access_iterator_tag, Type>() {}
        random_access_iterator(pointer ptr) : iterator<random_access_iterator_tag, Type>(ptr) {}
        random_access_iterator(const random_access_iterator& ref) : iterator<random_access_iterator_tag, Type>(ref) {}

        random_access_iterator& operator = (const random_access_iterator& ref)
        {
            if (this == &ref) {
                return *this;
            }
            this->ptr_ = ref.ptr_;
            return *this;
        }
        pointer base() const { return this->ptr_; }
        random_access_iterator& operator ++ () { ++this->ptr_; return *this; }
        random_access_iterator operator ++ (int) { random_access_iterator tmp(*this); ++(*this); return tmp;}
        random_access_iterator& operator -- () { --this->ptr_; return *this; }
        random_access_iterator operator -- (int) { random_access_iterator tmp(*this); --(*this); return tmp; }
        random_access_iterator operator + (difference_type n) const { return this->ptr_ + n; }
        random_access_iterator operator - (difference_type n) const { return this->ptr_ - n; }
        random_access_iterator& operator += (difference_type n) { this->ptr_ += n; return *this; }
        random_access_iterator& operator -= (difference_type n) { this->ptr_ -= n; return *this; }
        reference operator [] (difference_type n) { return *(*this += n); }
        operator random_access_iterator<const Type>() const { return random_access_iterator<const Type>(this->ptr_); }
    };

    // operator ==
    template <class Type>
    typename random_access_iterator<Type>::difference_type operator == (const random_access_iterator<Type>& lhs, const random_access_iterator<Type>& rhs)
    { return lhs.base() == rhs.base(); }

    template <class Type>
    typename random_access_iterator<Type>::difference_type operator == (random_access_iterator<Type>& lhs, random_access_iterator<Type>& rhs)
    { return lhs.base() == rhs.base(); }

    template <class Type, class ConstType>
    typename random_access_iterator<Type>::difference_type operator == (const random_access_iterator<Type>& lhs, const random_access_iterator<ConstType>& rhs)
    { return lhs.base() == rhs.base(); }

    // operator !=
    template <class Type>
    typename random_access_iterator<Type>::difference_type operator != (const random_access_iterator<Type>& lhs, const random_access_iterator<Type>& rhs)
    { return !(lhs == rhs); }

    template <class Type>
    typename random_access_iterator<Type>::difference_type operator != (random_access_iterator<Type>& lhs, random_access_iterator<Type>& rhs)
    { return !(lhs == rhs); }

    template <class Type, class ConstType>
    typename random_access_iterator<Type>::difference_type operator != (const random_access_iterator<Type>& lhs, const random_access_iterator<ConstType>& rhs)
    { return !(lhs == rhs); }

    // operator <
    template <class Type>
    typename random_access_iterator<Type>::difference_type operator < (const random_access_iterator<Type>& lhs, const random_access_iterator<Type>& rhs)
    { return lhs.base() < rhs.base(); }

    template <class Type>
    typename random_access_iterator<Type>::difference_type operator < (random_access_iterator<Type>& lhs, random_access_iterator<Type>& rhs)
    { return lhs.base() < rhs.base(); }

    template <class Type, class ConstType>
    typename random_access_iterator<Type>::difference_type operator < (random_access_iterator<Type>& lhs, random_access_iterator<ConstType>& rhs)
    { return lhs.base() < rhs.base(); }

    // operator >
    template <class Type>
    typename random_access_iterator<Type>::difference_type operator > (const random_access_iterator<Type>& lhs, const random_access_iterator<Type>& rhs)
    { return lhs.base() > rhs.base(); }

    template <class Type>
    typename random_access_iterator<Type>::difference_type operator > (random_access_iterator<Type>& lhs, random_access_iterator<Type>& rhs)
    { return lhs.base() > rhs.base(); }

    template <class Type, class ConstType>
    typename random_access_iterator<Type>::difference_type operator > (random_access_iterator<Type>& lhs, random_access_iterator<ConstType>& rhs)
    { return lhs.base() > rhs.base(); }

    // operator <=
    template <class Type>
    typename random_access_iterator<Type>::difference_type operator <= (const random_access_iterator<Type>& lhs, const random_access_iterator<Type>& rhs)
    { return lhs.base() <= rhs.base(); }

    template <class Type>
    typename random_access_iterator<Type>::difference_type operator <= ( random_access_iterator<Type>& lhs, random_access_iterator<Type>& rhs)
    { return lhs.base() <= rhs.base(); }

    template <class Type, class ConstType>
    typename random_access_iterator<Type>::difference_type operator <= (random_access_iterator<Type>& lhs, random_access_iterator<ConstType>& rhs)
    { return lhs.base() <= rhs.base(); }

    // operator >=
    template <class Type>
    typename random_access_iterator<Type>::difference_type operator >= (const random_access_iterator<Type>& lhs, const random_access_iterator<Type>& rhs)
    { return lhs.base() >= rhs.base(); }

    template <class Type>
    typename random_access_iterator<Type>::difference_type operator >= (random_access_iterator<Type>& lhs, random_access_iterator<Type>& rhs)
    { return lhs.base() >= rhs.base(); }

    template <class Type, class ConstType>
    typename random_access_iterator<Type>::difference_type operator >= (random_access_iterator<Type>& lhs, random_access_iterator<ConstType>& rhs)
    { return lhs.base() >= rhs.base(); }


    template <class Type>
    random_access_iterator<Type> operator += (typename random_access_iterator<Type>::difference_type n, const random_access_iterator<Type>& ref)
    { return &(*ref + n); }

    template <class Type>
    random_access_iterator<Type> operator -= (typename random_access_iterator<Type>::difference_type n, const random_access_iterator<Type>& ref)
    { return &(*ref - n); }

    template <class Type>
    typename random_access_iterator<Type>::difference_type operator - (const random_access_iterator<Type>& lhs, const random_access_iterator<Type>& rhs)
    { return (lhs.base() - rhs.base()); }

}

#endif //CONTAINERS_RANDOM_ACCESS_ITERATOR_HPP
