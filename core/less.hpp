//
// Created by Ilya Rozhnev on 03.05.2022.
//

#ifndef CONTAINERS_LESS_HPP
#define CONTAINERS_LESS_HPP
namespace ft
{
    template <class Arg1, class Arg2, class Result>
    struct binary_function
    {
        typedef Arg1 first_argument_type;
        typedef Arg2 second_argument_type;
        typedef Result result_type;
    };

    template <class T>
    struct less : binary_function<T, T, bool>
    {
        bool operator() (const T& x, const T& y) const { return (x < y); }
    };

    template <class Less, class T>
    struct map_less : binary_function<T, T, bool>
    {
        map_less() : less_(Less()) {}
        map_less(const Less& less) : less_(less) {}
        map_less(const map_less& ref) { *this = ref; }
        map_less& operator = (const map_less& ref)
        {
            if (this == &ref) {
                return *this;
            }
            less_ = ref.less_;
            return *this;
        }
        bool operator() (const T& x, const T& y) const { return less_(x.first, y.first); }
    private:
        Less less_;
    };

} // namespace ft
#endif //CONTAINERS_LESS_HPP
