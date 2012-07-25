//          Copyright Malcolm Noyes 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef GOOS_PIMPL_ALLOWING_HPP
#define GOOS_PIMPL_ALLOWING_HPP

#include "expectation.hpp"
#include "expected_function_count_at_least.hpp"
#include "matcher.hpp"
#include "with.hpp"
#include "function_call.hpp"

namespace goospimpl
{
    struct allowing
    {
        template <typename T, typename F>
        allowing(const T& obj, F fn)
        {
            std::vector<MatcherHolder> params;
            FunctionHolder t(new detail::FunctionBinder<T, F>(&obj, fn));
            ExpectationHolder tmp(new ExpectedFunctionCountAtLeast(t, params, 0));
            expectation = tmp;
        }
        template <typename T, typename F, typename P1>
        allowing(const T& obj, F fn, const P1& v1)
        {
            std::vector<MatcherHolder> params;
            typedef typename member_function_traits<F>::arg1_type arg1_nonref;
            addParam(params, static_cast<arg1_nonref>(v1));
            FunctionHolder t(new detail::FunctionBinder<T, F>(&obj, fn));
            ExpectationHolder tmp(new ExpectedFunctionCountAtLeast(t, params, 0));
            expectation = tmp;
        }
        template <typename T, typename F, typename P1, typename P2>
        allowing(const T& obj, F fn, const P1& v1, const P2& v2)
        {
            std::vector<MatcherHolder> params;
            typedef typename member_function_traits<F>::arg1_type arg1_nonref;
            addParam(params, static_cast<arg1_nonref>(v1));
            typedef typename member_function_traits<F>::arg2_type arg2_nonref;
            addParam(params, static_cast<arg2_nonref>(v2));
            FunctionHolder t(new detail::FunctionBinder<T, F>(&obj, fn));
            ExpectationHolder tmp(new ExpectedFunctionCountAtLeast(t, params, 0));
            expectation = tmp;
        }
        template<typename T>
        void addParam(std::vector<MatcherHolder>& params, const T& v)
        {
            MatcherHolder vx( new EqualsMatcher<T>(v));
            params.push_back(vx);
        }
        ExpectationHolder expectation;
    };
}

#endif
