//          Copyright Malcolm Noyes 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef GOOS_PIMPL_EXACTLY_HPP
#define GOOS_PIMPL_EXACTLY_HPP

#include "expectation.hpp"
#include "expected_function_count_equals.hpp"
#include "matcher.hpp"
#include "with.hpp"
#include "function_call.hpp"

namespace goospimpl
{
    struct exactly
    {
        explicit exactly(size_t n)
            : count(n)
        {}
        template <typename Target, typename P1>
        exactly& of(const P1& v1)
        {
            std::vector<MatcherHolder> params;
            typedef Target arg1_nonref;
            addWithParam<arg1_nonref>(params, v1);
            return *this;
        }
        template <typename T, typename F>
        exactly& of(const T& obj, F fn)
        {
            std::vector<MatcherHolder> params;
            FunctionHolder t(new detail::FunctionBinder<T, F>(&obj, fn));
            ExpectationHolder tmp(new ExpectedFunctionCountEquals(t, params, count));
            expectation = tmp;
            return *this;
        }
        template <typename T, typename F, typename P1>
        exactly& of(const T& obj, F fn, const P1& v1)
        {
            std::vector<MatcherHolder> params;
            typedef typename member_function_traits<F>::arg1_type arg1_nonref;
            addWithParam<arg1_nonref>(params, v1);
            FunctionHolder t(new detail::FunctionBinder<T, F>(&obj, fn));
            ExpectationHolder tmp(new ExpectedFunctionCountEquals(t, params, count));
            expectation = tmp;
            return *this;
        }
        template <typename T, typename F, typename P1, typename P2>
        exactly& of(const T& obj, F fn, const P1& v1, const P2& v2)
        {
            std::vector<MatcherHolder> params;
            typedef typename member_function_traits<F>::arg1_type arg1_nonref;
            addWithParam<arg1_nonref>(params, v1);
            typedef typename member_function_traits<F>::arg2_type arg2_nonref;
            addWithParam<arg2_nonref>(params, v2);
            FunctionHolder t(new detail::FunctionBinder<T, F>(&obj, fn));
            ExpectationHolder tmp(new ExpectedFunctionCountEquals(t, params, count));
            expectation = tmp;
            return *this;
        }
        template<typename Convert, typename T>
        void addWithParam(std::vector<MatcherHolder>& params, const T& v)
        {
            addEqualsParam(params, static_cast<Convert>(v));
        }
        template<typename Convert, typename Matcher>
        void addWithParam(std::vector<MatcherHolder>& params, const with_matcher<Matcher>& v)
        {
            MatcherHolder vx(v.template clone_with_new_type<Convert>());
            params.push_back(vx);
        }
        template<typename T>
        void addEqualsParam(std::vector<MatcherHolder>& params, const T& v)
        {
            MatcherHolder vx( new EqualsMatcher<T>(v));
            params.push_back(vx);
        }

        size_t count;
        ExpectationHolder expectation;
    };
}

#endif
