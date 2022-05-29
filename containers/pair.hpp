//
// Created by Ilya Rozhnev on 01.05.2022.
//

#ifndef CONTAINERS_PAIR_HPP
#define CONTAINERS_PAIR_HPP
#include "../core/Is_integral.hpp"
namespace ft
{
    template <class First, class Second>
    class pair
    {
    public:
        typedef First first_type;
        typedef Second second_type;

        first_type first;
        second_type second;

        pair() : first(), second() {}

        template <class F, class S>
        pair(const pair<F, S>& ref) : first(ref.first), second(ref.second) {}

        template <class F, class S>
        pair(const F& f, const S& s) : first(f), second(s) {}
        pair(const pair& ref) : first(ref.first), second(ref.second) {}
        
        pair& operator = (const pair& ref)
        {
            if (this == &ref) {
                return *this;
            }
            first_type& tmp = first;
            const_cast<typename ft::remove_cv<first_type>::type&>(tmp) = ref.first;
            second = ref.second;
            return *this;
        }

        ~pair() {}
    };

    template <class First, class Second>
    bool operator == (const pair<First, Second> first, const pair<First, Second> second)
    {
        return first.first == second.first && first.second == second.second;
    }

    template <class First, class Second>
    bool operator != (const pair<First, Second> first, const pair<First, Second> second)
    {
        return !(first == second);
    }

    template <class First, class Second>
    bool operator < (const pair<First, Second> first, const pair<First, Second> second)
    {
        if (first.first < second.first){
            return true;
        }
        if (first.first == second.first && first.second < second.second) {
            return true;
        }
        return false;
    }

    template <class First, class Second>
    bool operator > (const pair<First, Second> first, const pair<First, Second> second)
    {
        return !(first < second) && first != second;
    }

    template <class First, class Second>
    bool operator <= (const pair<First, Second> first, const pair<First, Second> second)
    {
        return first < second || first == second;
    }

    template <class First, class Second>
    bool operator >= (const pair<First, Second> first, const pair<First, Second> second)
    {
        return first > second || first == second;
    }

    template <class First, class Second>
    pair<First, Second> make_pair(First first, Second second)
    {
        return pair<First, Second>(first, second);
    }

} // ft

#endif //CONTAINERS_PAIR_HPP
