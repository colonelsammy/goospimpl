//          Copyright Malcolm Noyes 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef GOOS_PIMPL_ALLOWING_HPP
#define GOOS_PIMPL_ALLOWING_HPP

#include "at_least.hpp"

namespace goospimpl
{
    struct allowing : atLeast
    {
        template <typename T, typename F>
        allowing(const T& obj, F fn)
            : atLeast(0)
        {
            of(obj, fn);
        }
        template <typename T, typename F, typename P1>
        allowing(const T& obj, F fn, const P1& v1)
            : atLeast(0)
        {
            of(obj, fn, v1);
        }
        template <typename T, typename F, typename P1, typename P2>
        allowing(const T& obj, F fn, const P1& v1, const P2& v2)
            : atLeast(0)
        {
            of(obj, fn, v1, v2);
        }
        template <typename T, typename F, typename P1, typename P2, typename P3>
        allowing(const T& obj, F fn, const P1& v1, const P2& v2, const P3& v3)
            : atLeast(0)
        {
            of(obj, fn, v1, v2, v3);
        }
        template <typename T, typename F, typename P1, typename P2, typename P3, typename P4>
        allowing(const T& obj, F fn, const P1& v1, const P2& v2, const P3& v3, const P4& v4)
            : atLeast(0)
        {
            of(obj, fn, v1, v2, v3, v4);
        }
        template <typename T, typename F, typename P1, typename P2, typename P3, typename P4, typename P5>
        allowing(const T& obj, F fn, const P1& v1, const P2& v2, const P3& v3, const P4& v4, const P5& v5)
            : atLeast(0)
        {
            of(obj, fn, v1, v2, v3, v4, v5);
        }
        template <typename T, typename F, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
        allowing(const T& obj, F fn, const P1& v1, const P2& v2, const P3& v3, const P4& v4, const P5& v5, const P6& v6)
            : atLeast(0)
        {
            of(obj, fn, v1, v2, v3, v4, v5, v6);
        }
        template <typename T, typename F, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
        allowing(const T& obj, F fn, const P1& v1, const P2& v2, const P3& v3, const P4& v4, const P5& v5, const P6& v6, const P7& v7)
            : atLeast(0)
        {
            of(obj, fn, v1, v2, v3, v4, v5, v6, v7);
        }
        template <typename T, typename F, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
        allowing(const T& obj, F fn, const P1& v1, const P2& v2, const P3& v3, const P4& v4, const P5& v5, const P6& v6, const P7& v7, const P8& v8)
            : atLeast(0)
        {
            of(obj, fn, v1, v2, v3, v4, v5, v6, v7, v8);
        }
        template <typename T, typename F, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
        allowing(const T& obj, F fn, const P1& v1, const P2& v2, const P3& v3, const P4& v4, const P5& v5, const P6& v6, const P7& v7, const P8& v8, const P9& v9)
            : atLeast(0)
        {
            of(obj, fn, v1, v2, v3, v4, v5, v6, v7, v8, v9);
        }
        template <typename T, typename F, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10>
        allowing(const T& obj, F fn, const P1& v1, const P2& v2, const P3& v3, const P4& v4, const P5& v5, const P6& v6, const P7& v7, const P8& v8, const P9& v9, const P10& v10)
            : atLeast(0)
        {
            of(obj, fn, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10);
        }
    };
}

#endif
