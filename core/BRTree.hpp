//
// Created by Ilya Rozhnev on 09.05.2022.
//

#ifndef CONTAINERS_BRTREE_HPP
#define CONTAINERS_BRTREE_HPP
#include "less.hpp"
#include "Equal.hpp"
#include <memory>
#define RED false
#define BLACK true
#define LEFT false
#define RIGHT true
#include <iostream>

namespace ft
{
    template <class node_pointer>
    bool isLeaf(node_pointer node)
    {

        return node->value == NULL;
    }

    template <class T>
    struct b_list
    {
        T* value;
        struct b_list* l_node;
        struct b_list* r_node;
        struct b_list* p_node;
        bool color;
        b_list(T* x = NULL, b_list* prev = NULL, b_list* left = NULL, b_list* right = NULL)
                : value(x)
                , l_node(prev)
                , r_node(left)
                , p_node(right)
                , color(RED)
        {}
        b_list(const b_list& ref) { *this = ref; }
        b_list& operator = (const b_list& ref)
        {
            if (this == &ref) {
                return *this;
            }
            l_node = ref.l_node;
            r_node = ref.r_node;
            p_node = ref.p_node;
            color = ref.color;
            value = ref.value;
            return *this;
        }
        ~b_list() {}
    };

    template <class Type
            , class Comp = ft::less<Type>
            , class Equal = ft::Equal<Type>
            , class Node = b_list<Type>
            , class TypeAlloc = std::allocator<Type>
            , class NodeAlloc = std::allocator<Node> >
    class tree_handler
    {
    public:
        typedef tree_handler self;
        typedef Type value_type;
        typedef Node node_type;
        typedef Node* node_pointer;
        typedef NodeAlloc node_alloc;
        typedef TypeAlloc type_alloc;
        typedef Equal equal_comp;
        typedef Comp compare;
        typedef size_t size_type;

        tree_handler(const compare& comp = compare(), const equal_comp& eq = equal_comp(), const type_alloc& typeAlloc = type_alloc(), const node_alloc& nodeAlloc = node_alloc())
                : root_(NULL)
                , nodeAlloc_(nodeAlloc)
                , typeAlloc_(typeAlloc)
                , less_(comp)
                , equal_(eq)
        {}

        ~tree_handler()
        {
            clearAll(root_);
        }

        tree_handler(const tree_handler& ref)
        {
            *this = ref;
        }

        void copyAll(node_pointer n)
        {
            if (n == NULL) return;

            copyAll(n->l_node);
            copyAll(n->r_node);
            if (!isLeaf(n)) {
                insert(*n->value);
            }
        }

        tree_handler& operator = (const tree_handler& ref)
        {
            if (this == &ref) {
                return *this;
            }
            clearAll(root_);
            copyAll(ref.root_);
            return *this;
        }

        bool remove(const value_type& val)
        {
            node_pointer tmp = search(root_, val);
            if (tmp == NULL) {
                return false;
            }
            deleteOneChild(tmp);
            root_ = getRoot();
            return true;
        }

        void insert(const value_type& val)
        {
            if (root_ == NULL) {
                root_ = allocateNode(val);
                root_->color = BLACK;
            }
            else {
                recInsert(val);
            }
            root_ = getRoot();
        }

        node_pointer getRoot() const
        {
            node_pointer tmp = root_;
            if (tmp == NULL) return NULL;
            while (tmp->p_node != NULL) {
                tmp = tmp->p_node;
            }
            return tmp;
        }
        node_pointer getStart() const
        {
            node_pointer tmp = root_;
            if (tmp == NULL) return NULL;
            while (tmp->l_node != NULL && !isLeaf(tmp->l_node)) {
                tmp = tmp->l_node;
            }
            return tmp;
        }

        node_pointer getLast() const
        {
            node_pointer tmp = root_;
            if (tmp == NULL) return NULL;
            while (tmp->r_node != NULL && !isLeaf(tmp->r_node)) {
                tmp = tmp->r_node;
            }
            return tmp;
        }

        void print(node_pointer root)
        {
            if (root == NULL)
            {
                return;
            }
            if (!isLeaf(root->l_node)) {
                print(root->l_node);
            }
            if (!isLeaf(root)) {
                std::cout << *root->value << " ";
            }
            if (!isLeaf(root->r_node)) {
                print(root->r_node);
            }
        }

        void clearAll(node_pointer& n)
        {
            if (n == NULL) return;

            clearAll(n->l_node);
            clearAll(n->r_node);
            if (!isLeaf(n)) {
                deallocateNode(n);
                n = NULL;
            }
        }

        node_pointer& getRootRef()
        {
            return root_;
        }

        node_pointer search(node_pointer node, const value_type& x) const
        {
            if (node == NULL || isLeaf(node))
                return NULL;
            if (equal_(*node->value, x)) {
                return node;
            }
            if (!less_(x , *node->value))
                return search(node->r_node, x);
            else
                return search(node->l_node, x);
        }

    private:

