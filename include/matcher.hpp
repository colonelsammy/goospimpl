//          Copyright Malcolm Noyes 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef GOOS_PIMPL_MATCHER_HPP
#define GOOS_PIMPL_MATCHER_HPP

#include "value_holder.hpp"
#include <cassert>

namespace goospimpl
{
    class Description;

    struct MatcherContent : CountedType
    {
        virtual void describe_to(Description& desc) const = 0;
        virtual void describe_mismatch(const ValueHolder& v, Description& mismatch_desc) const = 0;
        virtual bool operator()(const ValueHolder& v) const = 0;
    };

    class MatcherHolder : public CountedHolder<MatcherHolder, MatcherContent>
    {
    public:
        explicit MatcherHolder(MatcherContent* p)
            : CountedHolder(p)
        {
        }
        MatcherHolder& operator=(MatcherHolder rhs)
        {
            rhs.swapCountedHolder(*this);
            return *this;
        }

        void describe_to(Description& desc) const
        {
            assert(content);
            content->describe_to(desc);
        }
        void describe_mismatch(const ValueHolder& v, Description& mismatch_desc) const
        {
            assert(content);
            content->describe_mismatch(v, mismatch_desc);
        }
        bool operator()(const ValueHolder& v) const
        {
            assert(content);
            return (*content)(v);
        }
        bool matches(const ValueHolder& v) const
        {
            assert(content);
            return (*content)(v);
        }
    private:
        MatcherHolder();
    };
}

#endif
