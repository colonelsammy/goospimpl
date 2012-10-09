//          Copyright Malcolm Noyes 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef GOOS_PIMPL_BETWEEN_MATCHER_HPP
#define GOOS_PIMPL_BETWEEN_MATCHER_HPP

#include "description.hpp"
#include "matcher.hpp"

namespace goospimpl
{
    template <typename LowerType, typename UpperType>
    class BetweenMatcher
    {
    public:
        BetweenMatcher()
            : lower(), upper(0)
        {}
        explicit BetweenMatcher(const LowerType & l, const UpperType& u)
            : lower(l), upper(u)
        {
        }
        bool matches(const LowerType& v) const
        {
            return (v >= lower && v <= upper);
        }
        void describe_to(goospimpl::Description& desc) const
        {
            desc.appendText("value between ").appendValue(lower).appendText(" and ").appendValue(upper);
        }
        void describe_mismatch(const LowerType& v, goospimpl::Description& mismatch_desc) const
        {
            mismatch_desc.appendText("was ").appendValue(v);
        }
    private:
        const LowerType lower;
        const UpperType upper;
    };
}

#endif
