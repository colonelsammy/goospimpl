//          Copyright Malcolm Noyes 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef GOOS_PIMPL_ANY_VALUE_OF_ANY_TYPE_MATCHER_HPP
#define GOOS_PIMPL_ANY_VALUE_OF_ANY_TYPE_MATCHER_HPP

#include "description.hpp"
#include "matcher.hpp"
#include <stdexcept>

namespace goospimpl
{
    struct AnyValueOfAnyTypeMatcher : public CountedContent<MatcherContent>
    {
    public:
        typedef void ValueType;
        AnyValueOfAnyTypeMatcher()
        {}
        virtual const std::type_info & type() const
        {
            return typeid(void);
        }
        virtual void describe_to(Description& desc) const
        {
            desc.appendText("value of any type ");
        }
        virtual void describe_mismatch(const ValueHolder&, Description&) const
        {
            // should never be called as should never fail
            throw std::runtime_error("describe_mismatch called for type anything (should never fail)");
        }
        virtual bool operator()(const ValueHolder&) const
        {
            return true;
        }
    };
}

#endif
