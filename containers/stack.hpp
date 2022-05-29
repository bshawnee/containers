//
// Created by Ilya Rozhnev on 01.05.2022.
//

#ifndef CONTAINERS_STACK_HPP
#define CONTAINERS_STACK_HPP
#include "vector.hpp"

namespace ft
{
    template <class Type, class Container = vector<Type> >
    class stack
    {
    public:
        typedef Type value_type;
        typedef Container container_type;
        typedef size_t size_type;

        stack(const container_type& container = container_type()) : c(container) {}
        ~stack() {}

        bool empty() const { return c.empty(); }
        size_type size() const { return c.size(); }
        value_type& top() { return c.back(); }
        const value_type& top() const { return c.back(); }
        void push(const value_type& val) { c.push_back(val); }
        void pop() {c.pop_back(); }

        template <class T, class C>
        friend bool operator == (const stack<T, C>& lhs, const stack<T, C>& rhs);

        template <class T, class C>
        friend bool operator != (const stack<T, C>& lhs, const stack<T, C>& rhs);

        template <class T, class C>
        friend bool operator < (const stack<T, C>& lhs, const stack<T, C>& rhs);

        template <class T, class C>
        friend bool operator <= (const stack<T, C>& lhs, const stack<T, C>& rhs);

        template <class T, class C>
        friend bool operator > (const stack<T, C>& lhs, const stack<T, C>& rhs);

        template <class T, class C>
        friend bool operator >= (const stack<T, C>& lhs, const stack<T, C>& rhs);

    protected:
        container_type c;
    };

    template <class Type, class Container>
    bool operator == (const stack<Type, Container>& lhs, const stack<Type, Container>& rhs)
    {
        return lhs.c == rhs.c;
    }

    template <class Type, class Container>
    bool operator != (const stack<Type, Container>& lhs, const stack<Type, Container>& rhs)
    {
        return !(lhs.c == rhs.c);
    }


    template <class Type, class Container>
    bool operator < (const stack<Type, Container>& lhs, const stack<Type, Container>& rhs)
    {
        return lhs.c < rhs.c;
    }

    template <class Type, class Container>
    bool operator <= (const stack<Type, Container>& lhs, const stack<Type, Container>& rhs)
    {
        return lhs.c <= rhs.c;
    }

    template <class Type, class Container>
    bool operator > (const stack<Type, Container>& lhs, const stack<Type, Container>& rhs)
    {
        return lhs.c > rhs.c;
    }

    template <class Type, class Container>
    bool operator >= (const stack<Type, Container>& lhs, const stack<Type, Container>& rhs)
    {
        return lhs.c >= rhs.c;
    }

} // namespace ft

#endif //CONTAINERS_STACK_HPP
