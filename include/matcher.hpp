//          Copyright Malcolm Noyes 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef GOOS_PIMPL_MATCHER_HPP
#define GOOS_PIMPL_MATCHER_HPP

#include "value_holder.hpp"
#include "description.hpp"
#include <cassert>
#include <algorithm>

namespace goospimpl
{
    class Description;

    /*struct MatcherContent : CountedType
    {
        virtual void describe_to(Description& desc) const = 0;
        virtual void describe_mismatch(const ValueHolder& v, Description& mismatch_desc) const = 0;
        virtual bool operator()(const ValueHolder& v) const = 0;
    };

    class MatcherHolder : public CountedHolder<MatcherContent>
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
    };*/

    struct CloneableMatcher
    {
        //virtual const std::type_info & type() const = 0;
        virtual CloneableMatcher* clone() const = 0;
        virtual void describe_to(goospimpl::Description& desc) const = 0;
        virtual void describe_mismatch(const ValueHolder& v, goospimpl::Description& mismatch_desc) const = 0;
        virtual bool matches(const ValueHolder& v) const = 0;
    };

    template <typename T, typename ValueType>
    struct has_matcher_function
    {
        typedef char yes[1];
        typedef char no[2];
 
        template <typename C, bool (C::*)(const ValueType& v) const> struct ptmf_helper {};
        
        template <typename C>
        static yes& test(ptmf_helper<C, &C::matches>* p);
        template <typename>
        static no& test(...);
 
        static const bool value = sizeof(test<T>(0)) == sizeof(yes);
    };

    template <bool value>
    struct match_forwarder
    {
        template <typename Matcher, typename T>
        bool matches(const Matcher& m, const T& v) const
        {
            return m.operator()(v);
        }
    };

    template <>
    struct match_forwarder<true>
    {
        template <typename Matcher, typename T>
        bool matches(const Matcher& m, const T& v) const
        {
            return m.matches(v);
        }
    };

    template <typename T1, template <typename> class Matcher>
    class SingleValueMatcherType : CloneableMatcher
    {
        typedef T1 ValueType;
    public:
        /*static CloneableMatcher* create()
        {
            return new SingleValueMatcherType();
        }*/
        static CloneableMatcher* create(const ValueType& value)
        {
            return new SingleValueMatcherType(value);
        }
    private:
        SingleValueMatcherType()
            : m_matcher()
        {}
        SingleValueMatcherType(const SingleValueMatcherType& rhs)
            : m_matcher(rhs.m_matcher)
        {
        }
        explicit SingleValueMatcherType(const ValueType & value)
            : m_matcher(value)
        {
        }
        /*virtual const std::type_info & type() const
        {
            return typeid(ValueType);
        }*/
        virtual CloneableMatcher* clone() const
        {
            return new SingleValueMatcherType(*this);
        }
        virtual void describe_to(goospimpl::Description& desc) const
        {
            m_matcher.describe_to(desc);
        }
        virtual void describe_mismatch(const ValueHolder& v, goospimpl::Description& mismatch_desc) const
        {
            if( v.type() == typeid(ValueType) )
            {
                m_matcher.describe_mismatch(v.value<ValueType>(), mismatch_desc);
            }
            else
            {
                mismatch_desc.appendText("was of incompatible type '").appendText(v.type().name()).appendText("'");
            }
        }
        virtual bool matches(const ValueHolder& v) const
        {
            if( v.type() == typeid(ValueType) )
            {
                const ValueType& parameter = v.value<ValueType>();
                match_forwarder<has_matcher_function<Matcher<ValueType>, ValueType>::value> mf;
                return mf.matches(m_matcher, parameter);
            }
            return false;
        }
    private:
        const Matcher<ValueType> m_matcher;
    };

    template <typename T, typename U, template <typename, typename> class Matcher>
    class MultipleValueMatcherType : CloneableMatcher
    {
        typedef T ValueType;
    public:
        /*static CloneableMatcher* create()
        {
            return new MultipleValueMatcherType();
        }*/
        static CloneableMatcher* create(const ValueType& v1, const U& v2)
        {
            return new MultipleValueMatcherType(v1, v2);
        }
    private:
        MultipleValueMatcherType()
            : m_matcher()
        {}
        MultipleValueMatcherType(const MultipleValueMatcherType& rhs)
            : m_matcher(rhs.m_matcher)
        {
        }
        explicit MultipleValueMatcherType(const ValueType & v1, const U& v2)
            : m_matcher(v1, v2)
        {
        }
        /*virtual const std::type_info & type() const
        {
            return typeid(ValueType);
        }*/
        virtual CloneableMatcher* clone() const
        {
            return new MultipleValueMatcherType(*this);
        }
        virtual void describe_to(goospimpl::Description& desc) const
        {
            m_matcher.describe_to(desc);
        }
        virtual void describe_mismatch(const ValueHolder& v, goospimpl::Description& mismatch_desc) const
        {
            if( v.type() == typeid(ValueType) )
            {
                m_matcher.describe_mismatch(v.value<ValueType>(), mismatch_desc);
            }
            else
            {
                mismatch_desc.appendText("was of incompatible type '").appendText(v.type().name()).appendText("'");
            }
        }
        virtual bool matches(const ValueHolder& v) const
        {
            if( v.type() == typeid(ValueType) )
            {
                const ValueType& parameter = v.value<ValueType>();
                match_forwarder<has_matcher_function<Matcher<ValueType,U>, ValueType>::value> mf;
                return mf.matches(m_matcher, parameter);
            }
            return false;
        }
    private:
        const Matcher<ValueType, U> m_matcher;
    };

    class MatcherHolder2
    {
    public:
        ~MatcherHolder2()
        {
            delete content;
        }
        /*template <template <typename> class Matcher, typename T>
        static MatcherHolder2 create()
        {
            return MatcherHolder2(SingleValueMatcherType<T, Matcher>::create());
        }*/
        template <template <typename> class Matcher, typename T>
        static MatcherHolder2 create(T value)
        {
            return MatcherHolder2(SingleValueMatcherType<T, Matcher>::create(value));
        }
        template <template <typename, typename> class Matcher, typename T1, typename T2>
        static MatcherHolder2 create(T1 v1, T2 v2)
        {
            return MatcherHolder2(MultipleValueMatcherType<T1, T2, Matcher>::create(v1, v2));
        }
        MatcherHolder2(const MatcherHolder2& rhs)
            : content(rhs.content ? rhs.content->clone() : NULL)
        {}
        MatcherHolder2& operator=(MatcherHolder2 rhs)
        {
            rhs.swapContent(*this);
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
        bool matches(const ValueHolder& v) const
        {
            assert(content);
            return content->matches(v);
        }
    private:
        explicit MatcherHolder2(CloneableMatcher* p)
            : content(p)
        {
        }
        MatcherHolder2()
            : content(NULL)
        {}
        void swapContent(MatcherHolder2& rhs)
        {
            std::swap(content, rhs.content);
        }

        const CloneableMatcher* content;
    };
}

#endif
