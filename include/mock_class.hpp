//          Copyright Malcolm Noyes 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef GOOS_PIMPL_MOCK_CLASS_HPP
#define GOOS_PIMPL_MOCK_CLASS_HPP

#include "expectations.hpp"
#include "member_function_traits.hpp"
#include <cassert>

namespace goospimpl
{
    namespace detail
    {
        template <int N1, int N2, typename T = int>
        struct equal_to
        {
            static const bool value = (N1 == N2);
            typedef T type;
        };

        template <typename T>
        struct ResolvedReturnValue
        {
            T v;
            explicit ResolvedReturnValue(const ValueHolder& a)
                : v(a.value<T>())
            {}
            T value() const {return v;}
        };

        template <>
        struct ResolvedReturnValue<void>
        {
            explicit ResolvedReturnValue(const ValueHolder&)
            {}
            void value() const {}
        };

        struct EmptyArg
        {
            typedef int type;
        };

        template <typename T, int N>
        struct ArityMatcher;

        template <typename T>
        struct ArityMatcher<T, 0>
        {
            typedef EmptyArg arg1_type;
            typedef EmptyArg arg2_type;
        };

        template <typename T>
        struct ArityMatcher<T, 1>
        {
            typedef typename member_function_traits<T>::arg1_type arg1_type;
            typedef EmptyArg arg2_type;
        };

        template <typename T>
        struct ArityMatcher<T, 2>
        {
            typedef typename member_function_traits<T>::arg1_type arg1_type;
            typedef typename member_function_traits<T>::arg2_type arg2_type;
        };

    } // detail

    class FunctionCallResolver
    {
    public:
        explicit FunctionCallResolver(Expectations* p)
            : expectations(p)
        {}
        template <typename RV, typename Mock, typename T>
        RV checkFunctionCall(const std::string& name, const Mock* obj, T fn, const std::vector<ValueHolder>& parameters)
        {
            FunctionHolder t(new detail::FunctionBinder<Mock, T>(obj, fn));
            assert(expectations);
            ValueHolder rv(0);
            expectations->checkFunctionParameters(name, t, parameters, rv);
            return detail::ResolvedReturnValue<RV>(rv).value();
        }
        Expectations* expectations;
    };

    #define BEGIN_MOCK(name) \
    template <typename name> \
    struct name##_mock_class : public name, public FunctionCallResolver \
    { \
        typedef name base_type; \
        name##_mock_class(Expectations* p) : FunctionCallResolver(p) \
        {}

    #define END_MOCK() \
    };

    #define MOCK_FN_IMPL(base_name, func_type, func_name) \
        typedef typename member_function_traits<func_type>::result_type result_type_##func_name; \
        typedef typename detail::ArityMatcher<func_type, member_function_traits<func_type>::arity>::arg1_type arg1_type_f1_##func_name; \
        typedef typename detail::ArityMatcher<func_type, member_function_traits<func_type>::arity>::arg2_type arg1_type_f2_##func_name; \
        result_type_##func_name func_name() \
        { \
            std::vector<ValueHolder> results; \
            return checkFunctionCall<result_type_##func_name>( std::string(#base_name) + "::" + #func_name, static_cast<const base_type*>(this), &base_type::func_name, results); \
        } \
        result_type_##func_name func_name(arg1_type_f1_##func_name v1) \
        { \
            std::vector<ValueHolder> results; \
            results.push_back(v1); \
            return checkFunctionCall<result_type_##func_name>( std::string(#base_name) + "::" + #func_name, static_cast<const base_type*>(this), &base_type::func_name, results); \
        } \
        result_type_##func_name func_name(arg1_type_f1_##func_name v1, arg1_type_f2_##func_name v2) \
        { \
            std::vector<ValueHolder> results; \
            results.push_back(v1); \
            results.push_back(v2); \
            return checkFunctionCall<result_type_##func_name>( std::string(#base_name) + "::" + #func_name, static_cast<const base_type*>(this), &base_type::func_name, results); \
        }

    template <typename T>
    class MockContent : public CountedContent<CountedType>, public T
    {
    public:
        typedef T ValueType;
        ValueType& base() {return *static_cast<ValueType*>(this);}
        virtual const std::type_info & type() const
        {
            return typeid(ValueType);
        }
    };

    class MockHolder : public CountedHolder<MockHolder, CountedType>
    {
    public:
        explicit MockHolder(CountedType* p)
            : CountedHolder(p)
        {
        }
        template <typename T>
        T& mockReference()
        {
            assert(content);
            if( content->type() != typeid(T) )
            {
                throw std::runtime_error("wrong type");
            }
            return static_cast<MockContent<T>*>(content)->base();
        }
        const std::type_info & type() const
        {
            assert(content);
            return content->type();
        }
    };

    template<typename I>
    MockHolder createMockClass(Expectations* p);

    #define MOCK_CLASS_1(base, func1) \
    namespace goospimpl { template <typename base_type, typename F1> \
    MockHolder createMock(Expectations* p, F1) \
    { \
        struct impl : public MockContent<base_type>, public FunctionCallResolver \
        { \
            impl(Expectations* p) : FunctionCallResolver(p) {} \
            virtual const std::type_info & type() const {return typeid(base_type);} \
            MOCK_FN_IMPL(base, F1, func1) \
        }; \
        return MockHolder(new impl(p)); \
    } \
    template<> \
    MockHolder createMockClass<base>(Expectations* p) \
    { \
        typedef base type; \
        return createMock<base>(p, &type::func1); \
    } }