        void deallocateNode(node_pointer n)
        {
            if (n->value != NULL) {
                typeAlloc_.destroy(n->value);
                typeAlloc_.deallocate(n->value, 1);
                n->value = NULL;
            }
            nodeAlloc_.destroy(n);
            nodeAlloc_.deallocate(n, 1);
        }

        node_pointer getGrandparent(node_pointer node)
        {
            if ((node != NULL) && (node->p_node != NULL)) {
                return node->p_node->p_node;
            }
            return NULL;
        }

        node_pointer getUncle(node_pointer node)
        {
            node_pointer g = getGrandparent(node);
            if (g == NULL) {
                return NULL; // No grandparent means no uncle
            }
            if (node->p_node == g->r_node) {
                return g->l_node;
            }
            return g->r_node;
        }

        node_pointer getSibling(node_pointer node)
        {
            if (node == node->p_node->r_node) {
                return node->p_node->l_node;
            }
            else {
                return node->p_node->r_node;
            }
        }

        node_pointer allocateLeaf()
        {
            leaf_.r_node = NULL;
            leaf_.l_node = NULL;
            leaf_.p_node = NULL;
            leaf_.value = NULL;
            leaf_.color = BLACK;
            return &leaf_;
        }

        void replaceNode(node_pointer n, node_pointer child) {

            child->p_node = n->p_node;
            if (n == n->p_node->l_node) {
                n->p_node->l_node = child;
            }
            else {
                n->p_node->r_node = child;
            }
        }

        node_pointer deleteCase0(node_pointer n)
        {
            node_pointer child = !isLeaf(n->l_node) ? n->l_node : n->r_node;
            if (n == NULL) {
                return NULL;
            }
            while (child && child->r_node != NULL && !isLeaf(child->r_node)) {
                child = child->r_node;
            }
            if (n == root_ &&
            (!n->l_node || isLeaf(n->l_node)) &&
            (!n->r_node || isLeaf(n->r_node))) {
                deallocateNode(n);
                root_ = NULL;
                return root_;
            }
            *n->value = *child->value;
            return child;
        }

        void deleteOneChild(node_pointer n)
        {
            if (n == root_) {
                n = deleteCase0(n);
                if (n == NULL) {
                    return;
                }
                if (isLeaf(n->r_node) && isLeaf(n->l_node)) {
                    bool side = LEFT;
                    root_ = n->p_node;
                    if (root_->r_node == n) side = RIGHT;
                    deallocateNode(n);
                    if (side == RIGHT) root_->r_node = NULL;
                    return;
                }
                n->color = BLACK;
            }
            if (less_(*n->value, *root_->value) && n->l_node != NULL &&
            !isLeaf(n->l_node) && n->r_node != NULL && !isLeaf(n->r_node)) {
                node_pointer tmp = n->r_node;
                while (tmp->r_node != NULL && !isLeaf(tmp->r_node)) {
                    tmp = tmp->r_node;
                }
                *n->value = *tmp->value;
                n = tmp;
            }
            else if (!less_(*n->value, *root_->value) && n->r_node != NULL &&
                     !isLeaf(n->r_node) && n->l_node != NULL && !isLeaf(n->l_node)) {
                node_pointer tmp = n->l_node;
                while (tmp->l_node != NULL && !isLeaf(tmp->l_node)) {
                    tmp = tmp->l_node;
                }
                *n->value = *tmp->value;
                n = tmp;
            }
            node_pointer child = isLeaf(n->r_node) ? n->l_node : n->r_node;
            replaceNode(n, child);
            if (n->color == BLACK) {
                if (child->color == RED) {
                    child->color = BLACK;
                }
                else {
                    deleteCase1(child);
                }
            }
            deallocateNode(n);
            n = allocateLeaf();
        }

        void deleteCase1(node_pointer n)
        {
            if (n->p_node != NULL) {
                deleteCase2(n);
            }
        }

        void deleteCase2(node_pointer n)
        {
            node_pointer s = getSibling(n);

            if (s->color == RED) {
                n->p_node->color = RED;
                s->color = BLACK;
                if (n == n->p_node->l_node) {
                    rotateLeft(n->p_node);
                }
                else {
                    rotateRight(n->p_node);
                }
            }
            deleteCase3(n);
        }

        void deleteCase3(node_pointer n)
        {
            node_pointer s = getSibling(n);

            if ((n->p_node->color == BLACK) && (s->color == BLACK) && (s->l_node->color == BLACK) &&(s->r_node->color == BLACK)) {
                s->color = RED;
                deleteCase1(n->p_node);
            }
            else
                deleteCase4(n);
        }

        void deleteCase4(node_pointer n)
        {
            node_pointer s = getSibling(n);

            if ((n->p_node->color == RED) && (s->color == BLACK) && (s->l_node->color == BLACK) && (s->r_node->color == BLACK)) {
                s->color = RED;
                n->p_node->color = BLACK;
            } else
                deleteCase5(n);
        }

