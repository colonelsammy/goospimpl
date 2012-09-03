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
    template<typename Matcher>
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

    template<typename Matcher>
    WithMatcher<Matcher> with(const WithMatcher<Matcher>& value)
    {
        return value;
    }

    template <typename Matcher>
    struct WithParameterType
    {
        typedef typename Matcher::ValueType MatchParameterType;
        WithParameterType(const MatchParameterType& v)
            : m_value(v)
        {}
        template <typename U>
        MatcherHolder2 convert() const
        {
            return MatcherHolder2::create<Matcher, U>(static_cast<U>(m_value));
        }
        MatchParameterType m_value;
    };

    template<typename Matcher>
    struct WithMatcher2
    {
        typedef typename WithParameterType<Matcher>::MatchParameterType MatchParameterType;
        WithMatcher2(const MatchParameterType& v)
            : m_params(v)
        {}
        WithParameterType<Matcher> m_params;
        //MatchParameterType m_value;
        template <typename U>
        MatcherHolder2 matcher() const
        {
            //Matcher m(m_value);
            return m_params.convert<U>();
        }
    };

}

#endif
