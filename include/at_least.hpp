//          Copyright Malcolm Noyes 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef GOOS_PIMPL_ATLEAST_HPP
#define GOOS_PIMPL_ATLEAST_HPP

#include "expectation.hpp"
#include "expected_function_count_at_least.hpp"
#include "matcher.hpp"
#include "with.hpp"
#include "function_call.hpp"

namespace goospimpl
{
    struct atLeast
    {
        explicit atLeast(size_t n)
            : count(n)
        {}
        template <typename T, typename F>
        atLeast& of(const T& obj, F fn)
        {
            std::vector<MatcherHolder> params;
            FunctionHolder t(new detail::FunctionBinder<T, F>(&obj, fn));
            ExpectationHolder tmp(new ExpectedFunctionCountAtLeast(t, params, count));
            expectation = tmp;
            return *this;
        }
        template <typename T, typename F, typename P1>
        atLeast& of(const T& obj, F fn, const P1& v1)
        {
            std::vector<MatcherHolder> params;
            typedef typename member_function_traits<F>::arg1_type arg1_nonref;
            addWithParam(params, static_cast<arg1_nonref>(v1));
            FunctionHolder t(new detail::FunctionBinder<T, F>(&obj, fn));
            ExpectationHolder tmp(new ExpectedFunctionCountAtLeast(t, params, count));
            expectation = tmp;
            return *this;
        }
        template <typename T, typename F, typename P1, typename P2>
        atLeast& of(const T& obj, F fn, const P1& v1, const P2& v2)
        {
            std::vector<MatcherHolder> params;
            typedef typename member_function_traits<F>::arg1_type arg1_nonref;
            addWithParam(params, static_cast<arg1_nonref>(v1));
            typedef typename member_function_traits<F>::arg2_type arg2_nonref;
            addWithParam(params, static_cast<arg2_nonref>(v2));
            FunctionHolder t(new detail::FunctionBinder<T, F>(&obj, fn));
            ExpectationHolder tmp(new ExpectedFunctionCountAtLeast(t, params, count));
            expectation = tmp;
            return *this;
        }
        template <typename T, typename F, typename P1, typename P2, typename P3>
        atLeast& of(const T& obj, F fn, const P1& v1, const P2& v2, const P3& v3)
        {
            std::vector<MatcherHolder> params;
            typedef typename member_function_traits<F>::arg1_type arg1_nonref;
            addWithParam(params, static_cast<arg1_nonref>(v1));
            typedef typename member_function_traits<F>::arg2_type arg2_nonref;
            addWithParam(params, static_cast<arg2_nonref>(v2));
            typedef typename member_function_traits<F>::arg3_type arg3_nonref;
            addWithParam(params, static_cast<arg3_nonref>(v3));
            FunctionHolder t(new detail::FunctionBinder<T, F>(&obj, fn));
            ExpectationHolder tmp(new ExpectedFunctionCountAtLeast(t, params, count));
            expectation = tmp;
            return *this;
        }
        template <typename T, typename F, typename P1, typename P2, typename P3, typename P4>
        atLeast& of(const T& obj, F fn, const P1& v1, const P2& v2, const P3& v3, const P4& v4)
        {
            std::vector<MatcherHolder> params;
            typedef typename member_function_traits<F>::arg1_type arg1_nonref;
            addWithParam(params, static_cast<arg1_nonref>(v1));
            typedef typename member_function_traits<F>::arg2_type arg2_nonref;
            addWithParam(params, static_cast<arg2_nonref>(v2));
            typedef typename member_function_traits<F>::arg3_type arg3_nonref;
            addWithParam(params, static_cast<arg3_nonref>(v3));
            typedef typename member_function_traits<F>::arg4_type arg4_nonref;
            addWithParam(params, static_cast<arg4_nonref>(v4));
            FunctionHolder t(new detail::FunctionBinder<T, F>(&obj, fn));
            ExpectationHolder tmp(new ExpectedFunctionCountAtLeast(t, params, count));
            expectation = tmp;
            return *this;
        }
        template <typename T, typename F, typename P1, typename P2, typename P3, typename P4, typename P5>
        atLeast& of(const T& obj, F fn, const P1& v1, const P2& v2, const P3& v3, const P4& v4, const P5& v5)
        {
            std::vector<MatcherHolder> params;
            typedef typename member_function_traits<F>::arg1_type arg1_nonref;
            addWithParam(params, static_cast<arg1_nonref>(v1));
            typedef typename member_function_traits<F>::arg2_type arg2_nonref;
            addWithParam(params, static_cast<arg2_nonref>(v2));
            typedef typename member_function_traits<F>::arg3_type arg3_nonref;
            addWithParam(params, static_cast<arg3_nonref>(v3));
            typedef typename member_function_traits<F>::arg4_type arg4_nonref;
            addWithParam(params, static_cast<arg4_nonref>(v4));
            typedef typename member_function_traits<F>::arg5_type arg5_nonref;
            addWithParam(params, static_cast<arg5_nonref>(v5));
            FunctionHolder t(new detail::FunctionBinder<T, F>(&obj, fn));
            ExpectationHolder tmp(new ExpectedFunctionCountAtLeast(t, params, count));
            expectation = tmp;
            return *this;
        }
        template <typename T, typename F, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
        atLeast& of(const T& obj, F fn, const P1& v1, const P2& v2, const P3& v3, const P4& v4, const P5& v5, const P6& v6)
        {
            std::vector<MatcherHolder> params;
            typedef typename member_function_traits<F>::arg1_type arg1_nonref;
            addWithParam(params, static_cast<arg1_nonref>(v1));
            typedef typename member_function_traits<F>::arg2_type arg2_nonref;
            addWithParam(params, static_cast<arg2_nonref>(v2));
            typedef typename member_function_traits<F>::arg3_type arg3_nonref;
            addWithParam(params, static_cast<arg3_nonref>(v3));
            typedef typename member_function_traits<F>::arg4_type arg4_nonref;
            addWithParam(params, static_cast<arg4_nonref>(v4));
            typedef typename member_function_traits<F>::arg5_type arg5_nonref;
            addWithParam(params, static_cast<arg5_nonref>(v5));
            typedef typename member_function_traits<F>::arg6_type arg6_nonref;
            addWithParam(params, static_cast<arg6_nonref>(v6));
            FunctionHolder t(new detail::FunctionBinder<T, F>(&obj, fn));
            ExpectationHolder tmp(new ExpectedFunctionCountAtLeast(t, params, count));
            expectation = tmp;
            return *this;
        }
        template <typename T, typename F, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
        atLeast& of(const T& obj, F fn, const P1& v1, const P2& v2, const P3& v3, const P4& v4, const P5& v5, const P6& v6, const P7& v7)
        {
            std::vector<MatcherHolder> params;
            typedef typename member_function_traits<F>::arg1_type arg1_nonref;
            addWithParam(params, static_cast<arg1_nonref>(v1));
            typedef typename member_function_traits<F>::arg2_type arg2_nonref;
            addWithParam(params, static_cast<arg2_nonref>(v2));
            typedef typename member_function_traits<F>::arg3_type arg3_nonref;
            addWithParam(params, static_cast<arg3_nonref>(v3));
            typedef typename member_function_traits<F>::arg4_type arg4_nonref;
            addWithParam(params, static_cast<arg4_nonref>(v4));
            typedef typename member_function_traits<F>::arg5_type arg5_nonref;
            addWithParam(params, static_cast<arg5_nonref>(v5));
            typedef typename member_function_traits<F>::arg6_type arg6_nonref;
            addWithParam(params, static_cast<arg6_nonref>(v6));
            typedef typename member_function_traits<F>::arg7_type arg7_nonref;
            addWithParam(params, static_cast<arg7_nonref>(v7));
            FunctionHolder t(new detail::FunctionBinder<T, F>(&obj, fn));
            ExpectationHolder tmp(new ExpectedFunctionCountAtLeast(t, params, count));
            expectation = tmp;
            return *this;
        }
        template <typename T, typename F, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
        atLeast& of(const T& obj, F fn, const P1& v1, const P2& v2, const P3& v3, const P4& v4, const P5& v5, const P6& v6, const P7& v7, const P8& v8)
        {
            std::vector<MatcherHolder> params;
            typedef typename member_function_traits<F>::arg1_type arg1_nonref;
            addWithParam(params, static_cast<arg1_nonref>(v1));
            typedef typename member_function_traits<F>::arg2_type arg2_nonref;
            addWithParam(params, static_cast<arg2_nonref>(v2));
            typedef typename member_function_traits<F>::arg3_type arg3_nonref;
            addWithParam(params, static_cast<arg3_nonref>(v3));
            typedef typename member_function_traits<F>::arg4_type arg4_nonref;
            addWithParam(params, static_cast<arg4_nonref>(v4));
            typedef typename member_function_traits<F>::arg5_type arg5_nonref;
            addWithParam(params, static_cast<arg5_nonref>(v5));
            typedef typename member_function_traits<F>::arg6_type arg6_nonref;
            addWithParam(params, static_cast<arg6_nonref>(v6));
            typedef typename member_function_traits<F>::arg7_type arg7_nonref;
            addWithParam(params, static_cast<arg7_nonref>(v7));
            typedef typename member_function_traits<F>::arg8_type arg8_nonref;
            addWithParam(params, static_cast<arg8_nonref>(v8));
            FunctionHolder t(new detail::FunctionBinder<T, F>(&obj, fn));
            ExpectationHolder tmp(new ExpectedFunctionCountAtLeast(t, params, count));
            expectation = tmp;
            return *this;
        }
        template <typename T, typename F, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
        atLeast& of(const T& obj, F fn, const P1& v1, const P2& v2, const P3& v3, const P4& v4, const P5& v5, const P6& v6, const P7& v7, const P8& v8, const P9& v9)
        {
            std::vector<MatcherHolder> params;
            typedef typename member_function_traits<F>::arg1_type arg1_nonref;
            addWithParam(params, static_cast<arg1_nonref>(v1));
            typedef typename member_function_traits<F>::arg2_type arg2_nonref;
            addWithParam(params, static_cast<arg2_nonref>(v2));
            typedef typename member_function_traits<F>::arg3_type arg3_nonref;
            addWithParam(params, static_cast<arg3_nonref>(v3));
            typedef typename member_function_traits<F>::arg4_type arg4_nonref;
            addWithParam(params, static_cast<arg4_nonref>(v4));
            typedef typename member_function_traits<F>::arg5_type arg5_nonref;
            addWithParam(params, static_cast<arg5_nonref>(v5));
            typedef typename member_function_traits<F>::arg6_type arg6_nonref;
            addWithParam(params, static_cast<arg6_nonref>(v6));
            typedef typename member_function_traits<F>::arg7_type arg7_nonref;
            addWithParam(params, static_cast<arg7_nonref>(v7));
            typedef typename member_function_traits<F>::arg8_type arg8_nonref;
            addWithParam(params, static_cast<arg8_nonref>(v8));
            typedef typename member_function_traits<F>::arg9_type arg9_nonref;
            addWithParam(params, static_cast<arg9_nonref>(v9));
            FunctionHolder t(new detail::FunctionBinder<T, F>(&obj, fn));
            ExpectationHolder tmp(new ExpectedFunctionCountAtLeast(t, params, count));
            expectation = tmp;
            return *this;
        }
        template <typename T, typename F, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10>
        atLeast& of(const T& obj, F fn, const P1& v1, const P2& v2, const P3& v3, const P4& v4, const P5& v5, const P6& v6, const P7& v7, const P8& v8, const P9& v9, const P10& v10)
        {
            std::vector<MatcherHolder> params;
            typedef typename member_function_traits<F>::arg1_type arg1_nonref;
            addWithParam(params, static_cast<arg1_nonref>(v1));
            typedef typename member_function_traits<F>::arg2_type arg2_nonref;
            addWithParam(params, static_cast<arg2_nonref>(v2));
            typedef typename member_function_traits<F>::arg3_type arg3_nonref;
            addWithParam(params, static_cast<arg3_nonref>(v3));
            typedef typename member_function_traits<F>::arg4_type arg4_nonref;
            addWithParam(params, static_cast<arg4_nonref>(v4));
            typedef typename member_function_traits<F>::arg5_type arg5_nonref;
            addWithParam(params, static_cast<arg5_nonref>(v5));
            typedef typename member_function_traits<F>::arg6_type arg6_nonref;
            addWithParam(params, static_cast<arg6_nonref>(v6));
            typedef typename member_function_traits<F>::arg7_type arg7_nonref;
            addWithParam(params, static_cast<arg7_nonref>(v7));
            typedef typename member_function_traits<F>::arg8_type arg8_nonref;
            addWithParam(params, static_cast<arg8_nonref>(v8));
            typedef typename member_function_traits<F>::arg9_type arg9_nonref;
            addWithParam(params, static_cast<arg9_nonref>(v9));
            typedef typename member_function_traits<F>::arg10_type arg10_nonref;
            addWithParam(params, static_cast<arg10_nonref>(v10));
            FunctionHolder t(new detail::FunctionBinder<T, F>(&obj, fn));
            ExpectationHolder tmp(new ExpectedFunctionCountAtLeast(t, params, count));
            expectation = tmp;
            return *this;
        }
        template<typename T>
        void addWithParam(std::vector<MatcherHolder>& params, const T& v)
        {
            MatcherHolder vx( new EqualsMatcher<T>(v));
            params.push_back(vx);
        }
        template<typename Convert, typename Matcher>
        void addWithParam(std::vector<MatcherHolder>& params, const WithMatcher<Matcher>& v)
        {
            MatcherHolder vx(v.template clone_with_new_type<Convert>());
            params.push_back(vx);
        }

        size_t count;
        ExpectationHolder expectation;
    };
}

#endif
