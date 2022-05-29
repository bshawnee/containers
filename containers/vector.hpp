//
// Created by Ilya Rozhnev on 17.04.2022.
//

#ifndef CONTAINERS_VECTOR_HPP
#define CONTAINERS_VECTOR_HPP
#include <memory>
#include "../iterators/reverse_iterator.hpp"
#include "../iterators/random_access_iterator.hpp"
#include "../core/Enable_if.hpp"
#include "../core/Is_integral.hpp"
#include "../core/IteratorFunc.hpp"
#include "../core/lexicographical_compare.hpp"
#include "../core/Assert.hpp"

namespace ft
{
    template <typename Type, class Allocator = std::allocator<Type> >
    class vector
    {
    public:
        typedef Type value_type;
        typedef Allocator allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef random_access_iterator<const value_type> const_iterator;
        typedef random_access_iterator<value_type> iterator;
        typedef reverse_iterator<const iterator> const_reverse_iterator;
        typedef reverse_iterator<iterator> reverse_iterator;
        typedef typename Iterators_traits<iterator>::difference_type difference_type;
        typedef typename allocator_type::size_type size_type;

        vector(const allocator_type& allocator = allocator_type())
        : alloc_(allocator)
        , start_(NULL)
        , end_(NULL)
        , endCapacity_(NULL)
        {}

        vector(size_type n, const value_type& x = value_type(), const allocator_type& alloc = allocator_type())
        : alloc_(alloc)
        , start_(NULL)
        , end_(NULL)
        , endCapacity_(NULL)
        {
            start_ = alloc_.allocate(n);
            endCapacity_ = start_ + n;
            end_ = start_;
            while (n--) {
                alloc_.construct(end_, x);
                end_++;
            }
        }

        template<class InputIt>
        vector(InputIt first,
               InputIt last,
               const allocator_type& alloc = Allocator(),
               typename Enable_if<!Is_integral<InputIt>::value, InputIt>::type* = NULL)
        : alloc_(alloc)
        {
            difference_type n = distance(first, last);
            start_ = alloc_.allocate(n);
            endCapacity_ = start_ + n;
            end_ = start_;
            while (n--) {
                alloc_.construct(end_, *first++);
                end_++;
            }
        }

        vector(const vector& ref)
        : alloc_(ref.alloc_)
        , start_(NULL)
        , end_(NULL)
        , endCapacity_(NULL)
        {
            *this = ref;
        }

        ~vector() { clear(); alloc_.deallocate(start_, capacity()); }

        vector& operator = (const vector& ref)
        {
            if (this == &ref) {
                return *this;
            }
            if (!empty()) {
                clear();
            }
            insert(this->end(), ref.begin(), ref.end());
            return *this;
        }

        reference operator [] (size_type n) { return *(start_ + n); }

        const_reference operator [] (size_type n) const { return *(start_ + n); }


        iterator begin() { return start_; }
        iterator begin() const { return start_; }
        iterator end() { return empty() ? begin() : end_; }
        iterator end() const { return empty() ? begin() : end_; }
        const_reverse_iterator rbegin() const { return reverse_iterator(end()); }
        const_reverse_iterator rend() const { return reverse_iterator(begin()); }
        reverse_iterator rbegin() { return reverse_iterator(end()); }
        reverse_iterator rend() { return reverse_iterator(begin()); }

        bool empty() const { return size() == 0; }
        size_type size() const { return end_ - start_; }
        size_type capacity() const { return endCapacity_ - start_; }
        size_type max_size() const { return allocator_type().max_size(); }
        reference at(size_type n) const { ft::assertWithMsg(n < size(), "Out of range"); return *this[n]; }
        reference front() { return *start_; }
        const_reference front() const { start_; }
        reference back() { return *(end_ - 1); }
        const_reference back() const { return *(end_ -1); }

        iterator erase (iterator position)
        {
            pointer prev = &(*position);
            alloc_.destroy(&(*position));
            if (&(*position) + 1 == end_)
                alloc_.destroy(&(*position));
            else
            {
                for (int i = 0; i < end_ - &(*position) - 1; i++)
                {
                    alloc_.construct(&(*position) + i, *(&(*position) + i + 1));
                    alloc_.destroy(&(*position) + i + 1);
                }
            }
            end_ -= 1;
            return prev;
        }

        iterator erase (iterator first, iterator second)
        {
            pointer p_first = &(*first);
            for (; &(*first) != &(*second); first++)
                alloc_.destroy(&(*first));
            for (int i = 0; i < end_ - &(*second); i++)
            {
                alloc_.construct(p_first + i, *(&(*second) + i));
                alloc_.destroy(&(*second) + i);
            }
            end_ -= (&(*second) - p_first);
            return (iterator(p_first));
        }

