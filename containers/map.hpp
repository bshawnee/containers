//
// Created by Ilya Rozhnev on 14.05.2022.
//

#ifndef CONTAINERS_MAP_HPP
#define CONTAINERS_MAP_HPP
#include "../core/BRTree.hpp"
#include "../containers/pair.hpp"
#include "../core/Equal.hpp"
#include "../iterators/reverse_iterator.hpp"
#include "../iterators/bidirectional_iterator.hpp"
#include "../core/Is_integral.hpp"
#define MAYBE_UNUSED __attribute__((unused))
namespace ft
{
    template <class Key, class Type, class Compare = less<const Key>, class Alloc = std::allocator<pair<const Key,Type> > >
    class map
    {
    public:
        typedef Key key_type;
        typedef Type mapped_type;
        typedef pair<const key_type,mapped_type> value_type;
        typedef Alloc allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef Compare key_compare;
        typedef b_list<value_type> node_type;
        typedef key_compare value_compare;
        typedef map_less<key_compare, value_type> key_less;
        typedef node_type* node_pointer;
        typedef const bidirectional_iterator<value_type> const_iterator;
        typedef bidirectional_iterator<value_type> iterator;
        typedef reverse_iterator<const_iterator> const_reverse_iterator;
        typedef reverse_iterator<iterator> reverse_iterator;
        typedef typename Iterators_traits<iterator>::difference_type difference_type;
        typedef typename allocator_type::size_type size_type;
        typedef tree_handler<value_type, key_less, EqualMap<value_type>, node_type, allocator_type> tree;

