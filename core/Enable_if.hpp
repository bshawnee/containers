//
// Created by Ilya Rozhnev on 10.03.2022.
//

#ifndef CONTAINERS_ENABLE_IF_HPP
#define CONTAINERS_ENABLE_IF_HPP

namespace ft
{
    template <bool B, typename T = void>
    struct Enable_if {};

    template <typename T>
    struct Enable_if<true, T> { typedef T type; };
}

#endif //CONTAINERS_ENABLE_IF_HPP
