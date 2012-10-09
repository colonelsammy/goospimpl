//          Copyright Malcolm Noyes 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef GOOS_PIMPL_WITH_HPP
#define GOOS_PIMPL_WITH_HPP

#include "matcher.hpp"
#include "equals_matcher.hpp"
#include "equals_with_epsilon_matcher.hpp"
#include "between_matcher.hpp"
#include "any_value_of_type_matcher.hpp"
#include "any_value_of_any_type_matcher.hpp"

namespace goospimpl
{
    /*template<typename Matcher>
    struct WithMatcher
    {
        typedef typename Matcher::MatchParameterType MatchParameterType;
        WithMatcher(const MatchParameterType& v)
            : m_value(v)
        {}
        MatchParameterType m_value;
        template <typename U>
        MatcherContent* clone_with_new_type() const
        {
            Matcher m(m_value);
            return m.clone_with_new_type<U>();
        }
    };

    template<>
    struct WithMatcher<AnyValueOfAnyTypeMatcher>
    {
        template <typename U>
        MatcherContent* clone_with_new_type() const
        {
            return new AnyValueOfAnyTypeMatcher();
        }
    };

    template<typename T>
    struct WithMatcher<AnyValueOfTypeMatcher<T> >
    {
        typedef typename AnyValueOfTypeMatcher<T>::MatchParameterType MatchParameterType;
        template <typename U>
        MatcherContent* clone_with_new_type() const
        {
            return new AnyValueOfTypeMatcher<T>();
        }
    };

    template <typename T>
    WithMatcher<EqualsMatcher<T> > equal(const T& v)
    {
        typedef typename EqualsMatcher<T>::MatchParameterType MatchParameterType;
        MatchParameterType packed_value(v);
        return WithMatcher<EqualsMatcher<T> >(packed_value);
    }

    template <typename T, typename U>
    WithMatcher<EqualsWithEpsilonMatcher<T,U> > equal(const T& v, const U& epsilon)
    {
        typedef typename EqualsWithEpsilonMatcher<T,U>::MatchParameterType MatchParameterType;
        MatchParameterType packed_value(v, epsilon);
        return WithMatcher<EqualsWithEpsilonMatcher<T, U> >(packed_value);
    }

    template <typename T>
    WithMatcher<BetweenMatcher<T> > between(const T& l, const T& u)
    {
        typedef typename BetweenMatcher<T>::MatchParameterType MatchParameterType;
        MatchParameterType packed_value(l, u);
        return WithMatcher<BetweenMatcher<T> >(packed_value);
    }

    template <typename T>
    WithMatcher<AnyValueOfTypeMatcher<T> > any()
    {
        return WithMatcher<AnyValueOfTypeMatcher<T> >();
    }

    inline WithMatcher<AnyValueOfAnyTypeMatcher> anything()
    {
        return WithMatcher<AnyValueOfAnyTypeMatcher>();
    }

    template <template <typename> class Matcher, typename T>
    struct WithParameterType
    {
        typedef typename Matcher<T>::ValueType MatchParameterType;
        WithParameterType(const MatchParameterType& v)
            : m_value(v)
        {}
        template <typename U>
        MatcherHolder2 convert() const
        {
            //return MatcherHolder2::convertParam<Matcher, U>(static_cast<U>(m_value));
            return MatcherHolder2();
        }
        MatchParameterType m_value;
    };

    template<template <typename> class Matcher>
    struct WithMatcher2
    {
        //typedef typename WithParameterType<Matcher>::MatchParameterType MatchParameterType;
        template <typename T>
        WithMatcher2(const Matcher<T>& v)
            //: m_params(v)
        {}
        //WithParameterType<Matcher> m_params;
        //MatchParameterType m_value;
        template <typename U>
        MatcherHolder2 matcher() const
        {
            //Matcher m(m_value);
            //return m_params.convert<U>();
            return MatcherHolder2();
        }
    };

    template<template <typename> class Matcher>
    WithMatcher2<Matcher> with2(const WithMatcher2<Matcher>& value)
    {
        return value;
    }*/

    template <template <typename> class Matcher, typename T>
    struct SingleValueDeducedMatcher
    {
        SingleValueDeducedMatcher(const T& v)
            : m_value(v)
        {}
        SingleValueDeducedMatcher()
            : m_value()
        {}
        const T m_value;
    };

    template <template <typename, typename> class Matcher, typename T1, typename T2>
    struct MultipleValueDeducedMatcher
    {
        MultipleValueDeducedMatcher(const T1& v1, const T2& v2)
            : m_v1(v1), m_v2(v2)
        {}
        const T1 m_v1;
        const T2 m_v2;
    };

    template <typename U, typename EpsilonType>
    MultipleValueDeducedMatcher<goospimpl::EqualsWithEpsilonMatcher,U,EpsilonType> equal(const U& v, const EpsilonType& e)
    {
        return MultipleValueDeducedMatcher<EqualsWithEpsilonMatcher, U,EpsilonType>(v, e);
    }

    template <typename U>
    SingleValueDeducedMatcher<EqualsMatcher,U> equal(const U& v)
    {
        return SingleValueDeducedMatcher<EqualsMatcher, U>(v);
    }

    template <typename U>
    SingleValueDeducedMatcher<goospimpl::EqualsMatcher,U*> equal(U* v)
    {
        return SingleValueDeducedMatcher<EqualsMatcher, U*>(v);
    }

    template <typename T1, typename T2>
    MultipleValueDeducedMatcher<goospimpl::BetweenMatcher,T1,T2> between(const T1& lower, const T2& upper)
    {
        return MultipleValueDeducedMatcher<BetweenMatcher,T1,T2>(lower, upper);
    }

    template <typename T1, typename T2>
    MultipleValueDeducedMatcher<BetweenMatcher,T1*,T2*> between(T1* lower, T2* upper)
    {
        return MultipleValueDeducedMatcher<goospimpl::BetweenMatcher,T1*,T2*>(lower, upper);
    }

    template <typename DeducedMatcher>
    DeducedMatcher with(const DeducedMatcher& m)
    {
        return m;
    }

}

#endif
