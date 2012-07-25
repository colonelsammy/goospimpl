//          Copyright Malcolm Noyes 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef GOOS_PIMPL_COUNTED_INSTANCE_HPP
#define GOOS_PIMPL_COUNTED_INSTANCE_HPP

namespace boost
{
    class any;
}

#include <typeinfo>
#include <algorithm>

namespace goospimpl
{
    struct CountedInstance
    {
        virtual ~CountedInstance() = 0;
        virtual unsigned addRef() = 0;
        virtual unsigned release() = 0;
        virtual unsigned refCount() const = 0;
    };

    struct CountedType : CountedInstance
    {
        virtual const std::type_info & type() const = 0;
    };

    inline CountedInstance::~CountedInstance()
    {
    }

    template <typename Base>
    class CountedContent : public Base
    {
    public:
        CountedContent()
            : m_refs(1)
        {}
        virtual unsigned addRef()
        {
            return ++m_refs;
        }
        virtual unsigned release()
        {
            unsigned result = --m_refs;
            if( result == 0 )
            {
                delete this;
            }
            return result;
        }
        virtual unsigned refCount() const
        {
            return m_refs;
        }
    private:
        CountedContent(const CountedContent&);
        CountedContent& operator=(CountedContent);

        unsigned m_refs;
    };

    template <typename Derived, typename ContentHolder>
    class CountedHolder
    {
    public:
        const std::type_info & type() const
        {
            return content ? content->type() : typeid(void);
        }
        unsigned refCount() const
        {
            return content ? content->refCount() : 0;
        }
    protected:
        CountedHolder()
            : content(0)
        {}
        ~CountedHolder()
        {
            if( content) content->release();
        }
        explicit CountedHolder(ContentHolder* p)
            : content(p)
        {}
        CountedHolder(const CountedHolder& rhs)
            : content(rhs.content)
        {
            if( content) content->addRef();
        }
        CountedHolder& swapCountedHolder(CountedHolder & rhs)
        {
            std::swap(content, rhs.content);
            return *this;
        }

        ContentHolder* content;
    };

}

#endif
