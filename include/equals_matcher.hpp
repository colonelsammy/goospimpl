//          Copyright Malcolm Noyes 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef GOOS_PIMPL_EQUALS_MATCHER_HPP
#define GOOS_PIMPL_EQUALS_MATCHER_HPP

#include "description.hpp"

namespace goospimpl
{
    template <typename T>
    class EqualsMatcher
    {
        typedef T ValueType;
    public:
        EqualsMatcher()
            : expected()
        {}
        explicit EqualsMatcher(const ValueType & value)
            : expected(value)
        {
        }
        bool matches(const ValueType& v) const
        {
            return (expected == v);
        }
        void describe_to(goospimpl::Description& desc) const
        {
            desc.appendText("value ").appendValue(expected);
        }
        void describe_mismatch(const ValueType& v, goospimpl::Description& mismatch_desc) const
        {
            mismatch_desc.appendText("was ").appendValue(v);
        }
    private:
        ValueType expected;
    };

}

#endif
