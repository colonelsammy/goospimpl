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
    };
}

#endif
