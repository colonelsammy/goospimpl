//          Copyright Malcolm Noyes 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef GOOS_PIMPL_VALUE_HOLDER_HPP
#define GOOS_PIMPL_VALUE_HOLDER_HPP

#include "counted_instance.hpp"
#include <string>

namespace goospimpl
{
    template <typename T>
    class ValueContent : CountedContent<CountedType>
    {
        friend class ValueHolder;
    public:
        typedef T ValueType;
        ValueContent(const T& v)
            : m_value(v)
        {}
        virtual const std::type_info & type() const
        {
            return typeid(ValueType);
        }
    private:
        ValueContent& operator=(ValueContent); // not implemented

        ValueType m_value;
    };

    /*template <>
    class ValueContent<const char*> : CountedContent<CountedType>
    {
        friend class ValueHolder;
    public:
        typedef std::string ValueType;
        ValueContent(const char*& v)
            : m_value(v)
        {}
        virtual const std::type_info & type() const
        {
            return typeid(std::string);
        }
    private:
        ValueContent& operator=(ValueContent); // not implemented

        std::string m_value;
    };*/

    class ValueHolder : public CountedHolder<ValueHolder, CountedType>
    {
        class BadHolderCast : public std::bad_cast
        {
        public:
            virtual const char * what() const throw()
            {
                return "Attempt get a value of different type from ValueHolder";
            }
        };
    public:
        ValueHolder()
        {}
        template <typename T>
        ValueHolder(const T& v)
            : CountedHolder(new ValueContent<T>(v) )
        {}
        explicit ValueHolder(const char* v)
            : CountedHolder(new ValueContent<std::string>(v) )
        {}
        ValueHolder& operator=(ValueHolder rhs)
        {
            rhs.swapCountedHolder(*this);
            return *this;
        }

        template <typename T>
        const T& value() const
        {
            if( !content || (content->type() != typeid(T)) )
            {
                throw BadHolderCast();
            }
            return static_cast<ValueContent<T>*>(content)->m_value;
        }
    };
}

#endif
