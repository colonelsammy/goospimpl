//          Copyright Malcolm Noyes 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef GOOS_PIMPL_ONE_OF_HPP
#define GOOS_PIMPL_ONE_OF_HPP

#include "exactly.hpp"

namespace goospimpl
{
    struct oneOf : public exactly
    {
        template <typename T, typename F>
        oneOf(const T& obj, F fn)
            : exactly(1)
        {
            of(obj, fn);
        }
        template <typename T, typename F, typename P1>
        oneOf(const T& obj, F fn, const P1& v1)
            : exactly(1)
        {
            of(obj, fn, v1);
        }
        template <typename T, typename F, typename P1, typename P2>
        oneOf(const T& obj, F fn, const P1& v1, const P2& v2)
            : exactly(1)
        {
            of(obj, fn, v1, v2);
        }
        template <typename T, typename F, typename P1, typename P2, typename P3>
        oneOf(const T& obj, F fn, const P1& v1, const P2& v2, const P3& v3)
            : exactly(1)
        {
            of(obj, fn, v1, v2, v3);
        }
        template <typename T, typename F, typename P1, typename P2, typename P3, typename P4>
        oneOf(const T& obj, F fn, const P1& v1, const P2& v2, const P3& v3, const P4& v4)
            : exactly(1)
        {
            of(obj, fn, v1, v2, v3, v4);
        }
        template <typename T, typename F, typename P1, typename P2, typename P3, typename P4, typename P5>
        oneOf(const T& obj, F fn, const P1& v1, const P2& v2, const P3& v3, const P4& v4, const P5& v5)
            : exactly(1)
        {
            of(obj, fn, v1, v2, v3, v4, v5);
        }
        template <typename T, typename F, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
        oneOf(const T& obj, F fn, const P1& v1, const P2& v2, const P3& v3, const P4& v4, const P5& v5, const P6& v6)
            : exactly(1)
        {
            of(obj, fn, v1, v2, v3, v4, v5, v6);
        }
        template <typename T, typename F, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
        oneOf(const T& obj, F fn, const P1& v1, const P2& v2, const P3& v3, const P4& v4, const P5& v5, const P6& v6, const P7& v7)
            : exactly(1)
        {
            of(obj, fn, v1, v2, v3, v4, v5, v6, v7);
        }
        template <typename T, typename F, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
        oneOf(const T& obj, F fn, const P1& v1, const P2& v2, const P3& v3, const P4& v4, const P5& v5, const P6& v6, const P7& v7, const P8& v8)
            : exactly(1)
        {
            of(obj, fn, v1, v2, v3, v4, v5, v6, v7, v8);
        }
        template <typename T, typename F, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
        oneOf(const T& obj, F fn, const P1& v1, const P2& v2, const P3& v3, const P4& v4, const P5& v5, const P6& v6, const P7& v7, const P8& v8, const P9& v9)
            : exactly(1)
        {
            of(obj, fn, v1, v2, v3, v4, v5, v6, v7, v8, v9);
        }
        template <typename T, typename F, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10>
        oneOf(const T& obj, F fn, const P1& v1, const P2& v2, const P3& v3, const P4& v4, const P5& v5, const P6& v6, const P7& v7, const P8& v8, const P9& v9, const P10& v10)
            : exactly(1)
        {
            of(obj, fn, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
        }
    };
}

#endif
