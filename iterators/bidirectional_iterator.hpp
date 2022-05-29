//
// Created by Ilya Rozhnev on 02.05.2022.
//

#ifndef CONTAINERS_BIDIRECTIONAL_ITERATOR_HPP
#define CONTAINERS_BIDIRECTIONAL_ITERATOR_HPP
#include "../core/BaseIterator.hpp"
#include "../core/BRTree.hpp"

namespace ft
{
    template <class Type>
    struct bidirectional_iterator
    {
        typedef typename iterator<bidirectional_iterator_tag, Type>::iterator_category iterator_category;
        typedef typename iterator<bidirectional_iterator_tag, Type>::reference reference;
        typedef typename iterator<bidirectional_iterator_tag, Type>::pointer pointer;
        typedef typename iterator<bidirectional_iterator_tag, Type>::difference_type difference_type;
        typedef typename iterator<bidirectional_iterator_tag, Type>::value_type value_type;
        typedef const Type* const_pointer;
        typedef b_list<value_type>* node_pointer;
        typedef value_type& value_reference;
        typedef const value_type& const_value_reference;

        bidirectional_iterator() : prev_ptr_(NULL), ptr_(NULL) {}
        bidirectional_iterator(node_pointer ptr) : prev_ptr_(ptr), ptr_(ptr) {}
        bidirectional_iterator(const bidirectional_iterator& ref)
        {
            *this = ref;
        }

        bidirectional_iterator& operator = (const bidirectional_iterator& ref)
        {
            if (this == &ref) {
                return *this;
            }
            prev_ptr_ = ref.prev_ptr_;
            ptr_ = ref.ptr_;
            return *this;
        }

        bidirectional_iterator& operator ++ ()
        {
            if (ptr_ == NULL && prev_ptr_ != NULL) {
                ptr_ = prev_ptr_;
                prev_ptr_ = NULL;
                return *this;
            }
            prev_ptr_ = ptr_;
            if (this->ptr_ == NULL) {
                return *this;
            }
            if (this->ptr_->r_node != NULL && !isLeaf(this->ptr_->r_node)) {
                this->ptr_ = this->ptr_->r_node;
                while (this->ptr_->l_node != NULL && !isLeaf(this->ptr_->l_node))
                    this->ptr_ = this->ptr_->l_node;
            }
            else {
                node_pointer tmp = this->ptr_->p_node == NULL ? this->ptr_ : this->ptr_->p_node;
                while (tmp != NULL && this->ptr_ == tmp->r_node) {
                    this->ptr_ = tmp;
                    tmp = tmp->p_node;
                }
                if (this->ptr_->r_node != tmp)
                    this->ptr_ = tmp;
            }
            if (ptr_ &&
            ptr_->r_node && isLeaf(ptr_->r_node) &&
            ptr_->l_node && isLeaf(ptr_->l_node) && !ptr_->p_node)
                ptr_ = NULL;
            return *this;
        }

        bidirectional_iterator operator ++ (int)
        {
            bidirectional_iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        bidirectional_iterator operator -- (int)
        {
            bidirectional_iterator tmp(*this);
            --(*this);
            return tmp;
        }

        bidirectional_iterator& operator -- ()
        {
            if (this->ptr_ == NULL) {
                ptr_ = prev_ptr_;

                return *this;
            }
            if (this->ptr_->l_node != NULL && !isLeaf(this->ptr_->l_node)) {
                this->ptr_ = this->ptr_->l_node;
                while (this->ptr_->r_node != NULL && !isLeaf(this->ptr_->r_node))
                    this->ptr_ = this->ptr_->r_node;
            }
            else {
                node_pointer tmp = this->ptr_->p_node == NULL ? this->ptr_ : this->ptr_->p_node;
                while (tmp != NULL && this->ptr_ == tmp->l_node) {
                    this->ptr_ = tmp;
                    tmp = tmp->p_node;
                }
                if (this->ptr_->l_node != tmp)
                    this->ptr_ = tmp;
            }
            return *this;
        }

        const_value_reference & operator * () const
        {
            return *this->ptr_->value;
        }

        value_reference & operator * ()
        {
            return *this->ptr_->value;
        }

        pointer operator -> () { return &operator*(); }
        const_pointer operator -> () const { const_pointer tmp = &operator*(); return tmp;}
        node_pointer base() const { return ptr_; }

    private:
        node_pointer prev_ptr_;
        node_pointer ptr_;

    };

    template <class Type>
    typename bidirectional_iterator<Type>::difference_type operator ==
    (const bidirectional_iterator<Type>& lhs, const bidirectional_iterator<Type>& rhs)
    { return lhs.base() == rhs.base(); }

    template <class Type>
    typename bidirectional_iterator<Type>::difference_type operator ==
    (bidirectional_iterator<Type>& lhs, bidirectional_iterator<Type>& rhs)
    { return lhs.base() == rhs.base(); }

    template <class Type>
    typename bidirectional_iterator<Type>::difference_type operator !=
            (const bidirectional_iterator<Type>& lhs, const bidirectional_iterator<Type>& rhs)
    { return !(lhs.base() == rhs.base()); }

    template <class Type>
    typename bidirectional_iterator<Type>::difference_type operator !=
            (bidirectional_iterator<Type>& lhs, bidirectional_iterator<Type>& rhs)
    { return !(lhs.base() == rhs.base()); }
}


#endif //CONTAINERS_BIDIRECTIONAL_ITERATOR_HPP