        explicit map(MAYBE_UNUSED const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
        : tree_(key_less(comp), EqualMap<value_type>(), alloc)
        , size_(0)
        {}

        template <class InputIterator>
        map(InputIterator first, InputIterator last, MAYBE_UNUSED const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
        : tree_(key_less(comp), EqualMap<value_type>(), alloc)
        , size_(0)
        {
            while (first != last) {
                tree_.insert(*first);
                ++first;
                ++size_;
            }
        }

        map(const map& x)
        : tree_(key_less(), EqualMap<value_type>(), allocator_type())
        , size_(0)
        {
            *this = x;
        }

        map& operator = (const map& ref)
        {
            if (this == &ref) {
                return *this;
            }
            clear();
            insert(ref.begin(), ref.end());
            return *this;
        }

        iterator begin() { return tree_.getStart(); }
        iterator end()
        {
            if (tree_.getLast() == tree_.getRoot()) return NULL;
            return ++iterator(tree_.getLast());
        }
        const_iterator begin() const { return tree_.getStart(); }
        const_iterator end() const
        {
            if (tree_.getLast() == tree_.getRoot()) return NULL;
            return ++iterator(tree_.getLast());
        }
        reverse_iterator rbegin() { return const_reverse_iterator(--end()); }
        reverse_iterator rend() { return const_reverse_iterator(--begin()); }
        const_reverse_iterator rbegin() const { return const_reverse_iterator(--end()); }
        const_reverse_iterator rend() const { return const_reverse_iterator(--begin()); }

        bool empty() const { return size_ == 0; }
        size_type size() const { return  size_; }
        bool max_size() const { return allocator_type().max_size(); }

        mapped_type& operator [] (const key_type& n)
        {
            node_pointer tmp = tree_.search(tree_.getRoot(), ft::make_pair(n, mapped_type()));
            if (tmp != NULL) {
                return tmp->value->second;
            }
            tree_.insert(ft::make_pair(n, mapped_type()));
            ++size_;
            return tree_.search(tree_.getRoot(), ft::make_pair(n, mapped_type()))->value->second;
        }

        pair<iterator,bool> insert (const value_type& x)
        {
            node_type* tmp = tree_.search(tree_.getRoot(), x);
            if (tmp != NULL) {
                return pair<iterator, bool>(iterator(tmp), false);
            }
            tree_.insert(x);
            ++size_;
            return pair<iterator, bool>(iterator(tree_.search(tree_.getRoot(), x)), true);
        }
        iterator insert (iterator /*position*/, const value_type& val)
        {
            insert(val);
        }
        template <class InputIterator>
        void insert (InputIterator first, InputIterator last)
        {
            while (first != last) {
                insert(*first);
                ++first;
            }
        }

        void erase (iterator position, typename Enable_if<!ft::Is_integral<iterator>::value, void>::type* = NULL)
        {
            if (tree_.remove(*position))
                --size_;
        }
        size_type erase (const key_type& k)
        {
            bool removed = tree_.remove(ft::make_pair(k, mapped_type()));
            if (removed) {
                --size_;
            }
            return removed;
        }
        void erase (iterator first, iterator last)
        {
            ft::map<key_type, mapped_type> t(first, last);
            for (typename ft::map<key_type, mapped_type>::iterator it = t.begin(); it != t.end(); it++) {
                erase(it->first);
            }
        }

        void swap(map& x)
        {
            map tmp = x;
            x = *this;
            *this = tmp;
        }

        void clear()
        {
            node_pointer root = tree_.getRoot();
            tree_.clearAll(root);
            tree_.getRootRef() = NULL;
            size_ = 0;
        }

        iterator find (const key_type& k)
        {
            return tree_.search(tree_.getRoot(), make_pair(k, mapped_type()));
        }
        const_iterator find (const key_type& k) const
        {
            find(k);
        }

        size_type count (const key_type& k) const
        {
            if (tree_.search(tree_.getRoot(), make_pair(k, mapped_type())) == NULL) {
                return 0;
            }
            return 1;
        }

        iterator lower_bound (const key_type& k)
        {
            key_compare comp = key_compare();
            iterator itBeg = begin();
            while ( itBeg != end()) {
                if (comp(k, itBeg->first) || k == itBeg->first) {
                    break;
                }
                itBeg++;
            }
            return itBeg == end() ? end() : itBeg;
        }

        const_iterator lower_bound(const value_type& x) const
        {
            key_compare comp = key_compare ();
            iterator itBeg = begin();
            while (itBeg != end() || x == *itBeg) {
                if (comp(x, itBeg->first) || x == itBeg->first) {
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
            return itBeg->first == k ? ++itBeg : itBeg;
        }

        const_iterator upper_bound(const value_type& x) const
        {
            iterator itBeg = lower_bound(x);
            if (itBeg == end()) {
                return end();
            }
            return itBeg->first == x ? ++itBeg : itBeg;
        }

        pair<const_iterator,const_iterator> equal_range (const key_type& k) const
        {
            return ft::make_pair(lower_bound(k), upper_bound(k));
        }

        pair<iterator,iterator> equal_range (const key_type& k)
        {
            return ft::make_pair(lower_bound(k), upper_bound(k));
        }

        allocator_type get_allocator() const
        {
            return allocator_type();
        }
        key_compare key_comp() const
        {
            return Compare();
        }
    private:
        tree tree_;
        size_type size_;
        key_less less_;
    };

    template <class Key, class Value>
    bool operator == (const ft::map<Key, Value>& lhs, const ft::map<Key, Value>& rhs)
    {
        if (lhs.size() != rhs.size()) return false;
        if (lhs.size() == 1) {
            return *lhs.begin() == *rhs.begin();
        }
        typename ft::map<Key, Value>::iterator leftIt = lhs.begin();
        typename ft::map<Key, Value>::iterator rightIt = rhs.begin();
        while (leftIt != lhs.end()) {
            if (*leftIt != *rightIt)
                return false;
            leftIt++;
            rightIt++;
        }
        return true;
    }

    template <class Key, class Value>
    bool operator != (const ft::map<Key, Value>& lhs, const ft::map<Key, Value>& rhs)
    {
        return !(lhs == rhs);
    }

    template <class Key, class Value>
    bool operator < (const ft::map<Key, Value>& lhs, const ft::map<Key, Value>& rhs)
    {
        if (lhs.size() == rhs.size() && lhs.size() == 1) return *lhs.begin() < *rhs.begin();
        if (lhs.size() != rhs.size()) return lhs.size() < rhs.size();
        if (lhs.size() == 1) {
            return *lhs.begin() == *rhs.begin();
        }
        typename ft::map<Key, Value>::iterator leftIt = lhs.begin();
        typename ft::map<Key, Value>::iterator rightIt = rhs.begin();
        while (leftIt != lhs.end()) {
            if (*leftIt < *rightIt)
                return true;
            leftIt++;
            rightIt++;
        }
        return false;
    }

    template <class Key, class Value>
    bool operator <= (const ft::map<Key, Value>& lhs, const ft::map<Key, Value>& rhs)
    {
        return lhs < rhs || lhs == rhs;
    }

    template <class Key, class Value>
    bool operator > (const ft::map<Key, Value>& lhs, const ft::map<Key, Value>& rhs)
    {
        return !(lhs <= rhs);
    }

    template <class Key, class Value>
    bool operator >= (const ft::map<Key, Value>& lhs, const ft::map<Key, Value>& rhs)
    {
        return lhs > rhs || lhs == rhs;
    }

} // ft

#endif //CONTAINERS_MAP_HPP