    #define MOCK_CLASS_2(base, func1, func2) \
    namespace goospimpl { template <typename base_type, typename F1, typename F2> \
    MockHolder createMock(Expectations* p, F1, F2) \
    { \
        struct impl : public MockContent<base_type>, public FunctionCallResolver \
        { \
            impl(Expectations* p) : FunctionCallResolver(p) {} \
            virtual const std::type_info & type() const {return typeid(base_type);} \
            MOCK_FN_IMPL(base, F1, func1) \
            MOCK_FN_IMPL(base, F2, func2) \
        }; \
        return MockHolder(new impl(p)); \
    } \
    template<> \
    MockHolder createMockClass<base>(Expectations* p) \
    { \
        typedef base type; \
        return createMock<base>(p, &type::func1, &type::func2); \
    } }

    #define MOCK_CLASS_3(base, func1, func2, func3) \
    namespace goospimpl { template <typename base_type, typename F1, typename F2, typename F3> \
    MockHolder createMock(Expectations* p, F1, F2, F3) \
    { \
        struct impl : public MockContent<base_type>, public FunctionCallResolver \
        { \
            impl(Expectations* p) : FunctionCallResolver(p) {} \
            virtual const std::type_info & type() const {return typeid(base_type);} \
            MOCK_FN_IMPL(base, F1, func1) \
            MOCK_FN_IMPL(base, F2, func2) \
            MOCK_FN_IMPL(base, F3, func3) \
        }; \
        return MockHolder(new impl(p)); \
    } \
    template<> \
    MockHolder createMockClass<base>(Expectations* p) \
    { \
        typedef base type; \
        return createMock<base>(p, &type::func1, &type::func2, &type::func3); \
    } }

    #define MOCK_CLASS_4(base, func1, func2, func3, func4) \
    namespace goospimpl { template <typename base_type, typename F1, typename F2, typename F3, typename F4> \
    MockHolder createMock(Expectations* p, F1, F2, F3, F4) \
    { \
        struct impl : public MockContent<base_type>, public FunctionCallResolver \
        { \
            impl(Expectations* p) : FunctionCallResolver(p) {} \
            virtual const std::type_info & type() const {return typeid(base_type);} \
            MOCK_FN_IMPL(base, F1, func1) \
            MOCK_FN_IMPL(base, F2, func2) \
            MOCK_FN_IMPL(base, F3, func3) \
            MOCK_FN_IMPL(base, F4, func4) \
        }; \
        return MockHolder(new impl(p)); \
    } \
    template<> \
    MockHolder createMockClass<base>(Expectations* p) \
    { \
        typedef base type; \
        return createMock<base>(p, &type::func1, &type::func2, &type::func3, &type::func4); \
    } }

    #define MOCK_CLASS_5(base, func1, func2, func3, func4, func5) \
    namespace goospimpl { template <typename base_type, typename F1, typename F2, typename F3, typename F4, typename F5> \
    MockHolder createMock(Expectations* p, F1, F2, F3, F4, F5) \
    { \
        struct impl : public MockContent<base_type>, public FunctionCallResolver \
        { \
            impl(Expectations* p) : FunctionCallResolver(p) {} \
            virtual const std::type_info & type() const {return typeid(base_type);} \
            MOCK_FN_IMPL(base, F1, func1) \
            MOCK_FN_IMPL(base, F2, func2) \
            MOCK_FN_IMPL(base, F3, func3) \
            MOCK_FN_IMPL(base, F4, func4) \
            MOCK_FN_IMPL(base, F5, func5) \
        }; \
        return MockHolder(new impl(p)); \
    } \
    template<> \
    MockHolder createMockClass<base>(Expectations* p) \
    { \
        typedef base type; \
        return createMock<base>(p, &type::func1, &type::func2, &type::func3, &type::func4, &type::func5); \
    } }

    #define MOCK_CLASS_6(base, func1, func2, func3, func4, func5, func6) \
    namespace goospimpl { template <typename base_type, typename F1, typename F2, typename F3, typename F4, typename F5, typename F6> \
    MockHolder createMock(Expectations* p, F1, F2, F3, F4, F5, F6) \
    { \
        struct impl : public MockContent<base_type>, public FunctionCallResolver \
        { \
            impl(Expectations* p) : FunctionCallResolver(p) {} \
            virtual const std::type_info & type() const {return typeid(base_type);} \
            MOCK_FN_IMPL(base, F1, func1) \
            MOCK_FN_IMPL(base, F2, func2) \
            MOCK_FN_IMPL(base, F3, func3) \
            MOCK_FN_IMPL(base, F4, func4) \
            MOCK_FN_IMPL(base, F5, func5) \
            MOCK_FN_IMPL(base, F6, func6) \
        }; \
        return MockHolder(new impl(p)); \
    } \
    template<> \
    MockHolder createMockClass<base>(Expectations* p) \
    { \
        typedef base type; \
        return createMock<base>(p, &type::func1, &type::func2, &type::func3, &type::func4, &type::func5, &type::func6); \
    } }
}

#endif
