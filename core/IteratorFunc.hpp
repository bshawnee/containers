//
// Created by Ilya Rozhnev on 03.04.2022.
//

#ifndef CONTAINERS_ITERATORFUNC_HPP
#define CONTAINERS_ITERATORFUNC_HPP
#include "Iterator_traits.hpp"

namespace ft
{
    namespace detail
    {
        template <class InputIter>
        void do_advance(InputIter& i, typename Iterators_traits<InputIter>::difference_type n, input_iterator_tag)
        {
            for (; n > 0; --n)
                ++i;
        }

        template <class BiDirIter>
        void do_advance(BiDirIter& i, typename Iterators_traits<BiDirIter>::difference_type n, bidirectional_iterator_tag)
        {
            if (n >= 0) {
                for (; n > 0; --n) {
                    ++i;
                }
            }
            else {
                for (; n < 0; ++n) {
                    --i;
                }
            }
        }

        template <class RandIter>
        void do_advance(RandIter& i, typename Iterators_traits<RandIter>::difference_type n, random_access_iterator_tag)
        {
            i += n;
        }
    }

    template <class It, class Distance>
    void advance(It& it, Distance n)
    {
        detail::do_advance(it, typename Iterators_traits<It>::difference_type(n),
                           typename Iterators_traits<It>::iterator_category());
    }

    template <class InputIterator>
    typename Iterators_traits<InputIterator>::difference_type distance(InputIterator begin, InputIterator last)
    {
        typename Iterators_traits<InputIterator>::difference_type n = 0;
        while (begin != last) {
            ++n;
            ++begin;
        }
        return n;
    }
}

#endif //CONTAINERS_ITERATORFUNC_HPP
