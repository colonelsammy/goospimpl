//          Copyright Malcolm Noyes 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef GOOS_PIMPL_CATCH_MATCHER_WRAPPER_HPP
#define GOOS_PIMPL_CATCH_MATCHER_WRAPPER_HPP

#include "description.hpp"
#include "internal/catch_matchers.hpp"

namespace goospimpl
{
    template <typename T, typename Matcher>
    struct CatchMatcher
    {
    public:
        typedef T ValueType;
        CatchMatcher()
        {}
        explicit CatchMatcher(const ValueType & value)
            : m_matcher(value)
        {
        }
        void describe_to(goospimpl::Description& desc) const
        {
            desc.appendText(m_matcher.toString());
        }
        void describe_mismatch(const ValueType& v, goospimpl::Description& mismatch_desc) const
        {
            mismatch_desc.appendText("was ").appendValue(v);
        }
        bool matches(const ValueType& v) const
        {
            return m_matcher.match(v);
        }
    private:

        Matcher m_matcher;
    };
    
    template <typename T> struct ContainsMatcher;

    template <>
    class ContainsMatcher<std::string> : public CatchMatcher<std::string, Catch::Matchers::Impl::StdString::Contains>
    {
    public:
        explicit ContainsMatcher(const std::string& value)
            : CatchMatcher(value)
        {
        }
        bool matches(const ValueType& v) const
        {
            return CatchMatcher::matches(v);
        }
    };

    template <typename T> struct StartsWithMatcher;

    template <>
    class StartsWithMatcher<std::string> : public CatchMatcher<std::string, Catch::Matchers::Impl::StdString::StartsWith>
    {
    public:
        explicit StartsWithMatcher(const std::string& value)
            : CatchMatcher(value)
        {
        }
        bool matches(const ValueType& v) const
        {
            return CatchMatcher::matches(v);
        }
    };

    template <typename T> struct EndsWithMatcher;

    template <>
    class EndsWithMatcher<std::string> : public CatchMatcher<std::string, Catch::Matchers::Impl::StdString::EndsWith>
    {
    public:
        explicit EndsWithMatcher(const std::string& value)
            : CatchMatcher(value)
        {
        }
        bool matches(const ValueType& v) const
        {
            return CatchMatcher::matches(v);
        }
    };
}

#endif
