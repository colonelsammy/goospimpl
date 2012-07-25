//          Copyright Malcolm Noyes 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef GOOS_PIMPL_CATCH_MATCHER_WRAPPER_HPP
#define GOOS_PIMPL_CATCH_MATCHER_WRAPPER_HPP

#include "description.hpp"
#include "matcher.hpp"

namespace goospimpl
{
    template <typename T>
    struct CatchMatcher : public CountedContent<MatcherContent>
    {
    public:
        typedef std::string ValueType;
        typedef std::string MatchParameterType;
        CatchMatcher()
        {}
        explicit CatchMatcher(const MatchParameterType & value)
            : expected(value)
        {
        }
        virtual const std::type_info & type() const
        {
            return typeid(ValueType);
        }
        virtual void describe_to(goospimpl::Description& desc) const
        {
            std::ostringstream oss;
            oss << expected;
            desc.appendText(oss.str());
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
                return expected(parameter);
            }
            return false;
        }

        template <typename U>
        MatcherContent* clone_with_new_type() const
        {
            return new CatchMatcher<U>(static_cast<U>(expected.m_substr));
        }
    private:
        CatchMatcher(const CatchMatcher&);
        CatchMatcher operator=(CatchMatcher);

        T expected;
    };
    typedef CatchMatcher<Catch::Matchers::Impl::StdString::StartsWith> StartsWithMatcher;
}

#endif
