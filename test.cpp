//
// Created by Ilya Rozhnev on 15.05.2022.
//

#define RESET   "\033[0m"
#define BLACK_COLOR   "\033[30m"      /* Black */
#define RED_COLOR     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"
#include <iostream>
#define LOG_MSG(x) std::cout << YELLOW << x << RESET << std::endl

#define BOOST_TEST_MODULE ContainersTest
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include "containers/vector.hpp"
#include "containers/pair.hpp"
#include "containers/set.hpp"
#include "containers/stack.hpp"
#include "containers/map.hpp"
#include <vector>

BOOST_AUTO_TEST_SUITE(vector)
    BOOST_AUTO_TEST_CASE(vector_default_constructor)
    {
        LOG_MSG("ft/std::vector example;");
        ft::vector<int> v1;
        std::vector<int> v2;
        BOOST_CHECK_EQUAL(v1.size(), v2.size());
    }

    BOOST_AUTO_TEST_CASE(vector_copy_constructor)
    {
        LOG_MSG("ft::vector c(ref);");
        ft::vector<int> v1(100, 1);
        ft::vector<int> v2(v1);
        BOOST_CHECK_EQUAL(v1.size(), v2.size());
    }

    BOOST_AUTO_TEST_CASE(vector_assign_constructor)
    {
        LOG_MSG("ft::vector v1 = v2;");
        ft::vector<int> v1(100, 1);
        ft::vector<int> v2 = v1;
        BOOST_CHECK_EQUAL(v1.size(), v2.size());
    }

    BOOST_AUTO_TEST_CASE(vector_deep_copy)
    {
        LOG_MSG("ft::vector v1 = v2;");
        ft::vector<int> v1(100, 1);
        ft::vector<int> v2 = v1;
        v1[0] = 50;
        BOOST_CHECK(v1[0] != v2[0]);
    }

    BOOST_AUTO_TEST_CASE(vector_ct_iterators)
    {
        ft::vector<int> v1(10, 50);
        ft::vector<int> v2(v1.begin(), v1.end());
        BOOST_CHECK_EQUAL(v1.size(), v2.size());
        for (size_t i = 0; i < v1.size(); i++) {
            BOOST_CHECK_EQUAL(v1[i], v2[i]);
        }
    }

    BOOST_AUTO_TEST_CASE(vector_push_back)
    {
        ft::vector<int> v1;
        v1.push_back(50);
        BOOST_CHECK(v1[0] == 50);
    }


    BOOST_AUTO_TEST_CASE(vector_pop_back)
    {
        ft::vector<int> v1;
        v1.push_back(50);
        v1.pop_back();
        BOOST_CHECK(v1.empty());
    }

    BOOST_AUTO_TEST_CASE(vector_iterator_begin)
    {
        ft::vector<int> v1;
        v1.push_back(50);
        ft::vector<int>::iterator t = v1.begin();
        BOOST_CHECK_EQUAL(*t, v1[0]);
    }

    BOOST_AUTO_TEST_CASE(vector_iterator_end)
    {
        ft::vector<int> v2(10, 1);
        v2.push_back(11);
        BOOST_CHECK_EQUAL(*(--v2.end()), 11);
    }

    BOOST_AUTO_TEST_CASE(vector_iterator_rbegin)
    {
        ft::vector<int> v2(10, 1);
        v2.push_back(11);
        BOOST_CHECK_EQUAL(*v2.rbegin(), 11);
    }

    BOOST_AUTO_TEST_CASE(vector_iterator_rend)
    {
        ft::vector<int> v2(10, 1);
        v2.push_back(11);
        BOOST_CHECK_EQUAL(*(--v2.rend()), 1);
    }

    BOOST_AUTO_TEST_CASE(vector_at)
    {
        ft::vector<int> v2(10, 1);
        BOOST_CHECK_THROW(v2.at(11), std::exception);
        BOOST_CHECK_NO_THROW(v2.at(9));
    }

    BOOST_AUTO_TEST_CASE(vector_front)
    {
        ft::vector<int> v2;
        v2.push_back(1);
        v2.push_back(2);
        BOOST_CHECK_EQUAL(v2.front(), 1);
    }

    BOOST_AUTO_TEST_CASE(vector_back)
    {
        ft::vector<int> v2;
        v2.push_back(1);
        v2.push_back(2);
        BOOST_CHECK_EQUAL(v2.back(), 2);
    }

    BOOST_AUTO_TEST_CASE(vector_erase_iterators)
    {
        ft::vector<int> v2;
        for (int i = 1; i <= 10; i++) {
            v2.push_back(i * 10);
        }
        ft::vector<int>::iterator beg = v2.begin();
        v2.erase(beg);
        beg = v2.begin();
        BOOST_CHECK_EQUAL(*beg, 20);
        ft::vector<int>::iterator end = v2.begin()++;
        end++;
        end++;
        end++;
        v2.erase(beg, end);
        BOOST_CHECK_EQUAL(*v2.begin(), 50);
    }

    BOOST_AUTO_TEST_CASE(vector_swap)
    {
        ft::vector<int> v1(10, 0);
        ft::vector<int> v2(2, 50);
        v1.swap(v2);

        BOOST_CHECK_EQUAL(v2.size(), 10);
        BOOST_CHECK_EQUAL(v1.size(), 2);
        BOOST_CHECK_EQUAL(v1[0], 50);
        BOOST_CHECK_EQUAL(v2[0], 0);
    }

    BOOST_AUTO_TEST_CASE(vector_from_GIT_UT_resize)
    {
        int _ratio = 10000;
        std::vector<int> v;
        std::vector<int> vector;
        vector.assign(9900 * _ratio, 1);
        vector.resize(5000 * _ratio);
        vector.reserve(5000 * _ratio);
        v.push_back(vector.size());
        v.push_back(vector.capacity());
        vector.resize(7000 * _ratio);
        v.push_back(vector.size());
        v.push_back(vector.capacity());
        vector.resize(15300 * _ratio, int());
        v.push_back(vector.size());
        v.push_back(vector.capacity());
        v.push_back(vector[65]);

        ft::vector<int> vector2;
        std::vector<int> v2;
        vector2.assign(9900 * _ratio, 1);
        vector2.resize(5000 * _ratio);
        vector2.reserve(5000 * _ratio);
        v2.push_back(vector2.size());
        v2.push_back(vector2.capacity());
        vector2.resize(7000 * _ratio);
        v2.push_back(vector2.size());
        v2.push_back(vector2.capacity());
        vector2.resize(15300 * _ratio, int());
        v2.push_back(vector2.size());
        v2.push_back(vector2.capacity());
        v2.push_back(vector[65]);

        BOOST_CHECK_EQUAL(vector2.size(), vector.size());
        for (size_t i = 0; i < v.size(); i++) {
            if (v[i] != v2[i]) {
                std::cout <<"index: " << i << "(capacity) " << v[i] << " " << v2[i] << std::endl;
            }
        }
    }

    BOOST_AUTO_TEST_CASE(vector_insert_value_GIT_UT)
    {
        int _ratio = 10000;
        std::vector<int> v;
        std::vector<int> vector;

        vector.assign(2600 * _ratio, 1);
        v.push_back(*(vector.insert(vector.end() - 800 * _ratio, 44)));
        v.push_back(vector.size());
        v.push_back(vector.capacity());

        std::vector<int> v2;
        ft::vector<int> vector2;
        vector2.assign(2600 * _ratio, 1);
        v2.push_back(*(vector2.insert(vector2.end() - 800 * _ratio, 44)));
        v2.push_back(vector2.size());
        v2.push_back(vector2.capacity());
        for (size_t i = 0; i < v.size(); i++) {
            BOOST_CHECK_EQUAL(v[i], v2[i]);
        }
    }

    BOOST_AUTO_TEST_CASE(vector_insert_range_GIT_UT)
    {
        class B {
        public:
            char *l;
            int i;
            B():l(nullptr), i(1) {};
            B(const int &ex) {
                this->i = ex;
                this->l = new char('a');
            };
            virtual ~B() {
                delete this->l;
                this->l = nullptr;
            };
        };

        class A : public B {
        public:
            A():B(){};
            A(const B* ex){
                this->l = new char(*(ex->l));
                this->i = ex->i;
                if (ex->i == -1) throw "n";
            }
            ~A() {
                delete this->l;
                this->l = nullptr;
            };
        };

        int _ratio = 10000;
        std::vector<int> vector;
        std::vector<int> v;
        std::vector<int> tmp;
        tmp.assign(2600 * _ratio, 1);
        vector.assign(4200 * _ratio, 1);
        vector.insert(vector.end() - 1000 * _ratio, tmp.begin(), tmp.end());
        v.push_back(vector[3]);
        v.push_back(vector.size());
        v.push_back(vector.capacity());

        std::unique_ptr<B> k2(new B(3));
        std::unique_ptr<B> k3(new B(4));
        std::unique_ptr<B> k4(new B(-1));
        std::vector<A> vv;
        std::vector<B*> v1;

        v1.push_back(&(*k2));
        v1.push_back(&(*k3));
        v1.push_back(&(*k4));
        std::cout << sizeof (A) << " " << sizeof (B) << std::endl;
        try { vv.insert(vv.begin(), v1.begin(), v1.end()); }
        catch (...) {
            v.push_back(vv.size());
            v.push_back(vv.capacity());
        }

        ft::vector<int> v2;
        ft::vector<int> tmp2;
        ft::vector<int> vector2;
        tmp2.assign(2600 * _ratio, 1);
        vector2.assign(4200 * _ratio, 1);
        vector2.insert(vector2.end() - 1000 * _ratio, tmp2.begin(), tmp2.end());
        v2.push_back(vector2[3]);
        v2.push_back(vector2.size());
        v2.push_back(vector2.capacity());

        std::unique_ptr<B> k22(new B(3));
        std::unique_ptr<B> k32(new B(4));
        std::unique_ptr<B> k42(new B(-1));
        ft::vector<A> vv2;
        ft::vector<B*> v12;

        v12.push_back(&(*k22));
        v12.push_back(&(*k32));
        v12.push_back(&(*k42));
        try {
            vv2.insert(vv2.begin(), v12.begin(), v12.end());
        }
        catch (...) {
            v2.push_back(vv2.size());
            v2.push_back(vv2.capacity());
        }

        for (size_t i = 0; i < v.size(); i++) {
            BOOST_CHECK_EQUAL(v[i], v2[i]);
        }
    }

    BOOST_AUTO_TEST_CASE(vector_GIT_UT_swap)
    {
        int _ratio = 10000;

        std::vector<int> vector2;
        std::vector<int> v2;
        vector2.assign(1100 * _ratio, 11);
        std::vector<int> tmp0(500 * _ratio, 5), tmp22(1000 * _ratio, 10), tmp32(1500 * _ratio, 15), tmp42(3000 * _ratio, 30);
        v2.push_back(vector2[2]);
        v2.push_back(vector2.size());
        v2.push_back(vector2.capacity());
        long *adr12 = reinterpret_cast<long *>(&vector2);
        long *adr22 = reinterpret_cast<long *>(&tmp0);
        vector2.swap(tmp0);
        if (reinterpret_cast<long *>(&vector2) == adr12 && reinterpret_cast<long *>(&tmp0) == adr22)
            v2.push_back(1);
        v2.push_back(vector2[2]);
        v2.push_back(vector2.size());
        v2.push_back(vector2.capacity());
        vector2.swap(tmp32);
        v2.push_back(vector2[2]);
        v2.push_back(vector2.size());
        v2.push_back(vector2.capacity());
        std::swap(vector2, tmp22);
        v2.push_back(vector2[2]);
        v2.push_back(vector2.size());
        v2.push_back(vector2.capacity());
        std::swap(vector2, tmp42);
        v2.push_back(vector2[2]);
        v2.push_back(vector2.size());
        v2.push_back(vector2.capacity());


        ft::vector<int> vector;
        ft::vector<int> v;
        vector.assign(1100 * _ratio, 11);
        ft::vector<int> tmp(500 * _ratio, 5), tmp2(1000 * _ratio, 10), tmp3(1500 * _ratio, 15), tmp4(3000 * _ratio, 30);
        v.push_back(vector[2]);
        v.push_back(vector.size());
        v.push_back(vector.capacity());
        long *adr1 = reinterpret_cast<long *>(&vector);
        long *adr2 = reinterpret_cast<long *>(&tmp);
        vector.swap(tmp);
        if (reinterpret_cast<long *>(&vector) == adr1 && reinterpret_cast<long *>(&tmp) == adr2)
            v.push_back(1);
        v.push_back(vector[2]);
        v.push_back(vector.size());
        v.push_back(vector.capacity());
        vector.swap(tmp3);
        v.push_back(vector[2]);
        v.push_back(vector.size());
        v.push_back(vector.capacity());
        std::swap(vector, tmp2);
        v.push_back(vector[2]);
        v.push_back(vector.size());
        v.push_back(vector.capacity());
        std::swap(vector, tmp4);
        v.push_back(vector[2]);
        v.push_back(vector.size());
        v.push_back(vector.capacity());
        BOOST_CHECK_EQUAL(v.size(), v2.size());
        for (size_t i = 0; i < v.size(); i++) {
            BOOST_CHECK_EQUAL(v[i], v2[i]);
        }
    }

    BOOST_AUTO_TEST_CASE(vector_reserve)
    {
        ft::vector<int> v1(10, 5);
        BOOST_CHECK_THROW(v1.reserve(99999999999999999), std::exception);
        v1.reserve(11);
        BOOST_CHECK_EQUAL(v1.capacity(), 11);
    }

    BOOST_AUTO_TEST_CASE(vector_clear)
    {
        ft::vector<int> v1(100, 5);
        v1.clear();
        BOOST_CHECK(v1.empty());
    }

    BOOST_AUTO_TEST_CASE(vector_resize)
    {
        ft::vector<int> v1(10, 5);
        v1.resize(3);
        BOOST_CHECK_EQUAL(v1.size(), 3);
        v1.resize(5);
        BOOST_CHECK_EQUAL(v1.size(), 5);
    }

    BOOST_AUTO_TEST_CASE(vector_assign)
    {
        ft::vector<int> v1;
        ft::vector<int> v2(5, 10);
        v1.assign(v2.begin(), v2.end());
        BOOST_CHECK_EQUAL(v1.size(), 5);
        v1.assign(1, 12);
        BOOST_CHECK_EQUAL(v1[0], 12);

    }

    BOOST_AUTO_TEST_CASE(vector_insert)
    {
        ft::vector<int> v1(5, 10);
        v1.insert(v1.end(), 5, 20);
        BOOST_CHECK_EQUAL(v1.size(), 10);
        BOOST_CHECK_EQUAL(*v1.rbegin(), 20);
        v1.insert(v1.end(), 21);
        BOOST_CHECK_EQUAL(*v1.rbegin(), 21);

    }

    BOOST_AUTO_TEST_CASE(vector_compare)
    {
        ft::vector<int> v1(5, 10);
        ft::vector<int> v2(v1);
        BOOST_CHECK(v1 == v2);
        v2[4] = 1;
        BOOST_CHECK(v1 != v2);
        BOOST_CHECK(v1 > v2);
        v2[4] = 12;
        BOOST_CHECK(v1 < v2);
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(pair)

    BOOST_AUTO_TEST_CASE(pair_constructors)
    {
        ft::pair<std::string, int> test;
        BOOST_CHECK_EQUAL(test.first, "");
        test.first = "TEST";
        ft::pair<std::string, int> test2(test);
        BOOST_CHECK_EQUAL(test2.first, test.first);
    }

    BOOST_AUTO_TEST_CASE(make_pair)
    {
        auto test = ft::make_pair(std::string("Hello"), 42);
        BOOST_CHECK_EQUAL(test.first, "Hello");
        BOOST_CHECK_EQUAL(test.second, 42);
    }

    BOOST_AUTO_TEST_CASE(pair_copy)
    {
        auto test = ft::make_pair(1, 'a');
        auto test2 = test;
        BOOST_CHECK_EQUAL(test2.first, 1);
        BOOST_CHECK_EQUAL(test2.second, 'a');
        test2.first = 2;
        BOOST_CHECK(test2.first != test.first);
    }

    BOOST_AUTO_TEST_CASE(pair_compare)
    {
        auto test = ft::make_pair(1, std::string("test"));
        auto test2(test);
        BOOST_CHECK(test == test2);
        test.first = 2;
        BOOST_CHECK(test != test2);
        BOOST_CHECK(test > test2);
        test.first = 0;
        BOOST_CHECK(test < test2);
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(stack)

    BOOST_AUTO_TEST_CASE(stack_default_ct)
    {
        ft::stack<int> ok;
    }

    BOOST_AUTO_TEST_CASE(stack_push)
    {
        ft::stack<int> test;
        test.push(5);
        test.push(10);
        BOOST_CHECK_EQUAL(test.top(), 10);
    }

    BOOST_AUTO_TEST_CASE(stack_pop)
    {
        ft::stack<int> test;
        test.push(5);
        test.push(10);
        test.pop();
        BOOST_CHECK_EQUAL(test.top(), 5);
    }

    BOOST_AUTO_TEST_CASE(stack_compare)
    {
        ft::stack<int> test;
        ft::stack<int> test2;

        test.push(5);
        test2.push(5);

        BOOST_CHECK(test == test2);
        test.push(10);
        BOOST_CHECK(test != test2);
        BOOST_CHECK(test > test2);
        BOOST_CHECK(test2 < test);
    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(set)

    BOOST_AUTO_TEST_CASE(set_GIT_UT_clear)
    {
        int _ratio = 10000;
        ft::set<int> st;
        std::vector<int> v;
        st.clear();
        for (int i = 0; i < 25 * _ratio; ++i)
            st.insert(i);
        v.push_back(st.size());
        st.clear();
        v.push_back(st.size());
        typename ft::set<int>::iterator it = st.begin();
        if (it == st.end())
            v.push_back(1);
    }

    BOOST_AUTO_TEST_CASE(set_GIT_UT_copy_assign)
    {
        int _ratio = 10000;
        ft::set<int> st;
        for (int i = 0; i < 20 * _ratio; ++i)
            st.insert(i);
        ft::set<int> st2;
        for (int i = 20 * _ratio; i < 40 * _ratio; ++i)
            st2.insert(i);
        st2 = st;
    }

    BOOST_AUTO_TEST_CASE(set_GIT_UT_reverse_iter)
    {
        std::vector<int> v;

        ft::set<int> st;
        st.insert(5);
        st.insert(3);
        st.insert(7);
        ft::set<int>::reverse_iterator rit = st.rbegin();
        ft::set<int>::reverse_iterator rit2 = st.rend();
        v.push_back(*rit);
        rit++;
        rit2--;
        v.push_back(*rit);
        v.push_back(*rit2);
        rit++;
        v.push_back(*rit == *rit2);
        v.push_back(rit == rit2);
        rit2--;
        v.push_back(*rit);
        v.push_back(*rit2);
        v.push_back(*rit2 > *rit);
        v.push_back(*rit2 < *rit);
        v.push_back(*(--rit));
        v.push_back(*(++rit2));
        v.push_back(*(rit--));
        v.push_back(*(rit2++));
    }

    BOOST_AUTO_TEST_CASE(set_GIT_UT_compare_class)
    {
        ft::vector<int> fin;
        std::vector<int> finStd;
        {
            ft::set<int, std::greater<int> > st;
            std::set<int, std::greater<int> > stdSt;
            stdSt.insert(3);
            stdSt.erase(3);
            st.insert(3);
            st.erase(3);
            if (stdSt.begin() == stdSt.end()) {
                finStd.push_back(1);
            }
            if (st.begin() == st.end()) {
                fin.push_back(1);
            }
        }
        {
            ft::set<int, std::less<int> > st;
            std::set<int, std::less<int> > stdSt;
            st.insert(16);
            st.insert(8);
            st.insert(23);
            st.insert(7);
            st.insert(19);
            st.insert(29);
            st.insert(41);
            st.insert(4);
            st.insert(11);

            stdSt.insert(16);
            stdSt.insert(8);
            stdSt.insert(23);
            stdSt.insert(7);
            stdSt.insert(19);
            stdSt.insert(29);
            stdSt.insert(41);
            stdSt.insert(4);
            stdSt.insert(11);
            for (std::set<int>::iterator it = stdSt.begin(); it != stdSt.end(); it++) {
                finStd.push_back(*it);
            }
            for (std::set<int>::iterator it = --stdSt.end(); it != stdSt.begin(); it--) {
                finStd.push_back(*it);
            }

            for (ft::set<int>::iterator it = st.begin(); it != st.end(); it++) {
                fin.push_back(*it);
            }
            for (ft::set<int>::iterator it = --st.end(); it != st.begin(); it--) {
                fin.push_back(*it);
            }
        }
        BOOST_CHECK_EQUAL(fin.size(), finStd.size());
        for (size_t i = 0; i < fin.size(); i++) {
            BOOST_CHECK_EQUAL(fin[i], finStd[i]);
        }
    }

    BOOST_AUTO_TEST_CASE(set_compare)
    {
        {
            ft::set<int> s1, st1;
            s1.insert(1); st1.insert(1);
            s1.insert(2); st1.insert(2);
            s1.insert(3); st1.insert(3);
            s1.insert(4); st1.insert(4);
            s1.insert(5); st1.insert(5);

            BOOST_CHECK(s1 == st1);
            s1.insert(6);
            BOOST_CHECK(s1 != st1);
            BOOST_CHECK(s1 > st1);
            st1.insert(7);
            BOOST_CHECK(s1 < st1);
        }
        ft::set<std::string> s1, s2;
        s1.insert("123"); s2.insert("122");
        BOOST_CHECK(s1 != s2);

    }

    BOOST_AUTO_TEST_CASE(set_erase_GIT_UT)
    {
        std::vector<int> v;
        std::vector<int> v2;
        int _ratio = 10000;
        {
            ft::set<int> st;
            v.push_back(st.erase(3));
            for (int i = 0; i < 30 * _ratio; ++i)
                st.insert(i);
            ft::set<int>::iterator it = st.begin();
            v.push_back(*it);
            v.push_back(st.erase(-5));
            v.push_back(st.size());
            v.push_back(st.erase(0));
            v.push_back(st.size());
            ft::set<int>::iterator it4 = st.begin();
            for (; it4 != st.end(); it4 = st.begin()) {
                st.erase(*it4);
            }
            v.push_back(st.erase(30 * _ratio - 1));
            v.push_back(st.size());
            ft::set<int> st2;
            for (int i = 0; i < 10 ; ++i)
                st2.insert(i);
            st2.erase(2);
            st2.erase(7);
            ft::set<int>::iterator it3 = st2.begin();
            for (; it3 != st2.end(); ++it3) {
                v.push_back(*it3);
            }
        }
        {
            std::set<int> st;
            v2.push_back(st.erase(3));
            for (int i = 0; i < 30 * _ratio; ++i)
                st.insert(i);
            std::set<int>::iterator it = st.begin();
            v2.push_back(*it);
            v2.push_back(st.erase(-5));
            v2.push_back(st.size());
            v2.push_back(st.erase(0));
            v2.push_back(st.size());
            std::set<int>::iterator it4 = st.begin();
            for (; it4 != st.end(); it4 = st.begin())
                st.erase(*it4);
            v2.push_back(st.erase(30 * _ratio - 1));
            v2.push_back(st.size());
            std::set<int> st2;
            for (int i = 0; i < 10 ; ++i)
                st2.insert(i);
            st2.erase(2);
            st2.erase(7);
            std::set<int>::iterator it3 = st2.begin();
            for (; it3 != st2.end(); ++it3) {
                v2.push_back(*it3);
            }
        }
        BOOST_CHECK_EQUAL(v.size(), v2.size());
        for (size_t i = 0; i < v.size(); i++) {
            BOOST_CHECK_EQUAL(v[i], v2[i]);
        }
    }

    BOOST_AUTO_TEST_CASE(set_lower_bound_GIT_UT)
    {
        int _ratio = 10000;
        std::vector<int> v;
        std::vector<int> v2;
        {
            std::set<int> st;
            std::set<int, std::greater<int> > st2;
            st.insert(10);
            st2.insert(10);
            if (st.lower_bound(11) == st.end())
                v.push_back(1);
            if (st2.lower_bound(1) == st2.end())
                v.push_back(1);
            st.insert(20);
            st.insert(30);
            st.insert(40);
            st.insert(50);
            st.insert(60);
            st2.insert(20);
            st2.insert(30);
            st2.insert(40);
            st2.insert(50);
            st2.insert(60);
            std::set<int>::iterator it;
            for (int i = 1; i < 60; i += 10) {
                it = st.lower_bound(i);
                int temp = *it;
                v.push_back(temp);
            }
            for (int i = 11; i < 70; i += 10) {
                it = st2.lower_bound(i);
                v.push_back(*it);
            }
            std::set<int> st3;
            for (int i = 0; i < 50 * _ratio; ++i) {
                st3.insert(i);
            }
            st3.lower_bound(49 * _ratio);
        }
        {
            ft::set<int> st;
            ft::set<int, std::greater<int> > st2;
            st.insert(10);
            st2.insert(10);
            if (st.lower_bound(11) == st.end())
                v2.push_back(1);
            if (st2.lower_bound(1) == st2.end())
                v2.push_back(1);
            st.insert(20);
            st.insert(30);
            st.insert(40);
            st.insert(50);
            st.insert(60);
            st2.insert(20);
            st2.insert(30);
            st2.insert(40);
            st2.insert(50);
            st2.insert(60);
            ft::set<int>::iterator it;
            for (int i = 1; i < 60; i += 10) {
                it = st.lower_bound(i);
                v2.push_back(*it);
            }
            for (int i = 11; i < 70; i += 10) {
                it = st2.lower_bound(i);
                v2.push_back(*it);
            }
            ft::set<int> st3;
            for (int i = 0; i < 50 * _ratio; ++i) {
                st3.insert(i);
            }
            st3.lower_bound(49 * _ratio);
        }
        BOOST_CHECK_EQUAL(v.size(), v2.size());
        for (size_t i = 0; i < v.size(); i++) {
            BOOST_CHECK_EQUAL(v[i], v2[i]);
        }
    }

    BOOST_AUTO_TEST_CASE(set_equal_Range_GIT_UT)
    {
        std::vector<int> v;
        std::vector<int> v2;
        {
            std::set<int> st;
            st.insert(10);
            st.insert(20);
            st.insert(30);
            st.insert(40);
            st.insert(50);
            st.insert(60);
            const std::pair<std::set<int>::const_iterator , std::set<int>::const_iterator>& pair = st.equal_range(10);
            const std::pair<std::set<int>::const_iterator , std::set<int>::const_iterator>& pair2 = st.equal_range(11);
            const std::pair<std::set<int>::const_iterator , std::set<int>::const_iterator>& pair3 = st.equal_range(1);
            v.push_back(*(pair.first));
            v.push_back(*(pair.second));
            v.push_back(*(pair2.first));
            v.push_back(*(pair2.second));
            v.push_back(*(pair3.first));
            v.push_back(*(pair3.second));
        }
        {
            ft::set<int> st;
            st.insert(10);
            st.insert(20);
            st.insert(30);
            st.insert(40);
            st.insert(50);
            st.insert(60);
            const ft::pair<ft::set<int>::const_iterator , ft::set<int>::const_iterator>& pair = st.equal_range(10);
            const ft::pair<ft::set<int>::const_iterator , ft::set<int>::const_iterator>& pair2 = st.equal_range(11);
            const ft::pair<ft::set<int>::const_iterator , ft::set<int>::const_iterator>& pair3 = st.equal_range(1);
            v2.push_back(*(pair.first));
            v2.push_back(*(pair.second));
            v2.push_back(*(pair2.first));
            v2.push_back(*(pair2.second));
            v2.push_back(*(pair3.first));
            v2.push_back(*(pair3.second));
        }
        BOOST_CHECK_EQUAL(v.size(), v2.size());
        for (size_t i = 0; i < v.size(); i++) {
            BOOST_CHECK_EQUAL(v[i], v2[i]);
        }

    }


    BOOST_AUTO_TEST_CASE(set_compare_GIT_UT)
    {
        class SetBoolTest {
        public:
            std::set<int> s1, s2, s3, s4;
            std::set<std::string> s5, s6, s7, s8, s9;
            ft::set<int> st1, st2, st3, st4;
            ft::set<std::string> st5, st6, st7, st8, st9;

            SetBoolTest() {
                s1.insert(2); st1.insert(2);
                s2.insert(3); st2.insert(3);
                s3.insert(3); st3.insert(3);
                s4.insert(4); st4.insert(4);
                s4.insert(4); st4.insert(4);
                s5.insert("122"); st5.insert("122");
                s6.insert("123"); st6.insert("123");
                s7.insert("124"); st7.insert("124");
                s8.insert("12"); st8.insert("12");
                s9.insert("123"); st9.insert("123");
            }
        };
        std::vector<int> result;
        std::vector<int> result2;
        SetBoolTest st;
        result.push_back(st.s1 == st.s1); result.push_back(st.s3 == st.s3); result.push_back(st.s5 == st.s9);
        result.push_back(st.s1 == st.s2); result.push_back(st.s3 == st.s4); result.push_back(st.s6 == st.s6);
        result.push_back(st.s1 == st.s3); result.push_back(st.s4 == st.s4); result.push_back(st.s6 == st.s7);
        result.push_back(st.s1 == st.s4); result.push_back(st.s5 == st.s5); result.push_back(st.s6 == st.s8);
        result.push_back(st.s2 == st.s2); result.push_back(st.s5 == st.s6); result.push_back(st.s6 == st.s9);
        result.push_back(st.s2 == st.s3); result.push_back(st.s5 == st.s7); result.push_back(st.s7 == st.s7);
        result.push_back(st.s2 == st.s4); result.push_back(st.s5 == st.s8); result.push_back(st.s7 == st.s8);
        result.push_back(st.s7 == st.s9); result.push_back(st.s8 == st.s8); result.push_back(st.s8 == st.s9);
        result.push_back(st.s9 == st.s9);

        result2.push_back(st.st1 == st.st1); result2.push_back(st.st3 == st.st3); result2.push_back(st.st5 == st.st9);
        result2.push_back(st.st1 == st.st2); result2.push_back(st.st3 == st.st4); result2.push_back(st.st6 == st.st6);
        result2.push_back(st.st1 == st.st3); result2.push_back(st.st4 == st.st4); result2.push_back(st.st6 == st.st7);
        result2.push_back(st.st1 == st.st4); result2.push_back(st.st5 == st.st5); result2.push_back(st.st6 == st.st8);
        result2.push_back(st.st2 == st.st2); result2.push_back(st.st5 == st.st6); result2.push_back(st.st6 == st.st9);
        result2.push_back(st.st2 == st.st3); result2.push_back(st.st5 == st.st7); result2.push_back(st.st7 == st.st7);
        result2.push_back(st.st2 == st.st4); result2.push_back(st.st5 == st.st8); result2.push_back(st.st7 == st.st8);
        result2.push_back(st.st7 == st.st9); result2.push_back(st.st8 == st.st8); result2.push_back(st.st8 == st.st9);
        result2.push_back(st.st9 == st.st9);
        BOOST_CHECK(result == result2);
    }

    BOOST_AUTO_TEST_CASE(set_default_ct)
    {
        ft::set<int> test;
    }

    BOOST_AUTO_TEST_CASE(set_copy_container_ct)
    {
        ft::vector<int> test;

        for (int i = 0; i < 50; i++) {
            test.push_back(i);
        }
        ft::set<int> test1(test.begin(), test.end());
        int num = 0;
        for (const int& it : test1) {
            BOOST_CHECK_EQUAL(it, num);
            num++;
        }
        BOOST_CHECK_EQUAL(num, 50);
    }

    BOOST_AUTO_TEST_CASE(set_deep_copy_ct)
    {
        ft::vector<int> tmp;

        for (int i = 0; i < 50; i++) {
            tmp.push_back(i);
        }
        ft::set<int> test(tmp.begin(), tmp.end());
        ft::set<int> test1(test);
        BOOST_CHECK_EQUAL(test.size(), test1.size());
        test.insert(51);
        BOOST_CHECK(test.size() != test1.size());
    }

    BOOST_AUTO_TEST_CASE(set_insert_value)
    {
        ft::set<int> test;
        for (int i = 0; i < 10; i++) {
            test.insert(i);
        }
        int controlNum = 0;
        for (const int& num : test) {
            BOOST_CHECK_EQUAL(num, controlNum);
            controlNum++;
        }
        BOOST_CHECK_EQUAL(controlNum, 10);
    }

    BOOST_AUTO_TEST_CASE(set_insert_from_iter)
    {
        ft::set<int> test;
        ft::vector<int> v;
        for (int i = 0; i < 10; i++) {
            v.push_back(i);
        }
        test.insert(v.begin(), v.end());

        int controlNum = 0;
        for (const int& num : test) {
            BOOST_CHECK_EQUAL(num, controlNum);
            controlNum++;
        }
        BOOST_CHECK_EQUAL(controlNum, 10);
    }

    BOOST_AUTO_TEST_CASE(set_erase)
    {
        ft::set<int> test;
        ft::vector<int> v;
        for (int i = 0; i < 10; i++) {
            v.push_back(i);
        }
        test.insert(v.begin(), v.end());
        BOOST_CHECK_EQUAL(test.erase(9), 1);
        BOOST_CHECK_EQUAL(test.size(), 9);
        BOOST_CHECK_EQUAL(test.erase(10), 0);
    }

    BOOST_AUTO_TEST_CASE(set_erase_from_iterators)
    {
        ft::set<int> test;
        ft::vector<int> v;
        for (int i = 0; i < 10; i++) {
            v.push_back(i);
        }
        test.insert(v.begin(), v.end());
        auto tmp = ++(test.begin());
        tmp++;
        test.erase(test.begin()++, ++tmp);
        int check = 3;
        for (auto it = test.begin(); it != test.end(); it++) {
            BOOST_CHECK_EQUAL(*it, check);
            check++;
        }
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(map)

    BOOST_AUTO_TEST_CASE(map_default_ct)
    {
        ft::map<int, std::string> test;
    }

    BOOST_AUTO_TEST_CASE(map_ct_GIT_UT)
    {
        int _ratio = 10000;
        std::vector<int> v;
        ft::map<int, int> mp;
        for (int i = 0, j = 10; i < 30 * _ratio; ++i, ++j) {
            mp.insert(ft::make_pair(i, j));
        }
        ft::map<int, int> mp2(mp.begin(), mp.end());
        ft::map<int, int>::iterator it = mp2.begin();
        for (int i = 0; i < 30 * _ratio; ++i, it++) {
            v.push_back(it->first);
            v.push_back(it->second);
        }
        mp.erase(1);
    }

    BOOST_AUTO_TEST_CASE(map_ct_iterator)
    {
        ft::vector<ft::pair<int, std::string> > test;
        for (int i = 0; i < 10; i++) {
            test.push_back(ft::make_pair(i, std::string("test_string")));
        }
        ft::map<int, std::string> map(test.begin(), test.end());
        int i = 0;
        for (ft::map<int, std::string>::iterator it = map.begin(); it != map.end(); it++) {
            BOOST_CHECK_EQUAL(it->first, i);
            i++;
        }
    }

    BOOST_AUTO_TEST_CASE(map_deep_copy_ct)
    {
        ft::vector<ft::pair<int, std::string> > test;
        for (int i = 0; i < 10; i++) {
            test.push_back(ft::make_pair(i, std::string("test_string")));
        }
        ft::map<int, std::string> map(test.begin(), test.end());
        ft::map<int, std::string> map2(map);
        map.begin()->second = "test_string1";
        BOOST_CHECK(map.begin()->second != map2.begin()->second);
    }

    BOOST_AUTO_TEST_CASE(map_operator_sq_bracket)
    {
        ft::vector<ft::pair<int, std::string> > test;
        for (int i = 0; i < 10; i++) {
            test.push_back(ft::make_pair(i, std::string("test_string")));
        }
        ft::map<int, std::string> map(test.begin(), test.end());
        map[2] = "test";
        BOOST_CHECK_EQUAL(map[2], "test");
        map[10] = "test2";
        BOOST_CHECK_EQUAL(map[10], "test2");
    }

    BOOST_AUTO_TEST_CASE(map_insert)
    {
        ft::map<int, std::string> map;
        auto it = map.insert(ft::make_pair(1, std::string("test")));
        BOOST_CHECK_EQUAL(it.second, true);
        BOOST_CHECK_EQUAL(it.first->first, 1);
        BOOST_CHECK_EQUAL(it.first->second, "test");
        BOOST_CHECK_EQUAL(map[1], "test");
    }

    BOOST_AUTO_TEST_CASE(map_insert_iterator)
    {
        ft::vector<ft::pair<int, std::string> > test;
        for (int i = 0; i < 10; i++) {
            test.push_back(ft::make_pair(i, std::string("test_string")));
        }
        ft::map<int, std::string> map;
        map.insert(test.begin(), test.end());
        BOOST_CHECK_EQUAL(map.size(), 10);
    }

    BOOST_AUTO_TEST_CASE(map_assign_overload_GIT_UT)
    {
        int _ratio = 10000;
        ft::map<int, int> mp;
        std::vector<int> v;
        for (int i = 0, j = 10; i < 20 * _ratio; ++i, ++j)
            mp.insert(ft::make_pair(i, j));
        ft::map<int, int> mp2;
        for (int i = 20 * _ratio, j = 200010; i < 40 * _ratio; ++i, ++j)
            mp2.insert(ft::make_pair(i, j));
        mp2 = mp;
        ft::map<int, int>::iterator it = mp2.begin();
        for (; it != mp2.end(); it++) {
            v.push_back(it->first);
            v.push_back(it->second);
        }
        v.push_back(mp2.size());
    }

    BOOST_AUTO_TEST_CASE(map_equal_range_GIT_UT)
    {
        std::vector<int> v;
        ft::map<int, int> mp;
        mp.insert(ft::make_pair(10, 10));
        mp.insert(ft::make_pair(20, 20));
        mp.insert(ft::make_pair(30, 30));
        mp.insert(ft::make_pair(40, 40));
        mp.insert(ft::make_pair(50, 50));
        mp.insert(ft::make_pair(60, 60));
        const ft::pair<ft::map<int, int>::const_iterator , ft::map<int, int>::const_iterator>& pair = mp.equal_range(10);
        v.push_back(pair.first->first);
        v.push_back(pair.first->second);
    }

    BOOST_AUTO_TEST_CASE(map_key_comp_GIT_UT)
    {
        std::vector<int> v;
        ft::map<int, int> mp;
        ft::map<int, int, std::greater<int> > mp2;
        ft::map<int, int, std::equal_to<int> > mp3;
        v.push_back(mp.key_comp()(1, 2));
        v.push_back(mp2.key_comp()(1, 2));
        v.push_back(mp3.key_comp()(1, 2));
    }

    BOOST_AUTO_TEST_CASE(map_erase_key_GIT_UT)
    {
        std::vector<int> v;
        std::vector<int> v2;
        int _ratio = 10000;
        {

            ft::map<int, int> mp;
            v.push_back(mp.erase(3));
            for (int i = 0, j = 0; i < 30 * _ratio; ++i, ++j)
                mp.insert(ft::make_pair(i, j));
            ft::map<int, int>::iterator it = mp.begin();
            v.push_back(it->first);
            v.push_back(mp.erase(-5));
            v.push_back(mp.size());
            v.push_back(mp.erase(0));
            v.push_back(mp.size());
            it = mp.begin();
            v.push_back(it->first);
            ft::map<int, int>::iterator it4 = mp.begin();
            for (; it4 != mp.end(); it4 = mp.begin())
                mp.erase(it4->first);
            v.push_back(mp.erase(30 * _ratio - 1));
            v.push_back(mp.size());
            ft::map<int, int> mp2;
            for (int i = 0, j = 0; i < 10 ; ++i, ++j)
                mp2.insert(ft::make_pair(i, j));
            mp2.erase(2);
            mp2.erase(7);
            typename ft::map<int, int>::iterator it3 = mp2.begin();
            for (; it3 != mp2.end(); ++it3) {
                v.push_back(it3->first);
                v.push_back(it3->second);
            }
        }
        {
            std::map<int, int> mp;
            v2.push_back(mp.erase(3));
            for (int i = 0, j = 0; i < 30 * _ratio; ++i, ++j)
                mp.insert(std::make_pair(i, j));
            std::map<int, int>::iterator it = mp.begin();
            v2.push_back(it->first);
            v2.push_back(mp.erase(-5));
            v2.push_back(mp.size());
            v2.push_back(mp.erase(0));
            v2.push_back(mp.size());
            it = mp.begin();
            v2.push_back(it->first);
            std::map<int, int>::iterator it4 = mp.begin();
            for (; it4 != mp.end(); it4 = mp.begin())
                mp.erase(it4->first);
            v2.push_back(mp.erase(30 * _ratio - 1));
            v2.push_back(mp.size());
            std::map<int, int> mp2;
            for (int i = 0, j = 0; i < 10 ; ++i, ++j)
                mp2.insert(std::make_pair(i, j));
            mp2.erase(2);
            mp2.erase(7);
            std::map<int, int>::iterator it3 = mp2.begin();
            for (; it3 != mp2.end(); ++it3) {
                v2.push_back(it3->first);
                v2.push_back(it3->second);
            }
        }
        BOOST_CHECK_EQUAL(v.size(), v2.size());
        for (size_t i = 0; i < v.size(); i++) {
            BOOST_CHECK_EQUAL(v[i], v2[i]);
        }
    }

    BOOST_AUTO_TEST_CASE(map_less_GIT_UT)
    {
        class MapBoolTest {
        public:
            std::map<int, int> m1, m2, m3, m4;
            std::map<std::string, std::string> m5, m6, m7, m8, m9;
            ft::map<int, int> mp1, mp2, mp3, mp4;
            ft::map<std::string, std::string> mp5, mp6, mp7, mp8, mp9;

            MapBoolTest() {
                m1.insert(std::make_pair(2, 3)); mp1.insert(ft::make_pair(2, 3));
                m2.insert(std::make_pair(3, 3)); mp2.insert(ft::make_pair(3, 3));
                m3.insert(std::make_pair(3, 4)); mp3.insert(ft::make_pair(3, 4));
                m4.insert(std::make_pair(4, 4)); mp4.insert(ft::make_pair(4, 4));
                m4.insert(std::make_pair(4, 5)); mp4.insert(ft::make_pair(4, 5));
                m5.insert(std::make_pair("123", "123")); mp5.insert(ft::make_pair("123", "123"));
                m6.insert(std::make_pair("123", "124"));
                mp6.insert(ft::make_pair("123", "124"));
                m7.insert(std::make_pair("124", "123")); mp7.insert(ft::make_pair("124", "123"));
                m8.insert(std::make_pair("12", "123")); mp8.insert(ft::make_pair("12", "123"));
                m9.insert(std::make_pair("123", "12")); mp9.insert(ft::make_pair("123", "12"));
            }
        };
        MapBoolTest mt;
        std::vector<int> result, result2;
        result.push_back(mt.m1 < mt.m1); result.push_back(mt.m3 < mt.m3); result.push_back(mt.m5 < mt.m9);
        result.push_back(mt.m1 < mt.m2); result.push_back(mt.m3 < mt.m4); result.push_back(mt.m6 < mt.m6);
        result.push_back(mt.m1 < mt.m3); result.push_back(mt.m4 < mt.m4); result.push_back(mt.m6 < mt.m7);

        result.push_back(mt.m1 < mt.m4);

        result.push_back(mt.m5 < mt.m5);

        result.push_back(mt.m6 < mt.m8);

        result.push_back(mt.m2 < mt.m2);
        result.push_back(mt.m5 < mt.m6);
        result.push_back(mt.m6 < mt.m9);

        result.push_back(mt.m2 < mt.m3);

        result.push_back(mt.m5 < mt.m7); result.push_back(mt.m7 < mt.m7);
        result.push_back(mt.m2 < mt.m4); result.push_back(mt.m5 < mt.m8); result.push_back(mt.m7 < mt.m8);
        result.push_back(mt.m7 < mt.m9); result.push_back(mt.m8 < mt.m8); result.push_back(mt.m8 < mt.m9);
        result.push_back(mt.m9 < mt.m9);

        result2.push_back(mt.mp1 < mt.mp1); result2.push_back(mt.mp3 < mt.mp3); result2.push_back(mt.mp5 < mt.mp9);
        result2.push_back(mt.mp1 < mt.mp2); result2.push_back(mt.mp3 < mt.mp4); result2.push_back(mt.mp6 < mt.mp6);
        result2.push_back(mt.mp1 < mt.mp3); result2.push_back(mt.mp4 < mt.mp4); result2.push_back(mt.mp6 < mt.mp7);
        result2.push_back(mt.mp1 < mt.mp4);

        result2.push_back(mt.mp5 < mt.mp5);

        result2.push_back(mt.mp6 < mt.mp8);

        result2.push_back(mt.mp2 < mt.mp2);
        result2.push_back(mt.mp5 < mt.mp6);
        result2.push_back(mt.mp6 < mt.mp9);

        result2.push_back(mt.mp2 < mt.mp3);

        result2.push_back(mt.mp5 < mt.mp7); result2.push_back(mt.mp7 < mt.mp7);
        result2.push_back(mt.mp2 < mt.mp4); result2.push_back(mt.mp5 < mt.mp8); result2.push_back(mt.mp7 < mt.mp8);
        result2.push_back(mt.mp7 < mt.mp9); result2.push_back(mt.mp8 < mt.mp8); result2.push_back(mt.mp8 < mt.mp9);
        result2.push_back(mt.mp9 < mt.mp9);

        BOOST_CHECK_EQUAL(result.size(), result2.size());
        for (size_t i = 0; i < result2.size(); i++) {
            BOOST_CHECK_EQUAL(result2[i], result[i]);
        }
    }

    BOOST_AUTO_TEST_CASE(map_erase_key)
    {
        ft::map<int, std::string> map;
        map.insert(ft::make_pair(1, std::string("test")));
        map.erase(1);
        BOOST_CHECK_EQUAL(0, map.size());
    }

    BOOST_AUTO_TEST_CASE(map_upper_bound)
    {
        ft::vector<ft::pair<int, std::string> > test;
        for (int i = 0; i < 10; i++) {
            test.push_back(ft::make_pair(i * 10, std::string("test_string")));
        }
        ft::map<int, std::string> test2;
        test2.insert(test.begin(), test.end());
        {
            auto it = test2.upper_bound(60);
            BOOST_CHECK_EQUAL(it->first, 70);
        }
        {
            auto it = test2.upper_bound(-1);
            BOOST_CHECK_EQUAL(it->first, 0);
        }
    }

    BOOST_AUTO_TEST_CASE(map_lower_bound)
    {
        ft::vector<ft::pair<int, std::string> > test;
        for (int i = 0; i < 10; i++) {
            test.push_back(ft::make_pair(i * 10, std::string("test_string")));
        }
        ft::map<int, std::string> test2;
        test2.insert(test.begin(), test.end());
        {
            auto it = test2.lower_bound(10);
            BOOST_CHECK_EQUAL(it->first, 10);
        }
        {
            auto it = test2.lower_bound(9);
            BOOST_CHECK_EQUAL(it->first, 10);
        }
    }

    BOOST_AUTO_TEST_CASE(map_erase_iterator)
    {
        ft::vector<ft::pair<int, std::string> > test;
        for (int i = 0; i < 10; i++) {
            test.push_back(ft::make_pair(i, std::string("test_string")));
        }
        ft::map<int, std::string> test2;
        test2.insert(test.begin(), test.end());
        auto bIt = test2.lower_bound(1);
        auto eIt = test2.upper_bound(3);
        test2.erase(bIt, eIt);
        BOOST_CHECK_EQUAL(test2.begin()->first, 0);
        BOOST_CHECK_EQUAL((++test2.begin())->first, 4);
    }

    BOOST_AUTO_TEST_CASE(map_equal_range)
    {
        ft::vector<ft::pair<int, std::string> > test;
        for (int i = 0; i < 10; i++) {
            test.push_back(ft::make_pair(i, std::string("test_string")));
        }
        ft::map<int, std::string> test2;
        test2.insert(test.begin(), test.end());
        {
            auto t = test2.equal_range(-1);
            BOOST_CHECK_EQUAL(t.first->first, 0);
            BOOST_CHECK_EQUAL(t.second->first, 0);
        }
        {
            auto t = test2.equal_range(2);
            BOOST_CHECK_EQUAL(t.first->first, 2);
            BOOST_CHECK_EQUAL(t.second->first, 3);
        }
    }

BOOST_AUTO_TEST_SUITE_END()