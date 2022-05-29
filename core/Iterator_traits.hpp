//
// Created by Ilya Rozhnev on 10.03.2022.
//

#ifndef CONTAINERS_ITERATOR_TRAITS_HPP
#define CONTAINERS_ITERATOR_TRAITS_HPP
#include <cstddef>
namespace ft
{
    struct input_iterator_tag { };
    struct output_iterator_tag { };
    struct forward_iterator_tag : public input_iterator_tag { };
    struct bidirectional_iterator_tag : public forward_iterator_tag { };
    struct random_access_iterator_tag : public bidirectional_iterator_tag { };

    template <typename Iter>
    struct Iterators_traits
    {
        typedef typename Iter::difference_type difference_type;
        typedef typename Iter::value_type value_type;
        typedef typename Iter::pointer pointer;
        typedef typename Iter::reference reference;
        typedef typename Iter::iterator_category iterator_category;
    };

    template <typename T>
    struct Iterators_traits<T*>
    {
        typedef ptrdiff_t difference_type;
        typedef T value_type;
        typedef T* pointer;
        typedef T& reference;
        typedef random_access_iterator_tag iterator_category;
    };


    namespace detail
    {

        template <class IterTag, bool isValid>
        struct ValidIteratorTag
        {
            typedef IterTag tag;
            operator tag() const throw() { return isValid; }
            static const bool value = isValid;
        };

        template <class IterTag> struct IsValidIteratorTag : ValidIteratorTag<IterTag, true> {};
        template <class IterTag> struct IsInvalidIteratorTag : ValidIteratorTag<IterTag, false> {};

        template <class IterTag> struct ValidIterator : IsInvalidIteratorTag<IterTag> {};

        template <> struct ValidIterator<input_iterator_tag> : IsValidIteratorTag<input_iterator_tag> {};
        template <> struct ValidIterator<forward_iterator_tag> : IsValidIteratorTag<forward_iterator_tag> {};
        template <> struct ValidIterator<random_access_iterator_tag> : IsValidIteratorTag<random_access_iterator_tag> {};
        template <> struct ValidIterator<bidirectional_iterator_tag> : IsValidIteratorTag<bidirectional_iterator_tag> {};


    }


}

#endif //CONTAINERS_ITERATOR_TRAITS_HPP
