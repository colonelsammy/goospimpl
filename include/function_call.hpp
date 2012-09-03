//          Copyright Malcolm Noyes 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef GOOS_PIMPL_FUNCTION_CALL_HPP
#define GOOS_PIMPL_FUNCTION_CALL_HPP

#include "member_function_traits.hpp"
#include "value_holder.hpp"

#include <cassert>

namespace goospimpl
{
    namespace detail
    {
        struct FunctionContent : CountedType
        {
            virtual bool compare(const FunctionContent* v) const = 0;
            virtual ValueHolder defaultReturnValue() const = 0;
        };

        template <typename T>
        struct DefaultReturnValueHelper
        {
            ValueHolder value() const {return ValueHolder(T());}
        };

        template <>
        struct DefaultReturnValueHelper<void>
        {
            ValueHolder value() const {return ValueHolder();}
        };

        template <typename Mock, typename T>
        class FunctionBinder : public CountedContent<FunctionContent>
        {
        public:
            typedef T ValueType;
            FunctionBinder(const Mock* obj, const ValueType & value)
                : mock(obj), held(value)
            {
            }

            virtual const std::type_info & type() const
            {
                return typeid(ValueType);
            }
            virtual bool compare(const FunctionContent* v) const
            {
                if( type() != v->type() )
                    return false;
                const Mock* rhs_mock =  static_cast<const FunctionBinder<Mock, ValueType>*>(v)->mock;
                if( mock != rhs_mock )
                    return false;
                const ValueType& rhs_held =  static_cast<const FunctionBinder<Mock, ValueType>*>(v)->held;
                return held == rhs_held;
            }
            virtual ValueHolder defaultReturnValue() const
            {
                typedef typename member_function_traits<ValueType>::result_type result_type;
                DefaultReturnValueHelper<result_type> rv;
                return rv.value();
            }

        private:
            const Mock* mock;
            ValueType held;
        };
    } // detail

    class FunctionHolder : public CountedHolder<detail::FunctionContent>
    {
    public:
        explicit FunctionHolder(detail::FunctionContent* p)
            : CountedHolder(p)
        {}
    public:

        FunctionHolder & swap(FunctionHolder & rhs)
        {
            rhs.swapCountedHolder(*this);
            return *this;
        }

        template<typename ValueType>
        FunctionHolder & operator=(const ValueType & rhs)
        {
            FunctionHolder(rhs).swap(*this);
            return *this;
        }

        FunctionHolder & operator=(FunctionHolder rhs)
        {
            rhs.swap(*this);
            return *this;
        }

        bool compare(const FunctionHolder& v) const
        {
            if(!content || !v.content)
                return false;
            return content->compare(v.content);
        }
        ValueHolder defaultReturnValue() const
        {
            assert(content);
            return content->defaultReturnValue();
        }
    };
}

#endif
