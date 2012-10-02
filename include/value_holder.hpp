//          Copyright Malcolm Noyes 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef GOOS_PIMPL_VALUE_HOLDER_HPP
#define GOOS_PIMPL_VALUE_HOLDER_HPP

//#include <string>

namespace goospimpl
{
    struct CloneableType
    {
        virtual ~CloneableType() {}
        virtual const CloneableType* clone() const = 0;
        virtual const std::type_info & type() const = 0;
    };

    template <typename T>
    class TypeErasedValue : CloneableType
    {
        friend class ValueHolder;
    public:
        typedef T ValueType;
        TypeErasedValue(const T& v)
            : m_value(v)
        {}
        virtual const CloneableType* clone() const
        {
            return new TypeErasedValue<T>(*this);
        }
        virtual const std::type_info & type() const
        {
            return typeid(ValueType);
        }
    private:
        TypeErasedValue& operator=(TypeErasedValue); // not implemented
        const ValueType m_value;
    };

    template <typename T>
    class TypeErasedValue<T*> : CloneableType
    {
        friend class ValueHolder;
    public:
        typedef T ValueType;
        TypeErasedValue(const T* v)
            : m_value(v)
        {}
        virtual const CloneableType* clone() const
        {
            return new TypeErasedValue<T*>(*this);
        }
        virtual const std::type_info & type() const
        {
            return typeid(ValueType*);
        }
    private:
        TypeErasedValue& operator=(TypeErasedValue); // not implemented
        const ValueType* m_value;
    };

    class ValueHolder
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
            : m_content(NULL)
        {}
        ~ValueHolder()
        {
            delete m_content;
        }
        ValueHolder(const ValueHolder& rhs)
            : m_content(rhs.m_content ? rhs.m_content->clone() : NULL)
        {}
        template <typename T>
        ValueHolder(const T& v)
            : m_content(new TypeErasedValue<T>(v) )
        {}
        /*explicit ValueHolder(const char* v)
            : m_content(new TypeErasedValue<std::string>(v) )
        {}*/
        ValueHolder& operator=(ValueHolder rhs)
        {
            return rhs.swapContent(*this);
        }
        const std::type_info & type() const
        {
            return m_content ? m_content->type() : typeid(void);
        }

        template <typename T>
        const T& value() const
        {
            if( !m_content || (m_content->type() != typeid(T)) )
            {
                throw BadHolderCast();
            }
            return static_cast<const TypeErasedValue<T>*>(m_content)->m_value;
        }
    private:
        ValueHolder& swapContent(ValueHolder & rhs)
        {
            std::swap(m_content, rhs.m_content);
            return *this;
        }

        const CloneableType* m_content;
    };

    /*template <typename T>
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

    class ValueHolder : public CountedHolder<CountedType>
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
        template <typename T>
        ValueHolder(T* v)
            : CountedHolder(new ValueContent<T*>(v) )
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
    };*/
}

#endif
