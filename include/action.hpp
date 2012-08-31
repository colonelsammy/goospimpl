//          Copyright Malcolm Noyes 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef GOOS_PIMPL_ACTION_HPP
#define GOOS_PIMPL_ACTION_HPP

#include "value_holder.hpp"
#include <cassert>

namespace goospimpl
{
    struct Action
    {
        virtual ~Action() {}
        virtual Action* clone() const = 0;
        virtual ValueHolder invoke() const = 0;
    };

    struct ReturnValueAction : public Action
    {
        ReturnValueAction(const ValueHolder& a)
            : value(a)
        {}
        virtual Action* clone() const
        {
            return new ReturnValueAction(value);
        }
        virtual ValueHolder invoke() const
        {
            return value;
        }
        ValueHolder value;
    };

    struct ThrowExceptionAction : public Action
    {
        struct InvokeException
        {
            virtual ~InvokeException() {}
            virtual InvokeException* clone() const = 0;
            virtual ValueHolder invoke() const = 0;
        };
        template<typename T>
        struct InvokeTypedException : public InvokeException
        {
            InvokeTypedException(const T& e)
                : exc(e)
            {}
            virtual InvokeException* clone() const
            {
                return new InvokeTypedException(exc);
            }
            virtual ValueHolder invoke() const
            {
                throw exc;
            }
            T exc;
        };
        ThrowExceptionAction()
            : content(NULL)
        {}
        ThrowExceptionAction(const ThrowExceptionAction& rhs)
            : content(rhs.content ? rhs.content->clone() : NULL )
        {}
        template <typename T>
        explicit ThrowExceptionAction(const T& e)
            : content(new InvokeTypedException<T>(e))
        {}
        virtual Action* clone() const
        {
            return new ThrowExceptionAction(*this);
        }
        virtual ValueHolder invoke() const
        {
            assert(content);
            return content->invoke();
        }
        InvokeException* content;
    };
}

#endif
