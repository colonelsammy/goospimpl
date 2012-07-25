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
    struct with_matcher
    {
        typedef typename Matcher::MatchParameterType MatchParameterType;
        /*with_matcher()
            : m()
        {}*/
        with_matcher(const MatchParameterType& v)
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
    struct with_matcher<AnyValueOfAnyTypeMatcher>
    {
        //typedef AnyValueOfAnyTypeMatcher::MatchParameterType MatchParameterType;
        template <typename U>
        MatcherContent* clone_with_new_type() const
        {
            return new AnyValueOfAnyTypeMatcher();
        }
    };

    template<typename T>
    struct with_matcher<AnyValueOfTypeMatcher<T> >
    {
        typedef typename AnyValueOfTypeMatcher<T>::MatchParameterType MatchParameterType;
        template <typename U>
        MatcherContent* clone_with_new_type() const
        {
            return new AnyValueOfTypeMatcher<T>();
        }
    };

    template <typename T>
    with_matcher<EqualsMatcher<T> > equal(const T& v)
    {
        typedef typename EqualsMatcher<T>::MatchParameterType MatchParameterType;
        MatchParameterType packed_value(v);
        return with_matcher<EqualsMatcher<T> >(packed_value);
    }

    template <typename T, typename U>
    with_matcher<EqualsWithEpsilonMatcher<T,U> > equal(const T& v, const U& epsilon)
    {
        typedef typename EqualsWithEpsilonMatcher<T,U>::MatchParameterType MatchParameterType;
        MatchParameterType packed_value(v, epsilon);
        return with_matcher<EqualsWithEpsilonMatcher<T, U> >(packed_value);
    }

    template <typename T>
    with_matcher<BetweenMatcher<T> > between(const T& l, const T& u)
    {
        typedef typename BetweenMatcher<T>::MatchParameterType MatchParameterType;
        MatchParameterType packed_value(l, u);
        return with_matcher<BetweenMatcher<T> >(packed_value);
    }

    template <typename T>
    with_matcher<AnyValueOfTypeMatcher<T> > any()
    {
        return with_matcher<AnyValueOfTypeMatcher<T> >();
    }

    inline with_matcher<AnyValueOfAnyTypeMatcher> anything()
    {
        return with_matcher<AnyValueOfAnyTypeMatcher>();
    }

    template<typename Matcher>
    with_matcher<Matcher> with(const with_matcher<Matcher>& value)
    {
        return value;
    }
}

#endif
