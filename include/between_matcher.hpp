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
    template <typename T>
    struct BetweenMatcher : public CountedContent<MatcherContent>
    {
    public:
        typedef T ValueType;
        typedef std::pair<ValueType, ValueType> MatchParameterType;
        BetweenMatcher()
            : lower(), upper()
        {}
        BetweenMatcher(const ValueType & l, const ValueType& u)
            : lower(l), upper(u)
        {
        }
        explicit BetweenMatcher(const MatchParameterType& v)
            : lower(v.first), upper(v.second)
        {
        }
        virtual const std::type_info & type() const
        {
            return typeid(ValueType);
        }
        virtual void describe_to(goospimpl::Description& desc) const
        {
            desc.appendText("value between ").appendValue(lower).appendText(" and ").appendValue(upper);
        }
        virtual void describe_mismatch(const ValueHolder& v, goospimpl::Description& mismatch_desc) const
        {
            if( v.type() == typeid(ValueType) )
            {
                const ValueType& parameter = v.value<ValueType>();
                mismatch_desc.appendText("was ").appendValue(parameter);
            }
            else
            {
                mismatch_desc.appendText("was of incompatible type '").appendText(v.type().name()).appendText("'");
            }
        }
        virtual bool operator()(const ValueHolder& v) const
        {
            if( v.type() == typeid(ValueType) )
            {
                const ValueType& parameter = v.value<ValueType>();
                return (parameter >= lower && parameter <= upper);
            }
            return false;
        }

        template <typename U>
        MatcherContent* clone_with_new_type() const
        {
            return new BetweenMatcher<U>(std::pair<U, U>(static_cast<U>(lower), static_cast<U>(upper)) );
        }
    private:
        BetweenMatcher(const BetweenMatcher&);
        BetweenMatcher operator=(BetweenMatcher);

        ValueType lower;
        ValueType upper;
    };
}

#endif
