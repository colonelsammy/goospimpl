//          Copyright Malcolm Noyes 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef GOOS_PIMPL_EQUALS_WITH_EPSILON_MATCHER_HPP
#define GOOS_PIMPL_EQUALS_WITH_EPSILON_MATCHER_HPP

#include "description.hpp"

namespace goospimpl
{
    template <typename T, typename EpsilonType>
    class EqualsWithEpsilonMatcher
    {
        typedef T ValueType;
    public:
        EqualsWithEpsilonMatcher()
            : expected(), epsilon(0)
        {}
        explicit EqualsWithEpsilonMatcher(const ValueType & value, const EpsilonType& e)
            : expected(value), epsilon(e)
        {
        }
        bool matches(const ValueType& v) const
        {
            return (expected <= (v + epsilon) && expected >= (v - epsilon));
        }
        void describe_to(goospimpl::Description& desc) const
        {
            desc.appendText("value ").appendValue(expected);
        }
        void describe_mismatch(const ValueType& v, goospimpl::Description& mismatch_desc) const
        {
            mismatch_desc.appendText("was ").appendValue(v).appendText(" (+-").appendValue(epsilon).appendText(")");
        }
    private:
        ValueType expected;
        EpsilonType epsilon;
    };
}

#endif
