//          Copyright Malcolm Noyes 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef GOOS_PIMPL_EQUALS_MATCHER_HPP
#define GOOS_PIMPL_EQUALS_MATCHER_HPP

#include "description.hpp"
#include "matcher.hpp"

namespace goospimpl
{
    template <typename T>
    struct EqualsMatcher : public CountedContent<MatcherContent>
    {
    public:
        typedef T ValueType;
        typedef T MatchParameterType;
        EqualsMatcher()
            : expected()
        {}
        explicit EqualsMatcher(const MatchParameterType & value)
            : expected(value)
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
                return (expected == parameter);
            }
            return false;
        }

        template <typename U>
        MatcherContent* clone_with_new_type() const
        {
            return new EqualsMatcher<U>(static_cast<U>(expected));
        }
    private:
        EqualsMatcher(const EqualsMatcher&);
        EqualsMatcher operator=(EqualsMatcher);

        ValueType expected;
    };

    template <typename T>
    class EqualsMatcher2
    {
    public:
        typedef T ValueType;
        //typedef T MatchParameterType;
        EqualsMatcher2()
            : expected()
        {}
        explicit EqualsMatcher2(const ValueType & value)
            : expected(value)
        {
        }
        /*bool operator()(const ValueType& v) const
        {
            return matches(v);
        }*/
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
