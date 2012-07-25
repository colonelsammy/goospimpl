//          Copyright Malcolm Noyes 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef GOOS_PIMPL_WILL_HPP
#define GOOS_PIMPL_WILL_HPP

#include "action.hpp"

namespace goospimpl
{
    struct return_value
    {
        template <typename T>
        explicit return_value(const T& t)
            : value(t)
        {}
        ValueHolder value;
    };

    struct throw_exception
    {
        template <typename T>
        explicit throw_exception(const T& e)
            : act(new throw_exception_action(e))
        {}
        action* act;
    };

    class will
    {
    public:
        explicit will(const return_value& v)
            : act(new ReturnValueAction(v.value))
        {}
        explicit will(const throw_exception& v)
            : act(v.act)
        {}
        action* act;
    private:
        will();
    };
}

#endif
