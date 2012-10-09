//          Copyright Malcolm Noyes 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef GOOS_PIMPL_ANY_VALUE_OF_TYPE_MATCHER_HPP
#define GOOS_PIMPL_ANY_VALUE_OF_TYPE_MATCHER_HPP

#include "description.hpp"
#include <typeinfo>
#include <stdexcept>

namespace goospimpl
{
    template <typename T>
    class AnyValueOfTypeMatcher
    {
        typedef T ValueType;
    public:
        AnyValueOfTypeMatcher()
        {}
        bool matches(const ValueType& v) const
        {
            return true;
        }
        template <typename U>
        bool matches(const U& v) const
        {
            return false;
        }
        void describe_to(goospimpl::Description& desc) const
        {
            desc.appendText("value of type ").appendText(typeid(ValueType).name());
        }
        void describe_mismatch(const ValueType& v, goospimpl::Description& mismatch_desc) const
        {
            // should never be called as should fail on type at higher level
            throw std::runtime_error("describe_mismatch called for type any (should never fail)");
        }
    };
}

#endif