        void swap(vector& ref)
        {
            pointer start = ref.start_;
            pointer end = ref.end_;
            pointer newCapacity = ref.endCapacity_;
            allocator_type alloc = ref.alloc_;

            ref.start_ = start_;
            ref.end_ = end_;
            ref.endCapacity_ = endCapacity_;
            ref.alloc_ = alloc_;

            start_ = start;
            end_ = end;
            endCapacity_ = newCapacity;
            alloc_ = alloc;
        }

        void reserve(size_type n)
        {
            ft::assertWithMsg(n <= max_size(), "Cant reserve new size");
            if (n > capacity()) {
                pointer prevStart = start_;
                pointer prevEnd = end_;
                size_type prevSize = size();
                size_type prevCapacity = capacity();

                start_ = alloc_.allocate(n);
                endCapacity_ = start_ + n;
                end_ = start_;
                while (prevStart != prevEnd) {
                    alloc_.construct(end_, *prevStart);
                    ++end_;
                    ++prevStart;
                }
                alloc_.deallocate(prevStart - prevSize, prevCapacity);
            }
        }

        void clear()
        {
            difference_type n = size();
            for (difference_type i = 0; i < n; i++) {
                alloc_.destroy(end_);
                --end_;
            }
        }

        void resize(size_type n, value_type value = value_type())
        {
            ft::assertWithMsg(n <= max_size(), "container size is too large");
            if (size() > n) {
                while (size() > n) {
                    --end_;
                    alloc_.destroy(end_);
                }
            }
            else {
                insert(end(), n - size(), value);
            }
        }

        template <class InputIter>
        void assign(InputIter first, InputIter last, typename Enable_if<!Is_integral<InputIter>::value, InputIter>::type* = NULL)
        {
            clear();
            size_type dist = distance(first, last);
            if (static_cast<size_type>(endCapacity_ - start_) >= dist) {
                while (first != last) {
                    alloc_.construct(end_, *first);
                    ++first;
                    ++end_;
                }
            }
            else {
                pointer newStart = alloc_.allocate(dist);
                pointer newEnd = newStart;
                pointer newCapacity = newStart + dist;

                while (first != last) {
                    alloc_.construct(newEnd, *first);
                    ++first;
                    ++newEnd;
                }
                alloc_.deallocate(start_, capacity());
                start_ = newStart;
                end_ = newEnd;
                endCapacity_ = newCapacity;
            }
        }

        void assign(size_type n, const value_type& x)
        {
            clear();
            if (n == 0) return;

            if (static_cast<size_type>(endCapacity_ - start_) >= n) {
                while (n != 0) {
                    alloc_.construct(end_++, x);
                    --n;
                }
            }
            else {
                alloc_.deallocate(start_, capacity());
                start_ = alloc_.allocate(n);
                end_ = start_;
                endCapacity_ = start_ + n;
                while (n != 0) {
                    alloc_.construct(end_, x);
                    end_++;
                    --n;
                }

            }
        }

        void insert(const_iterator pos, size_type n, const value_type& val)
        {
            if (n == 0) return;
            assertWithMsg(n < max_size(), "error: cant allocate new size");
            size_type unchangedPos = &(*pos) - start_;
            size_type memoryUsed = static_cast<size_type>(endCapacity_ - end_);
            if (memoryUsed >= n && end_ != NULL) {
                for (size_type i = 0; i < size() - unchangedPos; i++) {
                    alloc_.construct(end_ - i + (n - 1), *(end_ - i - 1));
                }
                end_ += n;
                while (n != 0) {
                    alloc_.construct(&(*pos) + (n - 1), val);
                    --n;
                }
            }
            else {
                size_t newCapacity = capacity() > 0 ? size() * 2 : 1;
                pointer newStart = alloc_.allocate(newCapacity);
                pointer finalCapacity = newStart + newCapacity;

                if (static_cast<size_type>(finalCapacity - newStart) < (size() + n)) {
                    if (newStart != NULL) {
                        alloc_.deallocate(newStart, newStart - finalCapacity);
                    }
                    newCapacity = size() + n;
                    newStart = alloc_.allocate(newCapacity);
                    finalCapacity = newStart + newCapacity;
                }
                pointer newEnd = newStart + size() + n;
                for (size_type i = 0; i < static_cast<size_type>(&(*pos) - start_); i++) {
                    alloc_.construct(newStart + i, *(newStart + i));
                }
                for (size_type i = 0; i < n; i++) {
                    alloc_.construct(newStart + unchangedPos + i, val);
                }
                for (size_type i = 0; i < (size() - unchangedPos); i++) {
                    alloc_.construct(newEnd - i - 1, *(end_ - i - 1));
                }

                for (size_type i = 0; i < size(); i++) {
                    alloc_.destroy(start_ + i);
                }
                alloc_.deallocate(start_, capacity());

                start_ = newStart;
                end_ = newEnd;
                endCapacity_ = finalCapacity;
            }
        }

