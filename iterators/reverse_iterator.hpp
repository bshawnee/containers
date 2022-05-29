//
// Created by Ilya Rozhnev on 17.04.2022.
//

#ifndef CONTAINERS_REVERSE_ITERATOR_HPP
#define CONTAINERS_REVERSE_ITERATOR_HPP
#include "random_access_iterator.hpp"
#include "../core/Enable_if.hpp"
#include "../core/Is_same.hpp"
namespace ft
{
    // reverse_iterator
    // ===================================================================

    template <class Iterator>
    class reverse_iterator
    {
    public:
        typedef Iterator iterator_type;
        typedef typename Iterators_traits<Iterator>::iterator_category iterator_category;
        typedef typename Iterators_traits<Iterator>::value_type value_type;
        typedef typename Iterators_traits<Iterator>::difference_type difference_type;
        typedef typename Iterators_traits<Iterator>::pointer pointer;
        typedef typename Iterators_traits<Iterator>::reference reference;
        typedef const reference const_reference;

        reverse_iterator() : iter_() {}
        reverse_iterator(const iterator_type& iter) : iter_(iter) {}
        template <class Iter>
        reverse_iterator(const reverse_iterator<Iter>& it) : iter_(it.base()) {}
        virtual ~reverse_iterator() {}

        iterator_type base() const { return iter_; }


        reference operator * () {
            iterator_type tmp = iter_;
            if (Is_same<iterator_category, random_access_iterator_tag>::value) {
                return *(--tmp);
            }
            return *tmp;
        }

        const_reference operator * () const {
            iterator_type tmp = iter_;
            if (Is_same<iterator_category, random_access_iterator_tag>::value) {
                return *(--tmp);
            }
            return *tmp;
        }

        reverse_iterator operator + (difference_type n) const { return reverse_iterator(iter_ - n); }
        reverse_iterator& operator ++ () { --iter_; return *this; }
        reverse_iterator operator ++ (int) { reverse_iterator tmp = *this; ++(*this); return tmp; }
        reverse_iterator& operator += (difference_type n) { iter_ -= n; return *this; }
        reverse_iterator operator - (difference_type n) { return reverse_iterator(iter_ + n); }
        reverse_iterator& operator -- () { ++iter_; return *this; }
        reverse_iterator operator --(int) { reverse_iterator tmp = *this; --(*this); return tmp; }
        reverse_iterator& operator -= (difference_type n) { iter_ += n; return *this; }
        pointer operator ->() const { return &(operator*()); }
        reference operator [] (difference_type n) const { return (this->base()[-n - 1]); }

    private:
        iterator_type iter_;
    };
    template <class Iterator>
    bool operator == (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    { return lhs.base() == rhs.base(); }

    template <class Iterator, class IteratorConst>
    bool operator == (const reverse_iterator<Iterator>& lhs, const reverse_iterator<IteratorConst>& rhs)
    { return lhs.base() == rhs.base(); }

    template <class Iterator>
    bool operator != (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    { return !(lhs.base() == rhs.base()); }

    template <class Iterator, class IteratorConst>
    bool operator != (const reverse_iterator<Iterator>& lhs, const reverse_iterator<IteratorConst>& rhs)
    { return !(lhs.base() == rhs.base()); }

    template <class Iterator>
    bool operator < (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    { return lhs.base() < rhs.base(); }

    template <class Iterator, class IteratorConst>
    bool operator < (const reverse_iterator<Iterator>& lhs, const reverse_iterator<IteratorConst>& rhs)
    { return lhs.base() < rhs.base(); }

    template <class Iterator>
    bool operator > (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    { return lhs.base() > rhs.base(); }

    template <class Iterator, class IteratorConst>
    bool operator > (const reverse_iterator<Iterator>& lhs, const reverse_iterator<IteratorConst>& rhs)
    { return lhs.base() > rhs.base(); }

    template <class Iterator>
    bool operator <= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    { return lhs.base() <= rhs.base(); }

    template <class Iterator, class IteratorConst>
    bool operator <= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<IteratorConst>& rhs)
    { return lhs.base() <= rhs.base(); }

    template <class Iterator>
    bool operator >= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    { return lhs.base() >= rhs.base(); }

    template <class Iterator, class IteratorConst>
    bool operator >= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<IteratorConst>& rhs)
    { return lhs.base() >= rhs.base(); }

    template <class Iterator>
    reverse_iterator<Iterator> operator + ( typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& iter)
    { return iter + n; }

    template <class Iterator>
    typename reverse_iterator<Iterator>::difference_type operator - (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
    { return lhs.base() - rhs.base(); }

    template <class Iterator, class IteratorConst>
    bool operator - (const reverse_iterator<Iterator>& lhs, const reverse_iterator<IteratorConst>& rhs)
    { return lhs.base() - rhs.base(); }
}

#endif //CONTAINERS_REVERSE_ITERATOR_HPP