        void deleteCase5(node_pointer n)
        {
            node_pointer s = getSibling(n);

            if  (s->color == BLACK) {
                if ((n == n->p_node->l_node) && (s->r_node->color == BLACK) && (s->l_node->color == RED)) {
                    s->color = RED;
                    s->l_node->color = BLACK;
                    rotateRight(s);
                }
                else if ((n == n->p_node->r_node) && (s->l_node->color == BLACK) && (s->r_node->color == RED)) {
                    s->color = RED;
                    s->r_node->color = BLACK;
                    rotateLeft(s);
                }
            }
            deleteCase6(n);
        }

        void deleteCase6(node_pointer n)
        {
            node_pointer s = getSibling(n);

            s->color = n->p_node->color;
            n->p_node->color = BLACK;

            if (n == n->p_node->l_node) {
                s->r_node->color = BLACK;
                rotateLeft(n->p_node);
            }
            else {
                s->l_node->color = BLACK;
                rotateRight(n->p_node);
            }
        }

        void rotateLeft(node_pointer node)
        {
            node_pointer pivot = node->r_node;

            pivot->p_node = node->p_node;
            if (node->p_node != NULL) {
                if (node->p_node->l_node == node) {
                    node->p_node->l_node = pivot;
                }
                else {
                    node->p_node->r_node = pivot;
                }
            }

            node->r_node = pivot->l_node;
            if (pivot->l_node != NULL)
                pivot->l_node->p_node = node;

            node->p_node = pivot;
            pivot->l_node = node;
        }

        void rotateRight(node_pointer node)
        {
            node_pointer pivot = node->l_node;

            pivot->p_node = node->p_node;
            if (node->p_node != NULL) {
                if (node->p_node->l_node == node) {
                    node->p_node->l_node = pivot;
                }
                else {
                    node->p_node->r_node = pivot;
                }
            }

            node->l_node = pivot->r_node;
            if (pivot->r_node != NULL)
                pivot->r_node->p_node = node;

            node->p_node = pivot;
            pivot->r_node = node;
        }

        node_pointer root_;
        node_alloc nodeAlloc_;
        type_alloc typeAlloc_;
        compare less_;
        equal_comp equal_;
        node_type leaf_;

        node_pointer allocateNode(const value_type& x)
        {
            node_pointer node = nodeAlloc_.allocate(1);
            nodeAlloc_.construct(node, node_type());
            node->value = typeAlloc_.allocate(1);
            typeAlloc_.construct(node->value, x);
            node->l_node = allocateLeaf();
            node->r_node = allocateLeaf();
            node->color = RED;
            return node;
        }

        void recInsert(const value_type& x)
        {
            node_pointer newNode = root_;
            node_pointer prevNode = NULL;
            bool side = LEFT;
            while (!isLeaf(newNode)) {
                if (less_(x, *newNode->value)) {
                    prevNode = newNode;
                    newNode = newNode->l_node;
                    side = LEFT;
                }
                else {
                    prevNode = newNode;
                    newNode = newNode->r_node;
                    side = RIGHT;
                }
            }
            newNode = allocateNode(x);
            if (side == RIGHT) {
                prevNode->r_node = newNode;
            }
            else {
                prevNode->l_node = newNode;
            }

            while (root_->p_node != NULL) {
                root_ = root_->p_node;
            }
            newNode->p_node = prevNode;
            insertCase1(newNode);
            if (newNode->color == RED) {
                if (newNode->p_node && newNode->p_node->color == RED) {
                    newNode->color = BLACK;
                }
            }
        }

        void insertCase1(node_pointer n)
        {
            if (n->p_node == NULL)
                n->color = BLACK;
            else
                insertCase2(n);
        }
        void insertCase2(node_pointer n)
        {
            if (n->p_node->color == BLACK) {
                return; /* Tree is still valid */
            }
            else {
                insertCase3(n);
            }
        }

        void insertCase3(node_pointer n)
        {
            node_pointer u = getUncle(n);
            node_pointer g;

            if ((u != NULL) && (u->color == RED)) {
                n->p_node->color = BLACK;
                u->color = BLACK;
                g = getGrandparent(n);
                g->color = RED;
                insertCase1(g);
            }
            else {
                insertCase4(n);
            }
        }

        void insertCase4(node_pointer n)
        {
            node_pointer g = getGrandparent(n);

            if ((n == n->p_node->r_node) && (n->p_node == g->l_node)) {
                rotateLeft(n->p_node);
                n = n->l_node;
            }
            else if ((n == n->p_node->l_node) && (n->p_node == g->r_node)) {
                rotateRight(n->p_node);
                n = n->r_node;
            }
            insertCase5(n);
        }
        void insertCase5(node_pointer n)
        {
            node_pointer g = getGrandparent(n);

            n->p_node->color = BLACK;
            g->color = RED;
            if ((n == n->p_node->l_node) && (n->p_node == g->l_node)) {
                rotateRight(g);
            } else {
                rotateLeft(g);
            }
        }
    };
} // namespace ft

#endif //CONTAINERS_BRTREE_HPP
