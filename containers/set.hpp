//
// Created by Ilya Rozhnev on 02.05.2022.
//

#ifndef CONTAINERS_SET_HPP
#define CONTAINERS_SET_HPP
#include "../iterators/bidirectional_iterator.hpp"
#include "../iterators/reverse_iterator.hpp"
#include "../core/Iterator_traits.hpp"
#include "../containers/pair.hpp"
#include "../core/BRTree.hpp"
#include "../containers/vector.hpp"

namespace ft
{

    template <class Type, class Compare = ft::less<Type>, class Allocator = std::allocator<Type> >
    class set
    {
    public:
        typedef Type key_type;
        typedef Type value_type;
        typedef Allocator allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef Compare key_compare;
        typedef b_list<key_type> node_type;
        typedef Compare value_compare;
        typedef node_type* node_pointer;
        typedef const bidirectional_iterator<value_type> const_iterator;
        typedef bidirectional_iterator<value_type> iterator;
        typedef reverse_iterator<const_iterator> const_reverse_iterator;
        typedef reverse_iterator<iterator> reverse_iterator;
        typedef typename Iterators_traits<iterator>::difference_type difference_type;
        typedef typename allocator_type::size_type size_type;
        typedef tree_handler<key_type, key_compare, Equal<value_type>, node_type, allocator_type> tree;


        set(const key_compare& comp = key_compare(), const allocator_type& allocator = allocator_type())
        : tree_(comp, Equal<value_type>(), allocator)
        , first_(NULL)
        , end_(NULL)
        , size_(0)
        {}
        set(const set& ref)
        : first_(NULL)
        , end_(NULL)
        , size_(0)
        { *this = ref; }

        template< class InputIt >
        set(InputIt first, InputIt last, const value_compare& comp = value_compare(), const allocator_type& alloc = allocator_type() )
        : tree_(comp, Equal<value_type>(), alloc)
        , size_(0)
        {
            while (first != last) {
                tree_.insert(*first);
                ++first;
                ++size_;
            }
        }

        set& operator = (const set& ref)
        {
            if (this == &ref) {
                return *this;
            }
            clear();
            insert(ref.begin(), ref.end());
            return *this;
        }

        void clear()
        {
            node_pointer root = tree_.getRoot();
            tree_.clearAll(root);
            tree_.getRootRef() = NULL;
            size_ = 0;
        }

        size_type size() const { return size_; }
        size_type max_size() const { return allocator_type().max_size();}
        bool empty() const { return size() == 0; }

        iterator find(const value_type& x) const
        {
            return tree_.search(tree_.getRoot(), x);
        }

        size_type count(const value_type& x) const
        {
            node_type* tmp = tree_.search(tree_.getRoot(), x);
            if (tmp == NULL) {
                return 0;
            }
            return 1;
        }

        iterator lower_bound (const key_type& k)
        {
            key_compare comp = key_comp();
            iterator itBeg = begin();
            while ( itBeg != end()) {
                if (comp(k, *itBeg) || k == *itBeg) {
                    break;
                }
                itBeg++;
            }
            return itBeg == end() ? end() : itBeg;
        }

        const_iterator lower_bound(const value_type& x) const
        {
            key_compare comp = key_comp();
            iterator itBeg = begin();
            while (itBeg != end() || x == *itBeg) {
                if (comp(x, *itBeg)) {
                    break;
                }
                itBeg++;
            }
            return itBeg == end() ? end() : itBeg;
        }

        iterator upper_bound (const key_type& k)
        {
            iterator itBeg = lower_bound(k);
            if (itBeg == end()) {
                return end();
            }
            return *itBeg == k ? ++itBeg : itBeg;
        }

        const_iterator upper_bound(const value_type& x) const
        {
            iterator itBeg = lower_bound(x);
            if (itBeg == end()) {
                return end();
            }
            return *itBeg == x ? ++itBeg : itBeg;
        }

