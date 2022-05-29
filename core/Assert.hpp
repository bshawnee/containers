//
// Created by Ilya Rozhnev on 03.04.2022.
//

#ifndef CONTAINERS_ASSERT_HPP
#define CONTAINERS_ASSERT_HPP
#include <stdexcept>

namespace ft
{
    namespace detail
    {
        //pseudo-static Assertion
        class PseudoStaticAssert : public std::logic_error
        {
        public:
            PseudoStaticAssert(const std::string& msg);
        };
    }

    void assertWithMsg(bool expression, const std::string& msg);

}

#endif //CONTAINERS_ASSERT_HPP