        iterator insert(iterator pos, const value_type& val)
        {
            size_type diff = &(*pos) - start_;
            insert(pos, 1, val);
            return start_ + diff;
        }

        template <typename InputIterator>
        typename Enable_if<!Is_integral<InputIterator>::value, void>::type
        insert(const_iterator pos, InputIterator first, InputIterator second)
        {
            size_type dist = ft::distance(first, second);
            if (size_type(endCapacity_ - end_) >= dist)
            {
                for(size_type i = 0; i < size() - (&(*pos) - start_); i++)
                    alloc_.construct(end_ - i + (dist - 1), *(end_ - i - 1));
                end_ += dist;
                for (; &(*first) != &(*second); first++, pos++)
                    alloc_.construct(&(*pos), *first);
            }
            else {
                pointer new_start =  alloc_.allocate(size() * 2);
                pointer new_end =  new_start + size() + dist;
                pointer new_end_capacity = new_start + (size() * 2);

                if (size_type(new_end_capacity - new_start) < size() + dist) {
                    if (new_start)
                        alloc_.deallocate(new_start, new_end_capacity - new_start);
                    new_start = alloc_.allocate(size() + dist);
                    new_end = new_start + size() + dist;
                    new_end_capacity = new_end;
                }

                try {
                    for (int i = 0; i < &(*pos) - start_; i++)
                        alloc_.construct(new_start + i, *(start_ + i));
                    for (int j = 0; first != second; first++, j++)
                        alloc_.construct(new_start + (&(*pos) - start_) + j, *first);
                    for (size_type k = 0; k < size() - (&(*pos) - start_); k++)
                        alloc_.construct(new_start + (&(*pos) - start_) + dist + k, *(start_ + (&(*pos) - start_) + k));

                    for (size_type l = 0; l < size(); l++)
                        alloc_.destroy(start_ + l);
                    alloc_.deallocate(start_, capacity());
                } catch (...) {
                    for (size_type l = 0; l < static_cast<size_type>(new_end - new_start); l++)
                        alloc_.destroy(new_start + l);
                    alloc_.deallocate(new_start, new_end - new_start);
                    throw std::exception();
                }

                start_ = new_start;
                end_ = new_end;
                endCapacity_ = new_end_capacity;
            }
        }

        void push_back(const value_type& x)
        {
            if (end_ == endCapacity_)
            {
                size_type newCapacity = (size() > 0) ? size() * 2 : 1;
                this->reserve(newCapacity);
            }
            alloc_.construct(end_, x);
            ++end_;
        }

        void pop_back()
        {
            alloc_.destroy(&back());
            --end_;
        }

        reference at(size_type n)
        {
            ft::assertWithMsg(n >= 0 && n <= size(), "Invalid index: at()");
            return *(start_ + n);
        }

    private:
        allocator_type alloc_;
        pointer start_;
        pointer end_;
        pointer endCapacity_;
    };

    template <class Type, class Alloc>
    bool operator == (const ft::vector<Type, Alloc>& lhs, const ft::vector<Type, Alloc>& rhs)
    {
        if (lhs.size() != rhs.size()) return false;

        typename ft::vector<Type>::iterator leftIt = lhs.begin();
        typename ft::vector<Type>::iterator rightIt = rhs.begin();
        while (leftIt != lhs.end()) {
            if (*leftIt++ != *rightIt++)
                return false;
        }
        return true;
    }

    template <class Type, class Alloc>
    bool operator != (const ft::vector<Type, Alloc>& lhs, const ft::vector<Type, Alloc>& rhs)
    {
        return !(lhs == rhs);
    }

    template <class Type, class Alloc>
    bool operator < (const ft::vector<Type, Alloc>& lhs, const ft::vector<Type, Alloc>& rhs)
    {
        return lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <class Type, class Alloc>
    bool operator <= (const ft::vector<Type, Alloc>& lhs, const ft::vector<Type, Alloc>& rhs)
    {
        return lhs < rhs || lhs == rhs;
    }

    template <class Type, class Alloc>
    bool operator > (const ft::vector<Type, Alloc>& lhs, const ft::vector<Type, Alloc>& rhs)
    {
        return !(lhs <= rhs);
    }

    template <class Type, class Alloc>
    bool operator >= (const ft::vector<Type, Alloc>& lhs, const ft::vector<Type, Alloc>& rhs)
    {
        return lhs > rhs || lhs == rhs;
    }

} // namespace ft

namespace std
{
    template <class T>
    void swap(ft::vector<T>& lhs, ft::vector<T>& rhs)
    {
        lhs.swap(rhs);
    }
}

#endif //CONTAINERS_VECTOR_HPP
