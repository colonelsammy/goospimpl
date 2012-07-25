//          Copyright Malcolm Noyes 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef GOOS_PIMPL_ACTION_HPP
#define GOOS_PIMPL_ACTION_HPP

#include "value_holder.hpp"
#include <cassert>

//#include <boost/any.hpp>

namespace goospimpl
{
    struct action
    {
        virtual ~action() {}
        virtual action* clone() const = 0;
        virtual ValueHolder invoke() const = 0;
    };

    struct ReturnValueAction : public action
    {
        ReturnValueAction(const ValueHolder& a)
            : value(a)
        {}
        virtual action* clone() const
        {
            return new ReturnValueAction(value);
        }
        virtual ValueHolder invoke() const
        {
            return value;
        }
        ValueHolder value;
    };

    struct throw_exception_action : public action
    {
        struct invoke_exception
        {
            virtual ~invoke_exception() {}
            virtual invoke_exception* clone() const = 0;
            virtual ValueHolder invoke() const = 0;
        };
        template<typename T>
        struct invoke_typed_exception : public invoke_exception
        {
            invoke_typed_exception(const T& e)
                : exc(e)
            {}
            virtual invoke_exception* clone() const
            {
                return new invoke_typed_exception(exc);
            }
            virtual ValueHolder invoke() const
            {
                throw exc;
            }
            T exc;
        };
        throw_exception_action()
            : content(NULL)
        {}
        throw_exception_action(const throw_exception_action& rhs)
            : content(rhs.content ? rhs.content->clone() : NULL )
        {}
        template <typename T>
        explicit throw_exception_action(const T& e)
            : content(new invoke_typed_exception<T>(e))
        {}
        virtual action* clone() const
        {
            return new throw_exception_action(*this);
        }
        virtual ValueHolder invoke() const
        {
            assert(content);
            return content->invoke();
        }
        invoke_exception* content;
    };
}

#endif
