//
// Created by Ilya Rozhnev on 03.04.2022.
//
#include "Assert.hpp"
namespace ft
{
    detail::PseudoStaticAssert::PseudoStaticAssert(const std::string &msg) : std::logic_error(msg) {}

    void assertWithMsg(bool expression, const std::string& msg)
    {
        if (expression)
            return;
        throw detail::PseudoStaticAssert(msg);
    }
}