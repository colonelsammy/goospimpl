//          Copyright Malcolm Noyes 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef GOOS_PIMPL_ANY_VALUE_OF_ANY_TYPE_MATCHER_HPP
#define GOOS_PIMPL_ANY_VALUE_OF_ANY_TYPE_MATCHER_HPP

#include "description.hpp"
#include "value_holder.hpp"
#include <stdexcept>

namespace goospimpl
{
    template <typename T>
    class AnyValueOfAnyTypeMatcher
    {
        typedef T ValueType;
    public:
        AnyValueOfAnyTypeMatcher()
        {}
        template <typename U>
        bool matches(const U&) const
        {
            return true;
        }
        bool matchesType(const ValueHolder&) const
        {
            return true;
        }
        void describe_to(goospimpl::Description& desc) const
        {
            desc.appendText("value of any type");
        }
        void describe_mismatch(const ValueType&, goospimpl::Description&) const
        {
            // should never be called as should never fail
            throw std::runtime_error("describe_mismatch called for type anything (should never fail)");
        }
    };
}

#endif
