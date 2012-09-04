//          Copyright Malcolm Noyes 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef GOOS_PIMPL_EQUALS_WITH_EPSILON_MATCHER_HPP
#define GOOS_PIMPL_EQUALS_WITH_EPSILON_MATCHER_HPP

#include "description.hpp"
#include "matcher.hpp"

namespace goospimpl
{
    template <typename T, typename EpsilonType>
    struct EqualsWithEpsilonMatcher : public CountedContent<MatcherContent>
    {
    public:
        typedef T ValueType;
        typedef std::pair<ValueType, EpsilonType> MatchParameterType;
        EqualsWithEpsilonMatcher()
            : expected(), epsilon(0)
        {}
        EqualsWithEpsilonMatcher(const ValueType & value, const EpsilonType& e)
            : expected(value), epsilon(e)
        {
        }
        explicit EqualsWithEpsilonMatcher(const MatchParameterType& v)
            : expected(v.first), epsilon(v.second)
        {
        }
        virtual const std::type_info & type() const
        {
            return typeid(ValueType);
        }
        virtual void describe_to(goospimpl::Description& desc) const
        {
            desc.appendText("value ").appendValue(expected);
        }
        virtual void describe_mismatch(const ValueHolder& v, goospimpl::Description& mismatch_desc) const
        {
            if( v.type() == typeid(ValueType) )
            {
                const ValueType& parameter = v.value<ValueType>();
                mismatch_desc.appendText("was ").appendValue(parameter).appendText(" (+-").appendValue(epsilon).appendText(")");
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
                return (expected <= (parameter + epsilon) && expected >= (parameter - epsilon));
            }
            return false;
        }

        template <typename U>
        MatcherContent* clone_with_new_type() const
        {
            return new EqualsWithEpsilonMatcher<U, EpsilonType>(std::pair<U, EpsilonType>(static_cast<U>(expected), epsilon) );
        }
    private:
        EqualsWithEpsilonMatcher(const EqualsWithEpsilonMatcher&);
        EqualsWithEpsilonMatcher operator=(EqualsWithEpsilonMatcher);

        ValueType expected;
        EpsilonType epsilon;
    };

    template <typename T, typename EpsilonType>
    class EqualsWithEpsilonMatcher2
    {
        typedef T ValueType;
    public:
        EqualsWithEpsilonMatcher2()
            : expected(), epsilon(0)
        {}
        explicit EqualsWithEpsilonMatcher2(const ValueType & value, const EpsilonType& e)
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
