//          Copyright Malcolm Noyes 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef GOOS_PIMPL_ANY_VALUE_OF_TYPE_MATCHER_HPP
#define GOOS_PIMPL_ANY_VALUE_OF_TYPE_MATCHER_HPP

#include "description.hpp"
#include "matcher.hpp"

namespace goospimpl
{
    template <typename T>
    struct AnyValueOfTypeMatcher : public CountedContent<MatcherContent>
    {
    public:
        typedef T ValueType;
        typedef ValueType MatchParameterType;
        AnyValueOfTypeMatcher()
        {}
        virtual const std::type_info & type() const
        {
            return typeid(ValueType);
        }
        virtual void describe_to(Description& desc) const
        {
            desc.appendText("value of type ").appendText(typeid(ValueType).name());
        }
        virtual void describe_mismatch(const ValueHolder& v, Description& mismatch_desc) const
        {
            mismatch_desc.appendText("was of type ").appendValue(v.type().name());
        }
        virtual bool operator()(const ValueHolder& v) const
        {
            return (type() == v.type());
        }
        template <typename U>
        MatcherContent* clone_with_new_type() const
        {
            return new AnyValueOfTypeMatcher<U>();
        }
    };
}

#endif
