//
// Created by Ilya Rozhnev on 14.05.2022.
//

#ifndef CONTAINERS_IS_SAME_HPP
#define CONTAINERS_IS_SAME_HPP

namespace ft
{
    template<typename T, typename U>
    struct Is_same
    {
        static const bool value = false;
    };

    template<typename T>
    struct Is_same<T,T>
    {
        static const bool value = true;
    };
}

#endif //CONTAINERS_IS_SAME_HPP