        reverse_iterator rend() { return reverse_iterator(--begin()); }
        reverse_iterator rbegin() { return reverse_iterator(--end()); }
        const_reverse_iterator rend() const{ return const_reverse_iterator(--begin()); }
        const_reverse_iterator rbegin() const{ return const_reverse_iterator(--end()); }
        iterator end() {
            if (tree_.getLast() == tree_.getRoot()) return NULL;
            return ++iterator(tree_.getLast());
        }
        const_iterator end() const {
            if (tree_.getLast() == tree_.getRoot()) return NULL;
            return ++iterator(tree_.getLast());
        }
        iterator begin() { return tree_.getStart(); }
        const_iterator begin() const { return tree_.getStart(); }

        pair<iterator, bool> insert(const value_type& x)
        {
            node_type* tmp = tree_.search(tree_.getRoot(), x);
            if (tmp != NULL) {
                return pair<iterator, bool>(iterator(tmp), false);
            }
            tree_.insert(x);
            ++size_;
            return pair<iterator, bool>(iterator(tree_.search(tree_.getRoot(), x)), true);
        }

        iterator insert(iterator /*pos*/, const value_type& x)
        {
            insert(x);
        }

        template <typename InputIter>
        void insert(InputIter first, InputIter second)
        {
            while (first != second) {
                insert(*first);
                ++first;
            }
        }

        void erase(iterator pos)
        {
            if (tree_.remove(*pos)) {
                --size_;
            }
        }

        size_type erase(const value_type& x)
        {
            bool removed = tree_.remove(x);
            if (removed) {
                --size_;
            }
            return removed;
        }

        void erase(iterator start, iterator end)
        {
            ft::vector<value_type> tmp(start, end);
            for (typename ft::vector<value_type>::iterator it = tmp.begin(); it != tmp.end(); it++) {
                if (tree_.remove(*it)) {
                    --size_;
                }
            }
        }

        key_compare key_comp() const
        {
            return key_compare();
        }

        value_compare value_comp() const
        {
            return value_compare();
        }
        void swap(set& x)
        {
            set tmp = x;
            x = *this;
            *this = tmp;
        }
        pair<const_iterator,const_iterator> equal_range (const key_type& k) const
        {
            return ft::make_pair(lower_bound(k), upper_bound(k));
        }
        pair<iterator,iterator> equal_range (const key_type& k)
        {
            return ft::make_pair(lower_bound(k), upper_bound(k));
        }

        ~set() {}
    private:
        tree tree_;
        node_pointer first_;
        node_pointer end_;
        size_type size_;
    };

} // namespace ft

template <class Type, class Comp>
bool operator == (const ft::set<Type, Comp>& lhs, const ft::set<Type, Comp>& rhs)
{
    if (lhs.size() != rhs.size()) return false;
    if (lhs.size() == 1) {
        return *lhs.begin() == *rhs.begin();
    }
    typename ft::set<Type, Comp>::iterator leftIt = lhs.begin();
    typename ft::set<Type, Comp>::iterator rightIt = rhs.begin();
    while (leftIt != lhs.end()) {
        const Type& tmp = *leftIt;
        const Type& tmp2 = *rightIt;
        if (tmp != tmp2)
            return false;
        leftIt++;
        rightIt++;
    }
    return true;
}

template <class Type, class Comp>
bool operator != (const ft::set<Type, Comp>& lhs, const ft::set<Type, Comp>& rhs)
{
    return !(lhs == rhs);
}

template <class Type, class Comp>
bool operator < (const ft::set<Type, Comp>& lhs, const ft::set<Type, Comp>& rhs)
{
    if (lhs.size() == rhs.size() && lhs.size() == 1) return *lhs.begin() < *rhs.begin();
    return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class Type, class Comp>
bool operator <= (const ft::set<Type, Comp>& lhs, const ft::set<Type, Comp>& rhs)
{
    return lhs < rhs || lhs == rhs;
}

template <class Type, class Comp>
bool operator > (const ft::set<Type, Comp>& lhs, const ft::set<Type, Comp>& rhs)
{
    return !(lhs <= rhs);
}

template <class Type, class Comp>
bool operator >= (const ft::set<Type, Comp>& lhs, const ft::set<Type, Comp>& rhs)
{
    return lhs > rhs || lhs == rhs;
}

#endif //CONTAINERS_SET_HPP
